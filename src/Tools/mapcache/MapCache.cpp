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

#include <boost/algorithm/string.hpp>
#include <libconfig.h++>

Horizon::Tools::MapCache::MapCache()
{

}

Horizon::Tools::MapCache::~MapCache()
{

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
				getLibrary().setGRFPath(arg_parts.at(1));
			} else if (arg_parts.at(0).compare("--config") == 0) {
				getLibrary().setMapListPath(arg_parts.at(1));
			} else if (arg_parts.at(0).compare("--compression-level") == 0) {
				int level = atoi(arg_parts.at(1).c_str());
				if (level > 9 || level < 1) {
					printf("Error: Invalid compression level set, defaulting to 6.");
				} else {
					getLibrary().setCompressionLevel(level);
				}
			} else if (arg_parts.at(0).compare("--verbose") == 0) {
				getLibrary().setVerbose();
			} else if (arg_parts.at(0).compare("--output") == 0) {
				getLibrary().setMapCachePath(arg_parts.at(1));
			} else {
				printf("Unrecognised argument '%s'\n", it->c_str());
			}
		}
	}
}

bool Horizon::Tools::MapCache::ParseInitializeResult(mcache_error_types type)
{
	switch (type)
	{
	case MCACHE_INVALID_GRF_PATH:
		printf("Invalid GRF path '%s' provided.\n", getLibrary().getGRFPath().c_str());
		return false;
	case MCACHE_INVALID_CONFIG_PATH:
		printf("Invalid config path '%s' provided.\n", getLibrary().getMapListPath().c_str());
		return false;
	case MCACHE_INVALID_OUTPUT_PATH:
		printf("Invalid output path '%s' provided.\n", getLibrary().getMapCachePath().c_str());
		return false;
	case MCACHE_CONFIG_READ_ERROR:
		printf("There was an error reading the configuration.\n");
		return false;
	case MCACHE_GRF_LOAD_ERROR:
		printf("There was an error loading the GRF.\n");
		return false;
	default:
		break;
	}
	return true;
}

bool Horizon::Tools::MapCache::ParseGRFLoadResult(grf_load_result_types result)
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
			printf("GRF: Invalid grf version %x. aborting...\n", getLibrary().getGRF().getGRFVersion());
			return true;
		case GRF_LOAD_READ_ERROR:
			printf("GRF: Read error while loading the grf. Aborting...\n");
			return true;
		case GRF_LOAD_MAGIC_ERROR:
			printf("GRF: Magic header was not 'Master of Magic'! Aborting...\n");
			return true;
		case GRF_LOAD_PATH_ERROR:
			printf("GRF: Incorrect path '%s' given for grf. Aborting...\n", getLibrary().getGRF().getGRFPath().c_str());
			return true;
		case GRF_LOAD_INCOMPLETE_HEADER:
			printf("GRF: Error reading header of the given grf '%s'. Aborting...\n", getLibrary().getGRF().getGRFPath().c_str());
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

bool Horizon::Tools::MapCache::ParseMapCacheImportResult(mcache_import_error_types type)
{
	switch (type)
	{
	default:
		printf("Info: Import of %lu maps was successful.\n", getLibrary().getMCache()->maps.size());
		break;
	case MCACHE_IMPORT_NONEXISTENT_FILE:
		printf("Error: Could not open file '%s'.\n", getLibrary().getMapCachePath().c_str());
		return false;
	case MCACHE_IMPORT_READ_ERROR:
		printf("Error: Could not read file '%s', rebuilding...\n", getLibrary().getMapCachePath().c_str());
		return false;
	case MCACHE_IMPORT_INVALID_CHECKSUM:
		printf("Error: File cache file '%s' is corrupted (invalid checksum), rebuilding...\n", getLibrary().getMapCachePath().c_str());
		return false;
	case MCACHE_IMPORT_DECOMPRESS_ERROR:
		printf("Error: File cache file '%s' could not be decompressed, rebuilding...\n", getLibrary().getMapCachePath().c_str());
		return false;
	case MCACHE_IMPORT_MAPINFO_ERROR:
		printf("Error: Could not read map information for a map while importing file '%s', rebuilding...\n", getLibrary().getMapCachePath().c_str());
		return false;
	case MCACHE_IMPORT_CELLINFO_ERROR:
		printf("Error: Could not read cell information for a map while importing file '%s', rebuilding...\n", getLibrary().getMapCachePath().c_str());
		return false;
	}

	return true;
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

	if (!m.ParseInitializeResult(m.getLibrary().Initialize()))
		return SIGABRT;

	printf("Info: Config file path: '%s'\n", m.getLibrary().getMapListPath().c_str());
	printf("Info: Compression Level '%d'\n", m.getLibrary().getCompressionLevel());
	printf("Info: Output file set to '%s'\n", m.getLibrary().getMapCachePath().c_str());

	// GRF
	m.getLibrary().getGRF().setGRFPath(m.getLibrary().getGRFPath().c_str());

	if (m.ParseGRFLoadResult(m.getLibrary().getGRF().load()))
		return 1;

	int size = m.getLibrary().getGRF().getGRFSize();
	float kb_size = size / 1024;
	float mb_size = kb_size / 1024;
	float gb_size = mb_size / 1024;

	printf("Info: GRF Loaded '%s' from path '%s'.\n", m.getLibrary().getGRF().getGRFPath().filename().c_str(),
		   m.getLibrary().getGRF().getGRFPath().generic_path().c_str());
	printf("Info: Total GRF Size - %d B (%0.2f KB or %0.2f MB or %0.2f GB).\n", size, kb_size, mb_size, gb_size);
	printf("Info: GRF has '%d' Total Compressed Files.\n", m.getLibrary().getGRF().getTotalFiles());
	printf("Info: GRF Version %x\n", m.getLibrary().getGRF().getGRFVersion());
	printf("Info: GRF file path: '%s'\n", m.getLibrary().getGRFPath().c_str());

	if (m.getLibrary().Exists()) {
		printf("Info: Importing previously cached information from '%s'...\n", m.getLibrary().getMapCachePath().c_str());
		m.ParseMapCacheImportResult(m.getLibrary().ImportFromCacheFile());
	}

	printf("Info: Building internal cache...\n");

	int new_maps = m.getLibrary().BuildInternalCache();
	printf("Info: Internal cache has been built with %d new maps (out of %lu total).\n", new_maps,
		   m.getLibrary().getMCache()->maps.size());

	printf("Info: Building external cache...\n");
	if (m.getLibrary().BuildExternalCache())
		printf("Info: Map cache has been built with %lu maps and saved to '%s'\n", m.getLibrary().getMCache()->maps.size(), m.getLibrary().getMapCachePath().c_str());
	
	return 0;
}
