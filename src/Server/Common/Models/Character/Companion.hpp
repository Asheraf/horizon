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

#ifndef HORIZON_MODELS_CHARACTERS_COMPANION_HPP
#define HORIZON_MODELS_CHARACTERS_COMPANION_HPP

#include "Server/Common/Horizon.hpp"
#include "Server/Common/Server.hpp"
#include "Core/Database/MySqlConnection.hpp"

namespace Horizon
{
namespace Models
{
namespace Character
{
class Companion
{
public:
	Companion() {}
	~Companion() {}

	/**
	 * Load all fields from the database into this instance.
	 * @param server
	 * @param char_id
	 * @return
	 */
	bool load(Server *server, uint32_t char_id)
	{
		std::string query = "SELECT * FROM `character_companion_data` WHERE `id` = ?";
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
				set_pet_id(res->getUInt("pet_id"));
				set_homun_id(res->getUInt("homun_id"));
				set_elemental_id(res->getUInt("elemental_id"));
				ret = true;
			}

			delete res;
			delete pstmt;
		} catch (sql::SQLException &e) {
			DBLog->error("Models::Character::Companion::LoadFromDatabase: {}", e.what());
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

		std::string query = "REPLACE INTO `character_companion_data` "
			"(`id`, `pet_id`, `homun_id`, `elemental_id`) VALUES (?, ?, ?, ?);";

		try {
			sql::PreparedStatement *pstmt = sql->getConnection()->prepareStatement(query);
			pstmt->setInt(1, get_character_id());
			pstmt->setInt(2, get_pet_id());
			pstmt->setInt(3, get_homun_id());
			pstmt->setInt(4, get_elemental_id());
			pstmt->executeUpdate();
			delete pstmt;
		} catch (sql::SQLException &e) {
			DBLog->error("SQLException: {}", e.what());
		}

		server->mysql_unborrow(sql);
	}
	
	/* Character Id */
	uint32_t get_character_id() const { return character_id; }
	void set_character_id(uint32_t character_id) { Companion::character_id = character_id; }
	/* Pet ID */
	uint32_t get_pet_id() const { return pet_id; }
	void set_pet_id(uint32_t pet_id) { Companion::pet_id = pet_id; }
	/* Homun ID */
	uint32_t get_homun_id() const { return homun_id; }
	void set_homun_id(uint32_t homun_id) { Companion::homun_id = homun_id; }
	/* Elemental ID */
	uint32_t get_elemental_id() const { return elemental_id; }
	void set_elemental_id(uint32_t elemental_id) { Companion::elemental_id = elemental_id; }
private:
	uint32_t character_id{0};
	uint32_t pet_id{0};
	uint32_t homun_id{0};
	uint32_t elemental_id{0};
};
}
}
}
#endif // HORIZON_MODELS_CHARACTERS_COMPANION_HPP
