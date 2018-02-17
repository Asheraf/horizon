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

#define NO_WATER 1000000

Horizon::Tools::MapCache::MapCache()
: m_cache(std::make_shared<map_cache>())
{
}


Horizon::Tools::MapCache::~MapCache()
{
}

void Horizon::Tools::MapCache::PrintGRFInfo()
{
	int size = getGRF().getGRFSize();
	float kb_size = size / 1024;
	float mb_size = kb_size / 1024;
	float gb_size = mb_size / 1024;

	printf("GRF: Loaded '%s' from path '%s'.\n", getGRF().getGRFPath().filename().c_str(), getGRF().getGRFPath().generic_path().c_str());
	printf("GRF: Total Size - %d B (%0.2f KB or %0.2f MB or %0.2f GB).\n", size, kb_size, mb_size, gb_size);
	printf("GRF: %d Total Compressed Files.\n", getGRF().getTotalFiles());
	printf("GRF: Version %x\n", getGRF().getGRFVersion());
}

bool Horizon::Tools::MapCache::ParseLoadResult(grf_load_result_types result)
{
	switch (result)
	{
	case GRF_LOAD_HEADER_READ_ERROR:
		printf("GRF: Error reading grf header. aborting...\n");
		return true;
	case GRF_LOAD_FORMAT_ERROR:
		printf("GRF: Invalid or unknown grf header format. aborting...\n");
		return true;
	case GRF_LOAD_INVALID_VERSION:
		printf("GRF: Invalid grf version %x. aborting...\n", getGRF().getGRFVersion());
		return true;
	case GRF_LOAD_READ_ERROR:
		printf("GRF: Read error while loading the grf. Aborting...\n");
		return true;
	case GRF_LOAD_MAGIC_ERROR:
		printf("GRF: Magic header was not 'Master of Magic'! Aborting...\n");
		return true;
	case GRF_LOAD_PATH_ERROR:
		printf("GRF: Incorrect path '%s' given for grf. Aborting...\n", getGRF().getGRFPath().c_str());
		return true;
	case GRF_LOAD_INCOMPLETE_HEADER:
		printf("GRF: Error reading header of the given grf '%s'. Aborting...\n", getGRF().getGRFPath().c_str());
		return true;
	case GRF_LOAD_ILLEGAL_DATA_FORMAT:
		printf("GRF: Illegal data format, compressed size is greater than expected.\n");
		return true;
	case GRF_LOAD_OK:
	default:
		break;
	}

	return false;
}

void Horizon::Tools::MapCache::ImportFromCacheFile()
{
	std::ifstream ifs(getMapCachePath().c_str(), std::ios::in | std::ios::binary);
	struct mapcache_header header;
	uint8_t *compressed_buf, *uncompressed_buf;
	unsigned long compressed_size = 0, uncompressed_size = 0;

	if (!ifs) {
		printf("An error as occured in fread while reading map_cache.\n");
		return;
	}
	
	// Determine the File Size.
	ifs.seekg(0, ifs.end);
	compressed_size = ifs.tellg();
	ifs.seekg(0, ifs.beg);

	// Read Header.
	if (!ifs.read((char *) &header, sizeof(mapcache_header))) {
		printf("Error: External map-cache is corrupted, rebuilding...\n");
		return;
	}

	m_cache->setHeader(header);

	// Compressed Size.
	compressed_size -= sizeof(mapcache_header);
	compressed_buf = new uint8_t[compressed_size];
	memset(compressed_buf, '\0', compressed_size);

	// Uncompressed Size.
	uncompressed_size = header.getFileSize();
	uncompressed_buf = new uint8_t[uncompressed_size];
	memset(uncompressed_buf, '\0', uncompressed_size);

	// Read the remaining size.
	if (!ifs.read((char *) compressed_buf, compressed_size)) {
		printf("Error: Couldn't read the external map cache file, rebuilding...\n");
		return;
	}

	// Unpack the file.
	if (getGRF().unpack(uncompressed_buf, &uncompressed_size, compressed_buf, compressed_size) != 0) {
		printf("Error: Couldn't decompress the map cache file, rebuilding...\n");
		return;
	}

	for (int i = 0, pos = 0; i < m_cache->getHeader().getMapCount(); ++i) {
		map_data m{};
		uint8_t *cells = nullptr;

		if (memcpy(&m.info, uncompressed_buf + pos, sizeof(map_info)) == nullptr) {
			printf("An error as occured while reading information for map #%d.\n", i);
			return;
		}

		cells = new uint8_t[m.info.length];
		pos += sizeof(map_info);

		if (memcpy(cells, uncompressed_buf + pos, m.info.length) == nullptr) {
			printf("An error as occured while reading cells for map '%s'.\n", m.info.name);
			return;
		}

		for (uint32_t c = 0; c < m.info.length; ++c)
			m.cells.push_back(cells[c]);

		delete[] cells;

		pos += m.info.length;

		m_cache->addMap(m);

		if (getVerbose())
			printf("Info: Found and read map '%s' from cache.\n", m.info.name);
	}

	printf("Info: Found and imported %lu maps from external cache file.\n", m_cache->getMapCount());

	delete[] compressed_buf;
	delete[] uncompressed_buf;
}

