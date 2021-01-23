/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 *
 * Copyright (c) 2019 Sagun K. (sagunxp@gmail.com).
 * Copyright (c) 2019 Horizon Dev Team.
 *
 * Base Author - Sagun K. (sagunxp@gmail.com)
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 **************************************************/

#include "MapCache.hpp"

#include "Server/Common/Configuration/Horizon.hpp"
#include "Utility/Utility.hpp"

#include <iostream>
#include <cstring>
#include <boost/algorithm/string.hpp>
#include <fstream>
#include <boost/crc.hpp>
#include <zlib.h>

#include <sol.hpp>

#define NO_WATER 1000000

Horizon::Libraries::MapCache::MapCache()
: m_cache(std::make_shared<map_cache>())
{
}


Horizon::Libraries::MapCache::~MapCache()
{
}

mcache_import_error_type Horizon::Libraries::MapCache::ImportFromCacheFile()
{
	std::ifstream ifs(getMapCachePath().c_str(), std::ios::in | std::ios::binary);
	struct mapcache_header header;
	uint8_t *compressed_buf, *uncompressed_buf;
	unsigned long compressed_size = 0, uncompressed_size = 0;
	boost::crc_32_type crc_32;

	if (!ifs.good())
		return MCACHE_IMPORT_NONEXISTENT_FILE;

	// Determine the File Size.
	ifs.seekg(0, ifs.end);
	compressed_size = ifs.tellg();
	compressed_size -= sizeof(mapcache_header);
	ifs.seekg(0, ifs.beg);

	// Read Header.
	if (!ifs.read((char *) &header, sizeof(mapcache_header)))
		return MCACHE_IMPORT_READ_ERROR;

	m_cache->setHeader(header);

	// Compressed Size.
	compressed_buf = new uint8_t[compressed_size];
	memset(compressed_buf, '\0', compressed_size);

	// Uncompressed Size.
	uncompressed_size = header.getFileSize();
	uncompressed_buf = new uint8_t[uncompressed_size];
	memset(uncompressed_buf, '\0', uncompressed_size);

	// Read the remaining size.
	if (!ifs.read((char *) compressed_buf, compressed_size)) {
		delete[] uncompressed_buf;
		delete[] compressed_buf;
		return MCACHE_IMPORT_READ_ERROR;
	}

	crc_32.process_bytes(compressed_buf, compressed_size);

	if (crc_32.checksum() != m_cache->getHeader().getChecksum()) {
		delete[] uncompressed_buf;
		delete[] compressed_buf;
		return MCACHE_IMPORT_INVALID_CHECKSUM;
	}

	// Unpack the file.
	if (uncompress((Bytef *) uncompressed_buf, &uncompressed_size, (const Bytef *) compressed_buf, compressed_size) != Z_OK) {
		delete[] uncompressed_buf;
		delete[] compressed_buf;
		return MCACHE_IMPORT_DECOMPRESS_ERROR;
	}

	for (int i = 0, pos = 0; i < m_cache->getHeader().getMapCount(); ++i) {
		map_data m{};
		uint8_t *cells = nullptr;

		if (memcpy(&m.info, uncompressed_buf + pos, sizeof(map_info)) == nullptr) {
			delete[] uncompressed_buf;
			delete[] compressed_buf;
			return MCACHE_IMPORT_MAPINFO_ERROR;
		}

		cells = new uint8_t[m.info.length];
		pos += sizeof(map_info);

		if (memcpy(cells, uncompressed_buf + pos, m.info.length) == nullptr) {
			delete[] cells;
			delete[] uncompressed_buf;
			delete[] compressed_buf;
			return MCACHE_IMPORT_CELLINFO_ERROR;
		}

		for (uint32_t c = 0; c < m.info.length; ++c)
			m.cells.push_back(cells[c]);

		delete[] cells;

		pos += m.info.length;

		m_cache->addMap(m);
	}

	delete[] compressed_buf;
	delete[] uncompressed_buf;

	return MCACHE_IMPORT_OK;
}

mcache_error_type Horizon::Libraries::MapCache::initialize()
{
	if (getGRFListPath().empty())
		return MCACHE_INVALID_GRF_PATH;

	if (getMapListPath().empty())
		return MCACHE_INVALID_CONFIG_PATH;

	if (getMapCachePath().empty())
		return MCACHE_INVALID_OUTPUT_PATH;

	if (ReadMapListConfig() != MCACHE_CONFIG_OK)
		return MCACHE_CONFIG_READ_ERROR;

	if (ReadGRFListConfig() != MCACHE_GRF_CONF_OK)
		return MCACHE_GRF_CONFIG_READ_ERROR;

	return MCACHE_OK;
}

