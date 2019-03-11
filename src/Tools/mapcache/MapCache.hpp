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

	bool ParseInitializeResult(mcache_error_type type);

	bool ParseGRFLoadResult(std::pair<uint8_t, grf_load_result_type> result);

	bool ParseMapCacheImportResult(mcache_import_error_type type);

	Horizon::Libraries::MapCache &getLibrary() { return _cache; }
private:
	Horizon::Libraries::MapCache _cache;
};
}
}

#endif // HORIZON_TOOLS_MAPCACHE_HPP
