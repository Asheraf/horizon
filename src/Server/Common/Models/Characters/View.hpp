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

#ifndef HORIZON_MODELS_CHARACTERS_VIEW_HPP
#define HORIZON_MODELS_CHARACTERS_VIEW_HPP

#include "Server/Common/Horizon.hpp"
#include "Server/Common/Server.hpp"
#include "Core/Database/MySqlConnection.hpp"

namespace Horizon
{
namespace Models
{
namespace Characters
{
class View
{
public:
	View() {}
	~View() {}

	View(uint16_t hair_style_id, uint16_t hair_color_id)
	: hair_style_id(hair_style_id), hair_color_id(hair_color_id)
	{

	}

	/**
	 * Load all fields from the database into this instance.
	 * @param server    Pointer to the invoking to borrow an sql connection from.
	 * @param char_id   Id of the character to load the view of.
	 * @return true on success, false on failure.
	 */
	bool load(Server *server, uint32_t char_id)
	{
		std::string query = "SELECT * FROM character_view_data WHERE char_id = ?";
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
				setHairStyleID((uint8_t) res->getInt("hair_style_id"));
				setHairColorID((uint16_t) res->getUInt("hair_color_id"));
				setClothColorID((uint16_t) res->getUInt("cloth_color_id"));
				setBodyID((uint16_t) res->getUInt("body_id"));
				setWeaponID((uint16_t) res->getUInt("weapon_id"));
				setShieldID((uint16_t) res->getUInt("shield_id"));
				setHeadTopViewID((uint16_t) res->getUInt("head_top_view_id"));
				setHeadMidViewID((uint16_t) res->getUInt("head_mid_view_id"));
				setHeadBottomViewID((uint16_t) res->getUInt("head_bottom_view_id"));
				setRobeViewID((uint16_t) res->getUInt("robe_view_id"));

				ret = true;
			}

			delete res;
			delete pstmt;
		} catch (sql::SQLException &e) {
			DBLog->error("Models::Characters::Misc::LoadFromDatabase: {}", e.what());
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

		std::string query = "REPLACE INTO `character_view_data` "
			"(`id`, `hair_style_id`, `hair_color_id`, `cloth_color_id`, `body_id`, "
			"`weapon_id`, `shield_id`, `head_top_view_id`, `head_mid_view_id`, `robe_view_id`) "
			"VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?);";

		try {
			sql::PreparedStatement *pstmt = sql->getConnection()->prepareStatement(query);
			pstmt->setInt(1, getCharacterID());
			pstmt->setInt(2, getHairStyleID());
			pstmt->setInt(3, getHairColorID());
			pstmt->setInt(4, getClothColorID());
			pstmt->setInt(5, getBodyID());
			pstmt->setInt(6, getWeaponID());
			pstmt->setInt(7, getShieldID());
			pstmt->setInt(8, getHeadTopViewID());
			pstmt->setInt(9, getHeadMidViewID());
			pstmt->setInt(10, getRobeViewID());
			pstmt->executeUpdate();
			delete pstmt;
		} catch (sql::SQLException &e) {
			DBLog->error("SQLException: {}", e.what());
		}

		server->MySQLUnborrow(sql);
	}

	/* Character Id */
	uint32_t getCharacterID() const { return character_id; }
	void setCharacterID(uint32_t character_id) { View::character_id = character_id; }
	/* Hair Style ID */
	uint8_t getHairStyleID() const { return hair_style_id; }
	void setHairStyleID(uint8_t hair_style_id) { View::hair_style_id = hair_style_id; }
	/* Hair Color ID */
	uint16_t getHairColorID() const { return hair_color_id; }
	void setHairColorID(uint16_t hair_color_id) { View::hair_color_id = hair_color_id; }
	/* Cloth Color ID */
	uint16_t getClothColorID() const { return cloth_color_id; }
	void setClothColorID(uint16_t cloth_color_id) { View::cloth_color_id = cloth_color_id; }
	/* Body ID */
	uint16_t getBodyID() const { return body_id; }
	void setBodyID(uint16_t body_id) { View::body_id = body_id; }
	/* Weapon ID */
	uint16_t getWeaponID() const { return weapon_id; }
	void setWeaponID(uint16_t weapon_id) { View::weapon_id = weapon_id; }
	/* Shield ID */
	uint16_t getShieldID() const { return shield_id; }
	void setShieldID(uint16_t shield_id) { View::shield_id = shield_id; }
	/* Head Top View ID */
	uint16_t getHeadTopViewID() const { return head_top_view_id; }
	void setHeadTopViewID(uint16_t head_top_view_id) { View::head_top_view_id = head_top_view_id; }
	/* Head Mid View ID */
	uint16_t getHeadMidViewID() const { return head_mid_view_id; }
	void setHeadMidViewID(uint16_t head_mid_view_id) { View::head_mid_view_id = head_mid_view_id; }
	/* Head Bottom View ID */
	uint16_t getHeadBottomViewID() const { return head_bottom_view_id; }
	void setHeadBottomViewID(uint16_t head_bottom_view_id) { View::head_bottom_view_id = head_bottom_view_id; }
	/* Robe View ID */
	uint16_t getRobeViewID() const { return robe_view_id; }
	void setRobeViewID(uint16_t robe_view_id) { View::robe_view_id = robe_view_id; }

private:
	uint32_t character_id{0};
	uint8_t hair_style_id{0};
	uint16_t hair_color_id{0};
	uint16_t cloth_color_id{0};
	uint16_t body_id{0};
	uint16_t weapon_id{0};
	uint16_t shield_id{0};
	uint16_t head_top_view_id{0};
	uint16_t head_mid_view_id{0};
	uint16_t head_bottom_view_id{0};
	uint16_t robe_view_id{0};
};
}
}
}
#endif //HORIZON_VIEWDATA_HPP
