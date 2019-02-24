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
 * Base Author - Sxyz (sagunxp@gmail.com)
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

#include "AtcommandExecutor.hpp"
#include "Server/Zone/Game/Entities/Unit/Player/Player.hpp"
#include <boost/algorithm/string.hpp>

using namespace Horizon::Zone::Game;
using namespace Horizon::Zone::Game::Entities;

bool AtcommandExecutor::execute()
{
	std::vector<std::string> parts;
	boost::split(parts, get_cmd(), boost::is_any_of(" "));

	int ret = execute_internal(parts);
	if (ret != 0) {
		on_failure(ret);
		return false;
	}

	return true;
}

void AtcommandExecutor::on_failure(int type)
{
	if (get_atcmd())
		get_player()->get_packet_handler()->Send_ZC_NOTIFY_PLAYERCHAT(get_atcmd()->help(type));
	return;
}

int AtcommandExecutor::execute_internal(std::vector<std::string> const &cmd)
{
	if (cmd.size() < 1)
		return -1;

	try {
		std::string const &name = cmd[0];

		if (!name.compare("mapmove") || !name.compare("warp") || !name.compare("movemap") || !name.compare("jump")) {
			auto atcmd = std::make_shared<AtcommandMapMove>();
			set_atcmd(std::dynamic_pointer_cast<Atcommand>(atcmd));
			try {
				atcmd->set_player(get_player());
				atcmd->set_map_name(cmd.size() > 1 ? cmd.at(1) : get_player()->get_map()->get_name());
				if (cmd.size() > 2)
					atcmd->set_map_coords({ (uint16_t) std::stoi(cmd.at(2)), (uint16_t) std::stoi(cmd.at(3)) });
				return atcmd->execute();
			} catch (std::exception &err) {
				return 1;
			}
		}
	} catch (std::exception &err) {
		set_atcmd(std::shared_ptr<Atcommand>());
		return -1;
	}

	return 0;
}

