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

#ifndef HORIZON_LIBRARIES_MAPCACHE_HPP
#define HORIZON_LIBRARIES_MAPCACHE_HPP

#include "Server/Common/Configuration/Client.hpp"
#include "Libraries/GRF/GRF.hpp"

#include <cstdint>
#include <map>
#include <boost/optional.hpp>
#include <unordered_map>

#pragma pack(push, 1)
struct mapcache_header
{
	uint32_t getFileSize() { return file_size; }
	void setFileSize(uint32_t size) { file_size = size; }

	uint16_t getMapCount() { return map_count; }
	void setMapCount(uint16_t count) { map_count = count; }

	uint16_t getVersion() { return version; }
	void setVersion(uint16_t v) { version = v; }

	uint32_t getChecksum() { return checksum; }
	void setChecksum(uint32_t c) { checksum = c; }

private:
	uint32_t file_size{0};
	uint16_t map_count{0};
	uint32_t version{0};
	uint32_t checksum{0};
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
	const std::vector<uint8_t> &getCells() { return cells; }
	std::string name() { return info.name; }
	uint16_t width() { return info.total_x; }
	uint16_t height() { return info.total_y; }
	uint32_t size() { return info.length; }

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

enum mcache_error_type
{
	MCACHE_OK                    = 0,
	MCACHE_INVALID_GRF_PATH      = 1,
	MCACHE_INVALID_CONFIG_PATH   = 2,
	MCACHE_INVALID_OUTPUT_PATH   = 3,
	MCACHE_CONFIG_READ_ERROR     = 4,
	MCACHE_GRF_CONFIG_READ_ERROR = 5,
	MCACHE_GRF_LOAD_ERROR        = 6
};

enum mcache_config_error_type
{
	MCACHE_CONFIG_OK                  = 0,
	MCACHE_CONFIG_PARSE_ERROR         = 1,
	MCACHE_CONFIG_INVALID_VALUE_TYPE  = 2,
};

enum mcache_grf_config_error_type
{
	MCACHE_GRF_CONF_OK                 = 0,
	MCACHE_GRF_CONF_INVALID_FILE       = 1,
	MCACHE_GRF_CONF_PARSE_ERROR        = 2,
	MCACHE_GRF_CONF_INVALID_VALUE_TYPE = 3
};

enum mcache_import_error_type
{
	MCACHE_IMPORT_OK                = 0,
	MCACHE_IMPORT_NONEXISTENT_FILE  = 1,
	MCACHE_IMPORT_READ_ERROR        = 2,
	MCACHE_IMPORT_INVALID_CHECKSUM  = 3,
	MCACHE_IMPORT_DECOMPRESS_ERROR  = 4,
	MCACHE_IMPORT_MAPINFO_ERROR     = 5,
	MCACHE_IMPORT_CELLINFO_ERROR    = 6,
};

enum mcache_map_cell_type
{
	MAP_CELL_WALKABLE = 0,
	MAP_CELL_WALKABLE_UNDER_WATER = 3,
};

namespace Horizon
{
namespace Libraries
{
// Used internally, this structure contains the physical map cells
class MapCache
{
public:
	MapCache();
	~MapCache();

	mcache_error_type initialize();
	bool Exists();

	mcache_import_error_type ImportFromCacheFile();

	int BuildInternalCache();
	bool BuildExternalCache();
	bool AppendHeader();
	bool CreateNewCacheWithHeader();
	bool AppendToCache(std::string const &name);

	bool GetMapFromGRF(GRF &grf, std::string const &name);

	bool ParseGRFReadResult(GRF &grf, std::string const &filename, grf_read_error_type error);

	/* */
	mcache_config_error_type ReadMapListConfig();
	/* */
	mcache_grf_config_error_type ReadGRFListConfig();
	/* */
	std::pair<uint8_t, grf_load_result_type> LoadGRFs();

	void PrintCacheForMap(std::string const &map_name);

	/* GRF Library */
	GRF &getGRF(uint8_t id) { return _grfs.at(id); }
	void addGRF(uint8_t id, GRF &grf) { _grfs[id] = grf; }

	/* Map Cache Path */
	boost::filesystem::path &getMapCachePath() { return _map_cache_path; }
	void setMapCachePath(std::string const &file) { _map_cache_path = file; }

	/* Compression Level */
	int getCompressionLevel() { return _compression_level; }
	void setCompressionLevel(int level) { _compression_level = level; }

	/* Map List Config Path */
	const boost::filesystem::path &getMapListPath() const { return _map_list_path; }
	void setMapListPath(std::string const &path) { _map_list_path = path; }

	/* GRF List Config Path */
	const boost::filesystem::path &getGRFListPath() const { return _grf_list_path; }
	void setGRFListPath(std::string const &path) { _grf_list_path = path; }

	/* Map List */
	void addToMapList(std::string const &map) { _map_list.push_back(map); }

	/* GRF Path */
	const boost::filesystem::path &getGRFPath(uint8_t id) { return _grfs[id].getGRFPath(); }
	void setGRFPath(uint8_t id, std::string const &path) { _grfs[id].setGRFPath(path); }

	/* Resource Path */
	const boost::filesystem::path &getResourcePath() { return _resource_path; }
	void setResourcePath(std::string const &path) { _resource_path = path; }

	/* Verbose */
	void setVerbose() { _verbose = true; }
	void unsetVerbose() { _verbose = false; }
	bool getVerbose() { return _verbose; }

	/* MCache */
	std::shared_ptr<map_cache> getMCache() { return m_cache; }

	const std::unordered_map<uint8_t, GRF> &getGRFs() { return _grfs; }
private:
	boost::filesystem::path _map_list_path;
	boost::filesystem::path _grf_list_path, _resource_path;
	boost::filesystem::path _map_cache_path;
	std::unordered_map<uint8_t, GRF> _grfs;
	int _compression_level{6};
	std::map<std::string, map_data> _map_cache_data;
	std::vector<std::string> _map_list;
	std::shared_ptr<map_cache> m_cache;
	bool _verbose{false};
};
}
}

#endif // HORIZON_LIBRARIES_MAPCACHE_HPP
