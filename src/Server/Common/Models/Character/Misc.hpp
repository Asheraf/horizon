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

#ifndef HORIZON_MODELS_CHARACTERS_MISCDATA_HPP
#define HORIZON_MODELS_CHARACTERS_MISCDATA_HPP

#include "Server/Common/Horizon.hpp"
#include "Server/Common/Server.hpp"
#include "Core/Database/MySqlConnection.hpp"

namespace Horizon
{
namespace Models
{
namespace Character
{
class Misc
{
public:
	Misc() {}
	~Misc() {}

	/**
	 * Load all fields from the database into this instance.
	 * @param server
	 * @param char_id
	 * @return
	 */
	bool load(Server *server, uint32_t char_id)
	{
		std::string query = "SELECT * FROM `character_misc_data` WHERE `id` = ?";
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
				set_rename_count((uint8_t) res->getUInt("rename_count"));
				set_unique_item_counter(res->getUInt("unique_item_counter"));
				set_hotkey_row_index((uint16_t) res->getUInt("hotkey_row_index"));
				set_change_slot_count((uint8_t) res->getUInt("change_slot_count"));
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

		std::string query = "REPLACE INTO `character_misc_data` "
			"(`id`, `rename_count`, `unique_item_counter`, `hotkey_row_index`, `change_slot_count`) "
			"VALUES (?, ?, ?, ?, ?);";

		try {
			sql::PreparedStatement *pstmt = sql->getConnection()->prepareStatement(query);
			pstmt->setInt(1, get_character_id());
			pstmt->setInt(2, get_rename_count());
			pstmt->setInt64(3, get_unique_item_counter());
			pstmt->setInt(4, get_hotkey_row_index());
			pstmt->setInt(5, get_change_slot_count());
			pstmt->executeUpdate();
			delete pstmt;
		} catch (sql::SQLException &e) {
			DBLog->error("SQLException: {}", e.what());
		}

		server->mysql_unborrow(sql);
	}

	/* Character ID */
	uint32_t get_character_id() const { return character_id; }
	void set_character_id(uint32_t character_id) { Misc::character_id = character_id; }
	/* Character Rename Count */
	uint8_t get_rename_count() const { return rename_count; }
	void set_rename_count(uint8_t rename_count) { Misc::rename_count = rename_count; }
	/* Unique Item Counter */
	uint64_t get_unique_item_counter() const { return unique_item_counter; }
	void set_unique_item_counter(uint64_t unique_item_counter) { Misc::unique_item_counter = unique_item_counter; }
	/* Hotkey Row Index */
	uint8_t get_hotkey_row_index() const { return hotkey_row_index; }
	void set_hotkey_row_index(uint8_t hotkey_row_index) { Misc::hotkey_row_index = hotkey_row_index; }
	/* Change Slot Count */
	uint8_t get_change_slot_count() const { return change_slot_count; }
	void set_change_slot_count(uint8_t change_slot_count) { Misc::change_slot_count = change_slot_count; }
private:
	uint32_t character_id{0};
	uint8_t rename_count{0};
	uint64_t unique_item_counter{0};
	uint8_t hotkey_row_index{0};
	uint8_t change_slot_count{0};
};
}
}
}
#endif // HORIZON_MODELS_CHARACTERS_MISCDATA_HPP