bool Horizon::Tools::MapCache::Initialize()
{
	if (getGRFPath().empty() || getMapListPath().empty()) {
		printf("GRF or Map List are not provided! aborting...\n");
		return false;
	}

	printf("Info: GRF file path: '%s'\n", _grf_path.c_str());
	printf("Info: Config file path: '%s'\n", getMapListPath().c_str());
	printf("Info: Compression Level '%d'\n", getCompressionLevel());
	printf("Info: Output file set to '%s'\n", getMapCachePath().c_str());

	// Config
	if (!ReadMapListConfig())
		return false;

	// GRF
	getGRF().setGRFPath(getGRFPath().c_str());

	if (ParseLoadResult(getGRF().load()))
		return false;

	PrintGRFInfo();

	if (!Exists()) {
		printf("Info: '%s' does not exist and will be built from scratch.\n", getMapCachePath().filename().c_str());
	} else {
		ImportFromCacheFile();
	}

	BuildInternalCache();

	return true;
}

inline bool Horizon::Tools::MapCache::Exists()
{
	std::ifstream ifs(getMapCachePath().c_str(), std::ios::in | std::ios::binary);
	return ifs.good();
}

bool Horizon::Tools::MapCache::ReadMapListConfig()
{
	libconfig::Config cfg;
	std::string tmp_string;

	// Read the file. If there is an error, report it and exit.
	try {
		cfg.readFile(getMapListPath().c_str());
	} catch(const libconfig::FileIOException &fioex) {
		printf("Error: I/O error while reading file '%s'.\n", getMapListPath().c_str());
		return false;
	} catch(const libconfig::ParseException &pex) {
		printf("Error: Parse error at %s:%d - %s.\n", pex.getFile(), pex.getLine(), pex.getError());
		return false;
	}

	const libconfig::Setting &map_list = cfg.getRoot()["map_list"];

	if (map_list.isArray() == false) {
		printf("Error: Expected array for config 'map_list' in file '%s'.\n", getMapListPath().c_str());
		return false;
	}

	for (int i = 0; i < map_list.getLength(); ++i) {
		if (map_list[i].getType() != libconfig::Setting::TypeString) {
			printf("Error: Invalid type for entry %d in config 'map_list'... skipping.\n", i + 1);
			continue;
		}

		addToMapList(map_list[i]);
	}

	return true;
}

bool Horizon::Tools::MapCache::BuildInternalCache()
{
	for (std::size_t i = 0; i < _map_list.size(); ++i) {
		std::string map_name = _map_list.at(i);

		if (!m_cache->getMap(map_name)) {
			if (GetMapFromGRF(map_name) && getVerbose()) {
				printf("Info: Map '%s' extracted from GRF into internal cache.\n", map_name.c_str());
			}
		} else if (getVerbose()) {
			printf("Info: Map '%s' is available in internal cache.\n", map_name.c_str());
		}
	}

	printf("Info: Built internal cache with %lu maps.\n", m_cache->getMapCount());

	return true;
}

