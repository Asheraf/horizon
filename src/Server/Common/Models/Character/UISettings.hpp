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
	UISettings() {}
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
	uint32_t get_character_id() const { return character_id; }
	void set_character_id(uint32_t character_id) { UISettings::character_id = character_id; }
	/* Font */
	uint8_t get_font() const { return font; }
	void set_font(uint8_t font) { UISettings::font = font; }
	/* Show Equip */
	uint8_t get_show_equip() const { return show_equip; }
	void set_show_equip(uint8_t show_equip) { UISettings::show_equip = show_equip; }
	/* Allow Party */
	uint8_t get_allow_party() const { return allow_party; }
	void set_allow_party(uint8_t allow_party) { UISettings::allow_party = allow_party; }
private:
	uint32_t character_id{0};
	uint8_t font{0};
	uint8_t show_equip{0};
	uint8_t allow_party{0};
};
}
}
}
#endif // HORIZON_MODELS_CHARACTERS_UISETTINGS_HPP
