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

#include "SessionData.hpp"

#include "Server/Common/Server.hpp"

#include <ctime>

using namespace Horizon::Models;

///**
// * Load all fields from the database into this instance.
// * @param server
// * @param char_id
// * @return
// */
//bool SessionData::load(Server *server, uint32_t game_account_id)
//{
//	std::string query = "SELECT `auth_code`, `client_version`, `client_type`, `character_slots`, `group_id`, `connect_time` FROM `session_data` WHERE game_account_id = ?";
//
//	try {
//		auto s = server->get_mysql_client()->getSession();
//		auto record = s.sql(query).bind(game_account_id).execute().fetchOne();
//
//		if (record) {
//			set_game_account_id(game_account_id);
//			set_auth_code(record[0].get<int>());
//			set_client_version(record[1].get<int>());
//			set_client_type(record[2].get<int>());
//			set_character_slots(record[3].get<int>());
//			set_group_id(record[4].get<int>());
//			set_connect_time(record[5].get<int>());
//
//			s.close();
//			return true;
//		}
//		s.close();
//	} catch (const mysqlx::Error &e) {
//		HLog(warn) <<"SessionData::load: {}", e.what());
//	}
//
//	return false;
//}
//
//bool SessionData::save(Server *server)
//{
//	std::string query = "REPLACE INTO `session_data` (`auth_code`, `game_account_id`, `client_version`, `client_type`, `character_slots`, `group_id`, `connect_time`) VALUES (?, ?, ?, ?, ?, ?, ?)";
//
//	try {
//		auto s = server->get_mysql_client()->getSession();
//		s.sql(query).bind(get_auth_code(),
//						  get_game_account_id(),
//						  get_client_version(),
//						  get_client_type(),
//						  get_character_slots(),
//						  get_group_id(),
//						  get_connect_time())
//		.execute();
//		s.close();
//		return true;
//	} catch (const mysqlx::Error &e) {
//		HLog(warn) <<"SessionData::save: {}", e.what());
//	}
//
//	return false;
//}
//
//bool SessionData::remove(Server *server)
//{
//	std::string query = "DELETE FROM `session_data` WHERE game_account_id = ?";
//
//	try {
//		auto s = server->get_mysql_client()->getSession();
//		s.sql(query).bind(get_game_account_id()).execute();
//		s.close();
//		return true;
//	} catch (const mysqlx::Error &e) {
//		HLog(warn) <<"SessionData::remove: {}", e.what());
//	}
//	return false;
//}