bool Horizon::Libraries::MapCache::Exists()
{
	std::ifstream ifs(getMapCachePath().c_str(), std::ios::in | std::ios::binary);
	return ifs.good();
}

mcache_config_error_type Horizon::Libraries::MapCache::ReadMapListConfig()
{
	sol::state lua;

	// Read the file. If there is an error, report it and exit.
	try {
		lua.script_file(getMapListPath().string());
	} catch(const std::exception &e) {
		printf("Error: Parse error at %s.\n", e.what());
		return MCACHE_CONFIG_PARSE_ERROR;
	}

	sol::table map_tbl = lua["map_list"];

	map_tbl.for_each([this](sol::object const &key, sol::object const &value) {
		if (key.get_type() != sol::type::number)
			return;
		addToMapList(value.as<std::string>());
	});

	return MCACHE_CONFIG_OK;
}

mcache_grf_config_error_type Horizon::Libraries::MapCache::ReadGRFListConfig()
{
	sol::state lua;

	if (getGRFListPath().empty())
		return MCACHE_GRF_CONF_INVALID_FILE;

	// Read the file. If there is an error, report it and exit.
	try {
		lua.script_file(getGRFListPath().string());
	} catch(const std::exception &e) {
		printf("Error: Parse error at %s.\n", e.what());
		return MCACHE_GRF_CONF_PARSE_ERROR;
	}

	sol::table tbl = lua["grf_config"];
	setResourcePath(tbl.get_or("grf_resource_path", std::string("./")));

	sol::table grf_list = tbl.get<sol::table>("grf_list");

	grf_list.for_each([this](sol::object const &key, sol::object const &value) {
		int id = key.as<int>();
		std::string path = value.as<std::string>();

		if (path.empty())
			return;

		GRF grf;
		grf.set_id(id);
		grf.setGRFPath(getGRFListPath().parent_path().string() + "/" + path);
		addGRF(id, grf);
	});

	return MCACHE_GRF_CONF_OK;
}

std::pair<uint8_t, grf_load_result_type> Horizon::Libraries::MapCache::LoadGRFs()
{
	grf_load_result_type res;

	for (auto &grf : _grfs)
		if ((res = grf.second.load()) != GRF_LOAD_OK)
			return std::make_pair(grf.second.get_id(), res);

	return std::pair<uint8_t, grf_load_result_type>(-1, GRF_LOAD_OK);
}

int Horizon::Libraries::MapCache::BuildInternalCache()
{
	int new_maps = 0;

	for (std::size_t i = 0; i < _map_list.size(); ++i) {
		std::string map_name = _map_list.at(i);

		if (!m_cache->getMap(map_name)) {
			for (auto &grf : _grfs) {
				if (GetMapFromGRF(grf.second, map_name)) {
					new_maps++;
					break;
				}
			}
		}
	}

	return new_maps;
}

void Horizon::Libraries::MapCache::PrintCacheForMap(std::string const &map_name)
{
	boost::optional<map_data> data;
	std::ofstream ofs("../../../maps/"+map_name+".txt", std::ios::out);

	if (!(data = m_cache->getMap(map_name))) {
		printf("map not found\n");
		return;
	}

	int **cells = (int **) std::malloc(sizeof(int *) * data->width());
	cells[0] = (int *) std::malloc(sizeof(int) * data->width() * data->height());

	for (int i = 0; i < data->width(); i++)
		cells[i] = (*cells) + data->height() * i;

	for (int y = 0, idx = 0; y < data->height(); y++) {
		for (int x = 0; x < data->width(); x++) {
			cells[x][y] = data->getCells().at(idx++);
		}
	}

	for (int y = data->height() - 1; y >= 0; --y) {
		for (int x = 0; x < data->width(); x++) {
			int type = cells[x][y];
			//			char s;
			//			switch (type)
			//			{
			//			case 3: s = '~'; break; // walkable water
			//			case 0: // walkable ground
			//			case 2: // ???
			//			case 4: // ???
			//			case 6: s = '.'; break; // ???
			//			case 5: s = 'O'; break; // gap (snipable)
			//			case 1: s = '#'; break; // non-walkable ground
			//			}
			ofs.write(std::string("%d,", type).c_str(), 1);
		}
		ofs.write("\n", 1);
	}

	std::free(cells[0]);
	std::free(cells);
}

