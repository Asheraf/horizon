/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 * Copyright (c) 2018 Horizon Dev Team.
 *
 * Base Author - Sagun Khosla. (sagunxp@gmail.com)
 *
 * Under a proprietary license this file is not for use
 * or viewing without permission.
 **************************************************/

#include "MapCache.hpp"

#include "Server/Common/Client.hpp"
#include "Utility/Utility.hpp"

#include <iostream>
#include <cstring>
#include <boost/algorithm/string.hpp>
#include <libconfig.h++>
#include <fstream>
#include <boost/crc.hpp>

#define NO_WATER 1000000

Horizon::Libraries::MapCache::MapCache()
: m_cache(std::make_shared<map_cache>())
{
}


Horizon::Libraries::MapCache::~MapCache()
{
}

mcache_import_error_types Horizon::Libraries::MapCache::ImportFromCacheFile()
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
	if (!ifs.read((char *) compressed_buf, compressed_size))
		return MCACHE_IMPORT_READ_ERROR;

	crc_32.process_bytes(compressed_buf, compressed_size);

	if (crc_32.checksum() != m_cache->getHeader().getChecksum())
		return MCACHE_IMPORT_INVALID_CHECKSUM;

	// Unpack the file.
	if (getGRF().unpack(uncompressed_buf, &uncompressed_size, compressed_buf, compressed_size) != 0)
		return MCACHE_IMPORT_DECOMPRESS_ERROR;

	for (int i = 0, pos = 0; i < m_cache->getHeader().getMapCount(); ++i) {
		map_data m{};
		uint8_t *cells = nullptr;

		if (memcpy(&m.info, uncompressed_buf + pos, sizeof(map_info)) == nullptr)
			return MCACHE_IMPORT_MAPINFO_ERROR;

		cells = new uint8_t[m.info.length];
		pos += sizeof(map_info);

		if (memcpy(cells, uncompressed_buf + pos, m.info.length) == nullptr)
			return MCACHE_IMPORT_CELLINFO_ERROR;

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

mcache_error_types Horizon::Libraries::MapCache::Initialize()
{
	if (getGRFPath().empty())
		return MCACHE_INVALID_GRF_PATH;

	if (getMapListPath().empty())
		return MCACHE_INVALID_CONFIG_PATH;

	if (getMapCachePath().empty())
		return MCACHE_INVALID_OUTPUT_PATH;

	// Config
	if (ReadMapListConfig() != MCACHE_CONFIG_OK)
		return MCACHE_CONFIG_READ_ERROR;

	return MCACHE_OK;
}

bool Horizon::Libraries::MapCache::Exists()
{
	std::ifstream ifs(getMapCachePath().c_str(), std::ios::in | std::ios::binary);
	return ifs.good();
}

mcache_config_error_types Horizon::Libraries::MapCache::ReadMapListConfig()
{
	libconfig::Config cfg;
	std::string tmp_string;

	// Read the file. If there is an error, report it and exit.
	try {
		cfg.readFile(getMapListPath().c_str());
	} catch(const libconfig::FileIOException &fioex) {
		return MCACHE_CONFIG_INVALID_FILE;
	} catch(const libconfig::ParseException &pex) {
		printf("Error: Parse error at %s:%d - %s.\n", pex.getFile(), pex.getLine(), pex.getError());
		return MCACHE_CONFIG_PARSE_ERROR;
	}

	const libconfig::Setting &map_list = cfg.getRoot()["map_list"];

	if (map_list.isArray() == false)
		return MCACHE_CONFIG_INVALID_ROOT_TYPE;

	for (int i = 0; i < map_list.getLength(); ++i) {
		if (map_list[i].getType() != libconfig::Setting::TypeString)
			return MCACHE_CONFIG_INVALID_VALUE_TYPE;
		addToMapList(map_list[i]);
	}

	return MCACHE_CONFIG_OK;
}

int Horizon::Libraries::MapCache::BuildInternalCache()
{
	int new_maps = 0;
	for (std::size_t i = 0; i < _map_list.size(); ++i) {
		std::string map_name = _map_list.at(i);

		if (!m_cache->getMap(map_name)) {
			if (GetMapFromGRF(map_name))
				new_maps++;
		}
	}

	return new_maps;
}

bool Horizon::Libraries::MapCache::BuildExternalCache()
{
	std::ofstream ofs(getMapCachePath().c_str(), std::ios::out | std::ios::binary);
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

	int pos = 0;
	// Content
	for (auto m : m_cache->maps) {
		map_data data = m.second;
		memcpy(uncompressed_buf + pos, &data.info, sizeof(data.info));
		pos += sizeof(data.info);
		memcpy(uncompressed_buf + pos, data.cells.data(), data.cells.size());
		pos += data.cells.size();
	}

	getGRF().pack(compressed_buf, &compressed_size, uncompressed_buf, file_size, getCompressionLevel());

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

bool Horizon::Libraries::MapCache::ParseGRFReadResult(std::string const &filename, grf_read_error_types error)
{
	switch (error)
	{
	case GRE_OK:
	default:
		break;
	case GRE_NOT_FOUND:
		printf("Warning: File '%s' could not be located in the GRF.\n", filename.c_str());
		return false;
	case GRE_DECOMPRESS_SIZE_MISMATCH:
		printf("Warning: File '%s' decompressed size mismatch.\n", filename.c_str());
		return false;
	case GRE_READ_ERROR:
		printf("Warning: File '%s' could not be read.\n", filename.c_str());
		return false;
	}

	return true;
}

/**
 * @brief Reads a map from GRF's GAT and RSW files
 * @param[in] name  name of the map.
 * @return true on success, false on failure.
 */
bool Horizon::Libraries::MapCache::GetMapFromGRF(std::string const &name)
{
	char filename[256];
	std::pair<grf_read_error_types, uint8_t *> gat, rsw;
	int water_height;
	map_data m;

	// Set the Map Name.
	std::strncpy(m.info.name, name.c_str(), sizeof(m.info.name));

	// Search and retrieve the map's GAT file.
	std::sprintf(filename, "data\\%s.gat", name.c_str());

	gat = getGRF().read(filename, nullptr);

	if (!ParseGRFReadResult(filename, gat.first))
		return false;

	// Search and retrieve the map's RSW file.
	std::sprintf(filename, "data\\%s.rsw", name.c_str());

	rsw = getGRF().read(filename, nullptr);

	if (!ParseGRFReadResult(filename, rsw.first))
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
		offset += 20;

		if (type == 0 && water_height != NO_WATER && height > water_height)
			type = 3; // Cell is 0 (walkable) but under water level, set to 3 (walkable water)

		// Push back into cell vector.
		m.cells.push_back(type);
	}

	// Push into our internal cache.
	m_cache->addMap(m);

	delete gat.second;

	return true;
}
