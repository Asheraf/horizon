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

#ifndef HORIZON_CHARSERVERCONFIGURATION_HPP
#define HORIZON_CHARSERVERCONFIGURATION_HPP

#include <utility>
#include <vector>
#include <string>

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

#endif /* HORIZON_CHARSERVERCONFIGURATION_HPP */