bool Horizon::Tools::MapCache::BuildExternalCache()
{
	std::ofstream ofs(getMapCachePath().c_str(), std::ios::out | std::ios::binary);
	unsigned long file_size = 0, compressed_size = 0;
	uint8_t *uncompressed_buf, *compressed_buf;
	int version = m_cache->getHeader().getVersion();

	// Pre-determine the file size.
	for (auto m : m_cache->maps) {
		map_data data = m.second;
		file_size += sizeof(struct map_info) + data.info.length;
	}

	m_cache->getHeader().setMapCount(m_cache->maps.size());
	m_cache->getHeader().setFileSize(file_size);
	m_cache->getHeader().setVersion(++version);

	// Header
	ofs.write((char *) &m_cache->getHeader(), sizeof(mapcache_header));

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
	ofs.write((char *) compressed_buf, compressed_size);

	printf("Info: Built external cache at '%s' with %lu maps. (Cache Version: %d)\n", getMapCachePath().c_str(), m_cache->getMapCount(), m_cache->getHeader().getVersion());

	delete[] uncompressed_buf;
	delete[] compressed_buf;
	return true;
}

enum map_cell_types
{
	MAP_CELL_WALKABLE = 0,
	MAP_CELL_WALKABLE_UNDER_WATER = 3,
};

bool Horizon::Tools::MapCache::ParseGRFReadResult(std::string const &filename, grf_read_error_types error)
{
	switch (error)
	{
	case GRE_OK:
	default:
		break;
	case GRE_NOT_FOUND:
		printf("Error: File '%s' could not be located in the GRF.\n", filename.c_str());
		return false;
	case GRE_DECOMPRESS_SIZE_MISMATCH:
		printf("Error: File '%s' decompressed size mismatch.\n", filename.c_str());
		return false;
	case GRE_READ_ERROR:
		printf("Error: File '%s' could not be read.\n", filename.c_str());
		return false;
	}

	return true;
}

/**
 * @brief Reads a map from GRF's GAT and RSW files
 * @param[in] name  name of the map.
 * @return true on success, false on failure.
 */
bool Horizon::Tools::MapCache::GetMapFromGRF(std::string const &name)
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

void Horizon::Tools::MapCache::parseExecArguments(int argc, const char *argv[])
{
	for (int i = 1; i < argc; ++i) {
		std::string arg(argv[i]);
		std::vector<std::string> separated_args;
		boost::split(separated_args, arg, boost::is_any_of(" "));

		for (auto it = separated_args.begin(); it != separated_args.end(); ++it) {
			std::vector<std::string> arg_parts;
			boost::split(arg_parts, *it, boost::is_any_of("="));

			if (arg_parts.at(0).compare("--grf") == 0) {
				setGRFPath(arg_parts.at(1));
			} else if (arg_parts.at(0).compare("--config") == 0) {
				setMapListPath(arg_parts.at(1));
			} else if (arg_parts.at(0).compare("--compression-level") == 0) {
				int level = atoi(arg_parts.at(1).c_str());
				if (level > 9 || level < 1) {
					printf("Error: Invalid compression level set, defaulting to 6.");
				} else {
					setCompressionLevel(level);
				}
			} else if (arg_parts.at(0).compare("--verbose") == 0) {
				setVerbose();
			} else if (arg_parts.at(0).compare("--output") == 0) {
				setMapCachePath(arg_parts.at(1));
			} else {
				printf("Unrecognised argument '%s'\n", it->c_str());
			}
		}
	}
}

/**
 * Main Runtime Method
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, const char * argv[])
{
	printf("     _   _            _\n");
	printf("    | | | |          (_)\n");
	printf("    | |_| | ___  _ __ _ _______  _ __\n");
	printf("    |  _  |/ _ \\| '__| |_  / _ \\| '_  \\\n");
	printf("    | | | | (_) | |  | |/ / (_) | | | |\n");
	printf("    \\_| |_/\\___/|_|  |_/___\\___/|_| |_|\n\n");
	printf("     Horizon Map Cache \n\n");
	printf("Credits: \n");
	printf("   Smokexyz (sagunkho@hotmail.com)\n\n");

	Horizon::Tools::MapCache m;

	m.parseExecArguments(argc, argv);

	if (!m.Initialize()) {
		printf("Error: Map Cache module failed to initialize.\n");
		return 1;
	}

	m.BuildExternalCache();
	return 0;
}
