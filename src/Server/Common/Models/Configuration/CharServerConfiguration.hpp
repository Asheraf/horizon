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
	const std::string &getStartMap() const { return _start_map; }
	void setStartMap(std::string const &map) { _start_map = map; }
	/* Start X */
	uint16_t getStartX() const { return _start_x; }
	void setStartX(uint16_t x) { _start_x = x; }
	/* Start Y */
	uint16_t getStartY() const { return _start_y; }
	void setStartY(uint16_t y) { _start_y = y; }
	/* Start Zeny */
	uint32_t getStartZeny() const { return _start_zeny; }
	void setStartZeny(uint32_t zeny) { _start_zeny = zeny; }
	/* Start Items */
	void addStartItem(std::pair<uint32_t, uint32_t> item) { _start_items.push_back(item); }
	std::pair<uint32_t, uint32_t> &getStartItem(std::size_t index) { return _start_items.at(index); }
	std::size_t getStartItemCount() { return _start_items.size(); }

private:
	std::string _start_map{"new_1-1"};
	uint16_t _start_x{53}, _start_y{111};
	uint32_t _start_zeny{0};
	std::vector<std::pair<uint32_t, uint32_t>> _start_items;
};

#endif /* HORIZON_CHARSERVERCONFIGURATION_HPP */
