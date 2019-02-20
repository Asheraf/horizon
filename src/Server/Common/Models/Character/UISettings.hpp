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

#ifndef HORIZON_MODELS_CHARACTERS_UISETTINGS_HPP
#define HORIZON_MODELS_CHARACTERS_UISETTINGS_HPP

#include "Server/Common/Horizon.hpp"
#include "Server/Common/Server.hpp"

namespace Horizon
{
namespace Models
{
namespace Character
{
class UISettings
{
public:
	UISettings(uint32_t char_id)
	: _character_id(char_id)
	{ }

	~UISettings() {}

	/**
	 * Load all fields from the database into this instance.
	 * @param server
	 * @param char_id
	 * @return
	 */
	bool load(Server *server, uint32_t char_id)
	{
		std::string query = "SELECT `font`, `show_equip`, `allow_party` FROM `character_ui_settings` WHERE `id` = ?";

		try {
			auto s = server->get_mysql_client()->getSession();
			auto record = s.sql(query).bind(char_id).execute().fetchOne();

			if (record) {
				set_character_id(char_id);
				set_font((uint8_t) record[0].get<int>());
				set_show_equip((uint8_t) record[1].get<int>());
				set_allow_party((uint8_t)  record[2].get<int>());
				return true;
			}
		} catch (const mysqlx::Error &e) {
			CoreLog->warn("UISettings::load: {}", e.what());
		}

		return false;
	}

	/**
	 * @brief Save this model to the database in its current state.
	 * @param[in|out] server   instance of the server object used to borrow mysql connections.
	 */
	void save(Server *server)
	{
		std::string query = "REPLACE INTO `character_ui_settings` "
		"(`id`, `font`, `show_equip`, `allow_party`) VALUES (?, ?, ?, ?);";

		try {
			auto s = server->get_mysql_client()->getSession();

			s.sql(query)
					.bind(get_character_id(),
						  get_font(),
						  get_show_equip(),
						  get_allow_party())
					.execute();
		} catch (const mysqlx::Error &e) {
			CoreLog->warn("UISettings::save: {}", e.what());
		}
	}

	/* Character ID */
	uint32_t get_character_id() const { return _character_id; }
	void set_character_id(uint32_t character_id) { _character_id = character_id; }
	/* Font */
	uint8_t get_font() const { return _font; }
	void set_font(uint8_t font) { _font = font; }
	/* Show Equip */
	uint8_t get_show_equip() const { return _show_equip; }
	void set_show_equip(uint8_t show_equip) { _show_equip = show_equip; }
	/* Allow Party */
	uint8_t get_allow_party() const { return _allow_party; }
	void set_allow_party(uint8_t allow_party) { _allow_party = allow_party; }
private:
	uint32_t _character_id{0};
	uint8_t _font{0};
	uint8_t _show_equip{0};
	uint8_t _allow_party{0};
};
}
}
}
#endif // HORIZON_MODELS_CHARACTERS_UISETTINGS_HPP
