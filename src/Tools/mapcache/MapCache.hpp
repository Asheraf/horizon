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

#ifndef HORIZON_TOOLS_MAPCACHE_HPP
#define HORIZON_TOOLS_MAPCACHE_HPP

#include "Server/Common/Client.hpp"
#include "Libraries/GRF/GRF.hpp"

#include <cstdint>
#include <map>
#include <boost/optional.hpp>

#pragma pack(push, 1)
struct mapcache_header
{
	uint32_t getFileSize() { return file_size; }
	void setFileSize(uint32_t size) { file_size = size; }

	uint16_t getMapCount() { return map_count; }
	void setMapCount(uint16_t count) { map_count = count; }

	uint16_t getVersion() { return version; }
	void setVersion(uint16_t v) { version = v; }

private:
	uint32_t file_size{0};
	uint16_t map_count{0};
	uint32_t version{0};
};

struct map_info
{
	char name[MAP_NAME_LENGTH];
	int16_t total_x{0};
	int16_t total_y{0};
	uint32_t length{0};
};
#pragma pack(pop)

struct map_data
{
	map_info info{};
	std::vector<uint8_t> cells;
};

struct map_cache
{
	mapcache_header &getHeader() { return _header; }
	void setHeader(mapcache_header &header) { _header = header; }

	void addMap(map_data &data) { maps.insert(std::make_pair(data.info.name, data)); }
	void removeMap(std::string &name)
	{
		auto it = maps.find(name);

		if (it != maps.end())
			maps.erase(it);
	}
	
	boost::optional<map_data> getMap(std::string name)
	{
		auto it = maps.find(name);

		if (it != maps.end())
			return boost::optional<map_data>(it->second);

		return boost::optional<map_data>();
	}

	std::size_t getMapCount() { return maps.size(); }

	std::map<std::string, map_data> maps;

private:
	mapcache_header _header{};
};

namespace Horizon
{
namespace Tools
{
// Used internally, this structure contains the physical map cells
class MapCache
{
public:
	MapCache();
	~MapCache();

	bool Initialize();
	bool Exists();
	bool ParseLoadResult(grf_load_result_types result);
	bool ParseGRFReadResult(std::string const &filename, grf_read_error_types error);
	void ParseExecArguments(int argc, const char *argv[]);

	void ImportFromCacheFile();

	bool BuildInternalCache();
	bool BuildExternalCache();
	bool AppendHeader();
	bool CreateNewCacheWithHeader();
	bool AppendToCache(std::string const &name);

	bool GetMapFromGRF(std::string const &name);
	void PrintGRFInfo();

	/* */
	bool ReadMapListConfig();

	/* GRF Library */
	GRF &getGRF() { return _grf; }

	/* Map Cache Path */
	boost::filesystem::path &getMapCachePath() { return _map_cache_path; }
	void setMapCachePath(std::string const &file) { _map_cache_path = file; }

	/* Compression Level */
	int getCompressionLevel() { return _compression_level; }
	void setCompressionLevel(int level) { _compression_level = level; }
	
	/* Map List Config Path */
	const boost::filesystem::path &getMapListPath() const { return _map_list_path; }
	void setMapListPath(std::string const &path) { _map_list_path = path; }

	/* Map List */
	void addToMapList(std::string const &map) { _map_list.push_back(map); }

	/* GRF Path */
	boost::filesystem::path &getGRFPath() { return _grf_path; }
	void setGRFPath(std::string const &path) { _grf_path = path; }

	/* Verbose */
	void setVerbose() { _verbose = true; }
	void unsetVerbose() { _verbose = false; }
	bool getVerbose() { return _verbose; }
private:
	boost::filesystem::path _grf_path;
	boost::filesystem::path _map_list_path;
	boost::filesystem::path _map_cache_path;
	GRF _grf;
	int _compression_level{6};
	std::map<std::string, map_data> _map_cache_data;
	std::vector<std::string> _map_list;
	std::shared_ptr<map_cache> m_cache;
	bool _verbose{false};
};
}
}

#endif // HORIZON_TOOLS_MAPCACHE_HPP
