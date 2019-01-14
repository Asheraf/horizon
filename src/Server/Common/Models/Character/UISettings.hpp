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
#include "Core/Database/MySqlConnection.hpp"

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
		std::string query = "SELECT * FROM `character_ui_settings` WHERE `id` = ?";
		auto sql = server->mysql_borrow();
		bool ret = false;

		try {
			sql::PreparedStatement *pstmt = sql->getConnection()->prepareStatement(query);
			pstmt->setInt(1, char_id);
			sql::ResultSet *res = pstmt->executeQuery();

			if (res != nullptr && res->next()) {
				/**
				 * Create Game Account Data
				 */
				set_character_id(char_id);
				set_font((uint8_t) res->getUInt("font"));
				set_show_equip((uint8_t) res->getUInt("show_equip"));
				set_allow_party((uint8_t) res->getUInt("allow_party"));

				ret = true;
			}

			delete res;
			delete pstmt;
		} catch (sql::SQLException &e) {
			DBLog->error("Models::Character::Misc::LoadFromDatabase: {}", e.what());
		}

		server->mysql_unborrow(sql);

		return ret;
	}

	/**
	 * @brief Save this model to the database in its current state.
	 * @param[in|out] server   instance of the server object used to borrow mysql connections.
	 */
	void save(Server *server)
	{
		auto sql = server->mysql_borrow();

		std::string query = "REPLACE INTO `character_ui_settings` "
		"(`id`, `font`, `show_equip`, `allow_party`) VALUES (?, ?, ?, ?);";

		try {
			sql::PreparedStatement *pstmt = sql->getConnection()->prepareStatement(query);
			pstmt->setInt(1, get_character_id());
			pstmt->setInt(2, get_font());
			pstmt->setInt(3, get_show_equip());
			pstmt->setInt(4, get_allow_party());
			pstmt->executeUpdate();
			delete pstmt;
		} catch (sql::SQLException &e) {
			DBLog->error("SQLException: {}", e.what());
		}

		server->mysql_unborrow(sql);
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
