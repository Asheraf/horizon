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

#include <mysqlx/xdevapi.h>

namespace Horizon
{
namespace Models
{
namespace Character
{
class Companion
{
public:
	Companion(uint32_t char_id) : _character_id(char_id)
	{}

	~Companion() {}

	/**
	 * Load all fields from the database into this instance.
	 * @param server
	 * @param char_id
	 * @return
	 */
	bool load(Server *server, uint32_t char_id)
	{
		std::string query = "SELECT `pet_id`, `homun_id`, `elemental_id` FROM `character_companion_data` WHERE `id` = ?";

		try {
			auto s = server->get_mysql_client()->getSession();
			auto record = s.sql(query).bind(char_id).execute().fetchOne();

			if (record) {
				set_character_id(char_id);
				set_pet_id(record[0]);
				set_homun_id(record[1]);
				set_elemental_id(record[2]);
				s.close();
				return true;
			}
			s.close();
		} catch (const mysqlx::Error &e) {
			CoreLog->warn("Companion::load: {}", e.what());
		}

		return false;
	}

	/**
	 * @brief Save this model to the database in its current state.
	 * @param[in|out] server   instance of the server object used to borrow mysql connections.
	 */
	void save(Server *server)
	{
		std::string query = "REPLACE INTO `character_companion_data` (`id`, `pet_id`, `homun_id`, `elemental_id`) VALUES (?, ?, ?, ?);";

		try {
			auto s = server->get_mysql_client()->getSession();
			s.sql(query).bind(get_character_id(), get_pet_id(), get_homun_id(), get_elemental_id()).execute();
			s.close();
		} catch (const mysqlx::Error &e) {
			CoreLog->warn("Companion::save: {}", e.what());
		}
	}
	
	/* Character Id */
	uint32_t get_character_id() const { return _character_id; }
	void set_character_id(uint32_t character_id) { _character_id = character_id; }
	/* Pet ID */
	uint32_t get_pet_id() const { return _pet_id; }
	void set_pet_id(uint32_t pet_id) { _pet_id = pet_id; }
	/* Homun ID */
	uint32_t get_homun_id() const { return _homun_id; }
	void set_homun_id(uint32_t homun_id) { _homun_id = homun_id; }
	/* Elemental ID */
	uint32_t get_elemental_id() const { return _elemental_id; }
	void set_elemental_id(uint32_t elemental_id) { _elemental_id = elemental_id; }

private:
	uint32_t _character_id{0};
	uint32_t _pet_id{0};
	uint32_t _homun_id{0};
	uint32_t _elemental_id{0};
};
}
}
}
#endif // HORIZON_MODELS_CHARACTERS_COMPANION_HPP
