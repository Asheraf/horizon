/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 * Copyright (c) 2019 Horizon Dev Team.
 *
 * Base Author - Sagun Khosla. (sagunxp@gmail.com)
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

#ifndef HORIZON_ZONE_GAME_ATCOMMANDIMPL_HPP
#define HORIZON_ZONE_GAME_ATCOMMANDIMPL_HPP

#include "Server/Zone/Game/Map/Grid/GridDefinitions.hpp"
#include <stdio.h>
#include <string>
#include <boost/smart_ptr.hpp>

namespace Horizon
{
namespace Zone
{
namespace Game
{
	namespace Entities
	{
		class Player;
	}
class Atcommand
{
public:
	Atcommand() { }
	~Atcommand() { }

	virtual int execute() = 0;

	virtual std::string help(int type = 1) = 0;
};
class AtcommandMapMove : public Atcommand
{
public:
	AtcommandMapMove()
	{ }

	int execute();

	void set_map_name(std::string const &map_name) { _map_name = map_name; }
	void set_map_coords(MapCoords coords) { _coords = coords; }
	void set_player(boost::weak_ptr<Entities::Player> p) { _player = p; };
	boost::shared_ptr<Entities::Player> get_player() { return _player.lock(); }

	std::string help(int type = 1)
	{
		switch (type)
		{
		case 1: return "usage: @<movemap|mapmove|warp> <map_name> [optional: <x, y>]";
		case 2: return "Map " + _map_name + " was not found.";
		default: return std::string("Moving to map '%s'.", _map_name.c_str());
		}
	}

private:
	std::string _map_name;
	MapCoords _coords;
	boost::weak_ptr<Entities::Player> _player;
};
}
}
}

#endif /* AtcommandImpl_hpp */
