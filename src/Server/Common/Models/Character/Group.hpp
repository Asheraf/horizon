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

#ifndef HORIZON_MODELS_CHARACTERS_GROUP_HPP
#define HORIZON_MODELS_CHARACTERS_GROUP_HPP

#include "Server/Common/Horizon.hpp"
#include "Server/Common/Server.hpp"
#include <mysqlx/xdevapi.h>

namespace Horizon
{
namespace Models
{
namespace Character
{
class Group
{
public:
	Group(uint32_t char_id) : _character_id(char_id) {}

	~Group() {}

	/**
	 * Load all fields from the database into this instance.
	 * @param server
	 * @param char_id
	 * @return
	 */
	bool load(Server *server, uint32_t char_id)
	{
		std::string query = "SELECT `party_id`, `guild_id` FROM `character_group_data` WHERE `id` = ?";

		try {
			auto s = server->get_mysql_client()->getSession();
			auto record = s.sql(query).bind(char_id).execute().fetchOne();

			if (record) {
				set_character_id(char_id);
				set_party_id(record[0]);
				set_guild_id(record[1]);
				s.close();
				return true;
			}
			s.close();
		} catch (const mysqlx::Error &e) {
			CoreLog->warn("Group::load: {}", e.what());
		}

		return false;
	}

	/**
	 * @brief Save this model to the database in its current state.
	 * @param[in|out] server   instance of the server object used to borrow mysql connections.
	 */
	void save(Server *server)
	{
		std::string query = "REPLACE INTO `character_group_data` "
			"(`id`, `party_id`, `guild_id`) VALUES (?, ?, ?);";

		try {
			auto s = server->get_mysql_client()->getSession();
			s.sql(query)
					.bind(get_character_id(),
						  get_party_id(),
						  get_guild_id())
					.execute();
		} catch (const mysqlx::Error &e) {
			CoreLog->warn("Group::save: {}", e.what());
		}
	}

	/* Character ID */
	uint32_t get_character_id() const { return _character_id; }
	void set_character_id(uint32_t character_id) { _character_id = character_id; }
	/* Party ID */
	uint32_t get_party_id() const { return _party_id; }
	void set_party_id(uint32_t party_id) { _party_id = party_id; }
	/* Guild ID */
	uint32_t get_guild_id() const { return _guild_id; }
	void set_guild_id(uint32_t guild_id) { _guild_id = guild_id; }

private:
	uint32_t _character_id{0};
	uint32_t _party_id{0};
	uint32_t _guild_id{0};
};
}
}
}
#endif // HORIZON_MODELS_CHARACTERS_GROUP_HPP
