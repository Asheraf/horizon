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

#ifndef HORIZON_MODELS_CHARACTERS_ACCESS_HPP
#define HORIZON_MODELS_CHARACTERS_ACCESS_HPP

#include "Server/Common/Definitions/Horizon.hpp"
#include "Server/Common/Server.hpp"
#include <mysqlx/xdevapi.h>

namespace Horizon
{
namespace Models
{
namespace Character
{
class Access
{
public:
	Access(uint32_t char_id) : _character_id(char_id)
	{}

	~Access() {}

	/**
	 * Load all fields from the database into this instance.
	 * @param server
	 * @param char_id
	 * @return
	 */
	bool load(Server *server, uint32_t char_id)
	{
		try {
			auto s = server->get_mysql_client()->getSession();
			auto record = s.sql("SELECT `unban_time`, `delete_date` FROM character_access_data WHERE id = ?")
					.bind(char_id)
					.execute()
					.fetchOne();

			if (record) {
				set_character_id(char_id);
				set_unban_time(record[0]);
				set_delete_date(record[1]);
				s.close();
				return true;
			}
			s.close();
		} catch (const mysqlx::Error &e) {
			CoreLog->warn("Access::load: {}", e.what());
		}

		return false;
	}

	/**
	 * @brief Save this model to the database in its current state.
	 * @param[in|out] server   instance of the server object used to borrow mysql connections.
	 */
	void save(Server *server)
	{
		std::string query = "REPLACE INTO `character_access_data` (`id`, `unban_time`, `delete_date`) VALUES (?, ?, ?);";

		try {
			auto s = server->get_mysql_client()->getSession();
			s.sql(query).bind(get_character_id(), get_unban_time(), get_delete_date()).execute();
			s.close();
		} catch (const mysqlx::Error &e) {
			CoreLog->warn("Access::save: {}", e.what());
		}
	}

	/* Char ID */
	uint32_t get_character_id() const { return _character_id; }
	void set_character_id(uint32_t character_id) { _character_id = character_id; }
	/* Unban Time */
	uint32_t get_unban_time() const { return _unban_time; }
	void set_unban_time(uint32_t unban_time) { _unban_time = unban_time; }
	/* Account Delete Date */
	uint32_t get_delete_date() const { return _delete_date; }
	void set_delete_date(uint32_t delete_date) { _delete_date = delete_date; }

private:
	uint32_t _character_id{0};        ///< Character ID
	uint32_t _unban_time{0};          ///< Time until character is unbanned.
	uint32_t _delete_date{0};         ///< Date when the character may be deleted, if set for deletion.
};
}
}
}
#endif // HORIZON_MODELS_CHARACTERS_ACCESS_HPP
