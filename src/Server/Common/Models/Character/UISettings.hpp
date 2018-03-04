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
		std::string query = "SELECT * FROM character_ui_settings WHERE char_id = ?";
		auto sql = server->MySQLBorrow();
		bool ret = false;

		try {
			sql::PreparedStatement *pstmt = sql->getConnection()->prepareStatement(query);
			pstmt->setInt(1, char_id);
			sql::ResultSet *res = pstmt->executeQuery();

			if (res != nullptr && res->next()) {
				/**
				 * Create Game Account Data
				 */
				setCharacterID(char_id);
				setFont((uint8_t) res->getUInt("font"));
				setShowEquip((uint8_t) res->getUInt("show_equip"));
				setAllowParty((uint8_t) res->getUInt("allow_party"));

				ret = true;
			}

			delete res;
			delete pstmt;
		} catch (sql::SQLException &e) {
			DBLog->error("Models::Character::Misc::LoadFromDatabase: {}", e.what());
		}

		server->MySQLUnborrow(sql);

		return ret;
	}

	/**
	 * @brief Save this model to the database in its current state.
	 * @param[in|out] server   instance of the server object used to borrow mysql connections.
	 */
	void save(Server *server)
	{
		auto sql = server->MySQLBorrow();

		std::string query = "REPLACE INTO `character_ui_settings` "
		"(`id`, `font`, `show_equip`, `allow_party`) VALUES (?, ?, ?, ?);";

		try {
			sql::PreparedStatement *pstmt = sql->getConnection()->prepareStatement(query);
			pstmt->setInt(1, getCharacterID());
			pstmt->setInt(2, getFont());
			pstmt->setInt(3, getShowEquip());
			pstmt->setInt(4, getAllowParty());
			pstmt->executeUpdate();
			delete pstmt;
		} catch (sql::SQLException &e) {
			DBLog->error("SQLException: {}", e.what());
		}

		server->MySQLUnborrow(sql);
	}

	/* Character ID */
	uint32_t getCharacterID() const { return character_id; }
	void setCharacterID(uint32_t character_id) { UISettings::character_id = character_id; }
	/* Font */
	uint8_t getFont() const { return font; }
	void setFont(uint8_t font) { UISettings::font = font; }
	/* Show Equip */
	uint8_t getShowEquip() const { return show_equip; }
	void setShowEquip(uint8_t show_equip) { UISettings::show_equip = show_equip; }
	/* Allow Party */
	uint8_t getAllowParty() const { return allow_party; }
	void setAllowParty(uint8_t allow_party) { UISettings::allow_party = allow_party; }
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
