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

#ifndef HORIZON_ZONE_GAME_GRIDOBJECT_HPP
#define HORIZON_ZONE_GAME_GRIDOBJECT_HPP

#include "Server/Zone/Game/Map/Grid/GridRefManager.hpp"
#include "Server/Zone/Game/Map/Grid/GridReference.hpp"

namespace Horizon
{
namespace Zone
{
template<class T>
class GridObject
{
public:
	virtual ~GridObject() { }

	bool has_valid_grid_reference() const { return _ref.is_valid(); }
	void add_grid_reference(GridRefManager<T> &m) { assert(!has_valid_grid_reference()); _ref.link(&m, (T*) this); }
	void remove_grid_reference() { assert(has_valid_grid_reference()); _ref.remove(); }

	GridReference<T> &get_reference() { return _ref; }

private:
	GridReference<T> _ref;
};
}
}

#endif /* HORIZON_ZONE_GAME_GRIDOBJECT_HPP */