bool Horizon::Libraries::MapCache::BuildExternalCache()
{
	std::ofstream ofs(getMapCachePath().c_str(), std::ios::out | std::ios::binary | std::ios::trunc);
	unsigned long file_size = 0, compressed_size = 0;
	uint8_t *uncompressed_buf, *compressed_buf;
	int version = m_cache->getHeader().getVersion();
	boost::crc_32_type crc_32;

	// Pre-determine the file size.
	for (auto m : m_cache->maps) {
		map_data data = m.second;
		file_size += sizeof(struct map_info) + data.info.length;
	}

	uncompressed_buf = new uint8_t[file_size];
	compressed_buf = new uint8_t[file_size];
	compressed_size = compressBound(file_size);

	int pos = 0;
	// Content
	for (auto m : m_cache->maps) {
		map_data data = m.second;
		memcpy(uncompressed_buf + pos, &data.info, sizeof(data.info));
		pos += sizeof(data.info);
		memcpy(uncompressed_buf + pos, data.cells.data(), data.cells.size());
		pos += data.cells.size();
		PrintCacheForMap(m.first);
	}

	compress2((Bytef *) compressed_buf, &compressed_size, (const Bytef *) uncompressed_buf, file_size, getCompressionLevel());
	crc_32.process_bytes(compressed_buf, compressed_size);

	// Header
	m_cache->getHeader().setMapCount(m_cache->maps.size());
	m_cache->getHeader().setFileSize(file_size);
	m_cache->getHeader().setVersion(++version);
	m_cache->getHeader().setChecksum(crc_32.checksum());

	ofs.write((char *) &m_cache->getHeader(), sizeof(mapcache_header));
	ofs.write((char *) compressed_buf, compressed_size);

	delete[] uncompressed_buf;
	delete[] compressed_buf;
	return true;
}

bool Horizon::Libraries::MapCache::ParseGRFReadResult(GRF &grf, std::string const &filename, grf_read_error_type error)
{
	std::string grf_name =  grf.getGRFPath().filename().string();

	switch (error)
	{
	case GRE_OK:
	default:
		break;
	case GRE_NOT_FOUND:
		printf("Warning: File '%s' could not be located in GRF '%s'.\n", filename.c_str(), grf_name.c_str());
		return false;
	case GRE_DECOMPRESS_SIZE_MISMATCH:
		printf("Warning: File '%s' decompressed size mismatch in GRF '%s'.\n", filename.c_str(), grf_name.c_str());
		return false;
	case GRE_READ_ERROR:
		printf("Warning: File '%s' could not be read in GRF '%s'.\n", filename.c_str(), grf_name.c_str());
		return false;
	}

	return true;
}

/**
 * @brief Reads a map from GRF's GAT and RSW files
 * @param[in] name  name of the map.
 * @return true on success, false on failure.
 */
bool Horizon::Libraries::MapCache::GetMapFromGRF(GRF &grf, std::string const &name)
{
	char filename[256];
	std::pair<grf_read_error_type, uint8_t *> gat, rsw;
	int water_height;
	map_data m;

	// Set the Map Name.
	std::strncpy(m.info.name, name.c_str(), sizeof(m.info.name));

	// Search and retrieve the map's GAT file.
	std::sprintf(filename, "data\\%s.gat", name.c_str());

	gat = grf.read(filename, nullptr);

	if (!ParseGRFReadResult(grf, filename, gat.first))
		return false;

	// Search and retrieve the map's RSW file.
	std::sprintf(filename, "data\\%s.rsw", name.c_str());

	rsw = grf.read(filename, nullptr);

	if (!ParseGRFReadResult(grf, filename, rsw.first))
		return false;

	// Determine the water height of the map.
	if (rsw.second != nullptr) {
		water_height = GetULong((unsigned char *) rsw.second + 166);
		delete rsw.second;
	} else
		water_height = NO_WATER;

	// Determine the map size and allocate needed memory.
	m.info.total_x = (int16_t) GetULong((unsigned char *) (gat.second + 6));
	m.info.total_y = (int16_t) GetULong((unsigned char *) (gat.second + 10));

	if (m.info.total_x <= 0 || m.info.total_y <= 0) {
		delete gat.second;
		return false;
	}

	// Set the length of total map cell data as part of the each cache entry.
	m.info.length = m.info.total_x * m.info.total_y;

	// Set cell information.
	int offset = 14;

	for (std::size_t i = 0; i < m.info.length; ++i) {
		// Height of the bottom-left corner
		// The actual start of the map.
		float height = GetFloat((unsigned char *) (gat.second + offset));
		// Type of cell
		uint32_t type = GetULong((unsigned char *) (gat.second + offset + 16));

		if (type == 0 && water_height != NO_WATER && height > water_height)
			type = 3; // Cell is 0 (walkable) but under water level, set to 3 (walkable water)

		offset += 20;

		// Maps are stored starting (0, map_height), (1, map_height) ... (map_width, 0)
		m.cells.push_back(type);
	}

	// Push into our internal cache.
	m_cache->addMap(m);

	delete gat.second;

	return true;
}
