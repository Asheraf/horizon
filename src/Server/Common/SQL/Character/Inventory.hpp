/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
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

#ifndef HORIZON_MODELS_CHARACTERS_INVENTORY_HPP
#define HORIZON_MODELS_CHARACTERS_INVENTORY_HPP

#include "Server/Common/Definitions/ItemDefinitions.hpp"

#include <cstdint>
#include <vector>
#include <memory>

class Server;

namespace Horizon
{
namespace Models
{
namespace Character
{
class Inventory
{
public:
	Inventory(uint32_t char_id) : _character_id(char_id) {}

	~Inventory() {}

//	/**
//	 * Load all fields from the database into this instance.
//	 * @param server
//	 * @param char_id
//	 * @return
//	 */
//	bool load(Server *server, uint32_t char_id);
//
//	/**
//	 * @brief Save this model to the database in its current state.
//	 * @param[in|out] server   instance of the server object used to borrow mysql connections.
//	 */
//	bool save(Server *server);
//
//	/* Character ID */
//	uint32_t get_character_id() const { return _character_id; }
//	void set_character_id(uint32_t character_id) { _character_id = character_id; }
//
//	std::vector<item_entry_data> &get_model_items() { return _inventory; }

private:
	uint32_t _character_id{0};
	std::vector<item_entry_data> _inventory;
};
}
}
}
#endif // HORIZON_MODELS_CHARACTERS_INVENTORY_HPP
