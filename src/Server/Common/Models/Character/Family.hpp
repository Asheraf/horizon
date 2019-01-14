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

#ifndef HORIZON_MODELS_CHARACTERS_FAMILY_HPP
#define HORIZON_MODELS_CHARACTERS_FAMILY_HPP

#include "Server/Common/Horizon.hpp"
#include "Server/Common/Server.hpp"
#include "Core/Database/MySqlConnection.hpp"

namespace Horizon
{
namespace Models
{
namespace Character
{
class Family
{
public:
	Family() {}
	~Family() {}

	/**
	 * Load all fields from the database into this instance.
	 * @param server
	 * @param char_id
	 * @return
	 */
	bool load(Server *server, uint32_t char_id)
	{
		std::string query = "SELECT * FROM `character_family_data` WHERE `id` = ?";
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
				set_partner_aid(res->getUInt("partner_aid"));
				set_father_aid(res->getUInt("father_aid"));
				set_mother_aid(res->getUInt("mother_aid"));
				set_child_aid(res->getUInt("child_aid"));
				ret = true;
			}

			delete res;
			delete pstmt;
		} catch (sql::SQLException &e) {
			DBLog->error("Models::Character::Family::LoadFromDatabase: {}", e.what());
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

		std::string query = "REPLACE INTO `character_family_data` "
			"(`id`, `partner_aid`, `father_aid`, `mother_aid`, `child_aid`) VALUES (?, ?, ?, ?, ?);";

		try {
			sql::PreparedStatement *pstmt = sql->getConnection()->prepareStatement(query);
			pstmt->setInt(1, get_character_id());
			pstmt->setInt(2, get_partner_aid());
			pstmt->setInt(3, get_father_aid());
			pstmt->setInt(4, get_mother_aid());
			pstmt->setInt(5, get_child_aid());
			pstmt->executeUpdate();
			delete pstmt;
		} catch (sql::SQLException &e) {
			DBLog->error("SQLException: {}", e.what());
		}

		server->mysql_unborrow(sql);
	}

	/* Character Id */
	uint32_t get_character_id() const { return character_id; }
	void set_character_id(uint32_t character_id) { Family::character_id = character_id; }
	/* Parter Account ID */
	uint32_t get_partner_aid() const { return parter_aid; }
	void set_partner_aid(uint32_t parter_aid) { Family::parter_aid = parter_aid; }
	/* Father Account ID */
	uint32_t get_father_aid() const { return father_aid; }
	void set_father_aid(uint32_t father_aid) { Family::father_aid = father_aid; }
	/* Mother Account ID */
	uint32_t get_mother_aid() const { return mother_aid; }
	void set_mother_aid(uint32_t mother_aid) { Family::mother_aid = mother_aid; }
	/* Child Account ID */
	uint32_t get_child_aid() const { return child_aid; }
	void set_child_aid(uint32_t child_aid) { Family::child_aid = child_aid; }

private:
	uint32_t character_id{0};
	uint32_t parter_aid{0};
	uint32_t father_aid{0};
	uint32_t mother_aid{0};
	uint32_t child_aid{0};
};
}
}
}
#endif // HORIZON_MODELS_CHARACTERS_FAMILY_HPP
