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

namespace Horizon
{
namespace Models
{
namespace Character
{
class Misc
{
public:
	Misc(uint32_t char_id)
	: _character_id(char_id)
	{ }

	~Misc() { }

	/**
	 * Load all fields from the database into this instance.
	 * @param server
	 * @param char_id
	 * @return
	 */
	bool load(Server *server, uint32_t char_id)
	{
		std::string query = "SELECT `rename_count`, `unique_item_counter`, `hotkey_row_index`, `change_slot_count` FROM `character_misc_data` WHERE `id` = ?";

		try {
			auto s = server->get_mysql_client()->getSession();
			auto record = s.sql(query).bind(char_id).execute().fetchOne();

			if (record) {
				set_character_id(char_id);
				set_rename_count((uint8_t) record[0].get<int>());
				set_unique_item_counter(record[1]);
				set_hotkey_row_index((uint8_t) record[2].get<int>());
				set_change_slot_count((uint8_t) record[3].get<int>());
				s.close();
				return true;
			}
			s.close();
		} catch (const mysqlx::Error &e) {
			CoreLog->warn("Misc::load: {}", e.what());
		}

		return false;
	}

	/**
	 * @brief Save this model to the database in its current state.
	 * @param[in|out] server   instance of the server object used to borrow mysql connections.
	 */
	void save(Server *server)
	{
		std::string query = "REPLACE INTO `character_misc_data` "
			"(`id`, `rename_count`, `unique_item_counter`, `hotkey_row_index`, `change_slot_count`) "
			"VALUES (?, ?, ?, ?, ?);";

		try {
			auto s = server->get_mysql_client()->getSession();
			s.sql(query)
					.bind(get_character_id(),
						  get_rename_count(),
						  get_unique_item_counter(),
						  get_hotkey_row_index(),
						  get_change_slot_count())
					.execute();
			s.close();
		} catch (const mysqlx::Error &e) {
			CoreLog->warn("Misc::save: {}", e.what());
		}
	}

	/* Character ID */
	uint32_t get_character_id() const { return _character_id; }
	void set_character_id(uint32_t character_id) { _character_id = character_id; }
	/* Character Rename Count */
	uint8_t get_rename_count() const { return _rename_count; }
	void set_rename_count(uint8_t rename_count) { _rename_count = rename_count; }
	/* Unique Item Counter */
	uint64_t get_unique_item_counter() const { return _unique_item_counter; }
	void set_unique_item_counter(uint64_t unique_item_counter) { _unique_item_counter = unique_item_counter; }
	/* Hotkey Row Index */
	uint8_t get_hotkey_row_index() const { return _hotkey_row_index; }
	void set_hotkey_row_index(uint8_t hotkey_row_index) { _hotkey_row_index = hotkey_row_index; }
	/* Change Slot Count */
	uint8_t get_change_slot_count() const { return _change_slot_count; }
	void set_change_slot_count(uint8_t change_slot_count) { _change_slot_count = change_slot_count; }
private:
	uint32_t _character_id{0};
	uint8_t _rename_count{0};
	uint64_t _unique_item_counter{0};
	uint8_t _hotkey_row_index{0};
	uint8_t _change_slot_count{0};
};
}
}
}
#endif // HORIZON_MODELS_CHARACTERS_MISCDATA_HPP
