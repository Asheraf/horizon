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

#ifndef HORIZON_CHAR_CHARMAIN_HPP
#define HORIZON_CHAR_CHARMAIN_HPP

#include "Core/Multithreading/TaskScheduler/TaskScheduler.hpp"
#include "Server/Common/Server.hpp"

#include <string>

namespace Horizon
{
namespace Char
{
class CharServer : public Server
{
	
enum character_server_type : uint16_t
{
	CHAR_SERVER_TYPE_NORMAL,
	CHAR_SERVER_TYPE_MAINTENANCE,
	CHAR_SERVER_TYPE_OVER18,
	CHAR_SERVER_TYPE_PAYING,
	CHAR_SERVER_TYPE_FREE2PLAY,
	CHAR_SERVER_TYPE_MAX,
};
	
struct character_server_configuration
{
	/* Start Map */
	const std::string &get_start_map() const { return _start_map; }
	void set_start_map(std::string const &map) { _start_map = map; }
	/* Start X */
	uint16_t get_start_x() const { return _start_x; }
	void set_start_x(uint16_t x) { _start_x = x; }
	/* Start Y */
	uint16_t get_start_y() const { return _start_y; }
	void set_start_y(uint16_t y) { _start_y = y; }
	/* Start Zeny */
	uint32_t get_start_zeny() const { return _start_zeny; }
	void set_start_zeny(uint32_t zeny) { _start_zeny = zeny; }
	/* Start Items */
	void add_start_item(std::pair<uint32_t, uint32_t> item) { _start_items.push_back(item); }
	std::pair<uint32_t, uint32_t> &get_start_item(std::size_t index) { return _start_items.at(index); }
	std::size_t get_start_item_count() { return _start_items.size(); }
	/* Character Deletion Time */
	time_t get_character_deletion_time() const { return _character_deletion_time; }
	void set_character_deletion_time(time_t time) { _character_deletion_time = time; }
	/* Zone Server IP */
	const std::string &get_zone_server_ip() const { return _zone_server_ip; }
	void set_zone_server_ip(std::string const &ip) { _zone_server_ip = ip; }
	/* Zone Server Port */
	uint16_t get_zone_server_port() const { return _zone_server_port; }
	void set_zone_server_port(uint16_t port) { _zone_server_port = port; }
	
private:
	std::string _start_map{"new_1-1"};
	uint16_t _start_x{53}, _start_y{111};
	uint32_t _start_zeny{0};
	std::vector<std::pair<uint32_t, uint32_t>> _start_items;
	time_t _character_deletion_time;
	std::string _zone_server_ip;
	uint16_t _zone_server_port;
};
	
public:
	CharServer();
	~CharServer();

	static CharServer *getInstance()
	{
		static CharServer instance;
		return &instance;
	}

	bool ReadConfig();
	void initialize_cli_commands();

	void initialize_core();

	character_server_configuration &get_char_config() { return _char_server_config; }

	TaskScheduler &get_task_scheduler() { return _task_scheduler; }

private:
	character_server_configuration _char_server_config;
	TaskScheduler _task_scheduler;
};
}
}

#define sChar Horizon::Char::CharServer::getInstance()

#endif //HORIZON_CHAR_CHARMAIN_HPP
