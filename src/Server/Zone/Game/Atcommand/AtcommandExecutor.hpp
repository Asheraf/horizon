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

#ifndef HORIZON_ZONE_GAME_ATCOMMAND_EXECUTOR_HPP
#define HORIZON_ZONE_GAME_ATCOMMAND_EXECUTOR_HPP

#include "AtcommandImpl.hpp"

#include <stdio.h>
#include <cstring>
#include <vector>
#include <memory>

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
class Atcommand;
class AtcommandExecutor
{
public:
	AtcommandExecutor(std::weak_ptr<Entities::Player> player, std::string const &cmd)
	: _player(player), _command(cmd)
	{ }
	~AtcommandExecutor() { }

	std::shared_ptr<Entities::Player> get_player() { return _player.lock(); }
	std::string const &get_cmd() { return _command; }

	bool execute();

	void on_failure(int type = 0);

	void set_atcmd(std::shared_ptr<Atcommand> cmd) { _atcmd = cmd; }
	std::shared_ptr<Atcommand> get_atcmd() { return _atcmd; }

private:
	int execute_internal(std::vector<std::string> const &cmd);
	
	std::weak_ptr<Entities::Player> _player;
	std::string const &_command;
	std::shared_ptr<Atcommand> _atcmd;
};
}
}
}
#endif /* HORIZON_ZONE_GAME_ATCOMMAND_EXECUTOR_HPP */
