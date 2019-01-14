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

#include "Libraries/MapCache/MapCache.hpp"
#include "Libraries/GRF/GRF.hpp"

#include <cstdint>
#include <map>
#include <boost/optional.hpp>

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

	void parse_exec_args(int argc, const char *argv[]);
	
	bool ParseInitializeResult(mcache_error_types type);

	bool ParseGRFLoadResult(std::pair<uint8_t, grf_load_result_types> result);

	bool ParseMapCacheImportResult(mcache_import_error_types type);

	Horizon::Libraries::MapCache &getLibrary() { return _cache; }
private:
	Horizon::Libraries::MapCache _cache;
};
}
}

#endif // HORIZON_TOOLS_MAPCACHE_HPP
