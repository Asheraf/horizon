/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 * Copyright (c) 2019 Sagun K. (sagunxp@gmail.com).
 * Copyright (c) 2019 Horizon Dev Team.
 *
 * Base Author - Sagun K. (sagunxp@gmail.com)
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

#include "Character.hpp"

#include "Core/Logging/Logger.hpp"
#include "Server/Common/Server.hpp"
#include "Server/Common/Models/Character/Status.hpp"
#include "Server/Common/Models/Character/Inventory.hpp"

#include <string>
#include <mysqlx/xdevapi.h>

using namespace Horizon::Models::Character;

/**
 * Load all fields from the database into this instance.
 * @param server
 * @param char_id
 * @return
 */
bool Character::load(Server *server, uint32_t char_id)
{
	std::string query = "SELECT `account_id`, `slot`, `name`, `gender`, `deleted_at`,`unban_time`, "
						"`pet_id`, `homun_id`, `elemental_id`, "
						"`partner_aid`, `father_aid`, `mother_aid`, `child_aid`, "
						"`party_id`, `guild_id`, "
						"`rename_count`, `last_unique_id`, `hotkey_row_index`, `change_slot_count`, "
						"`current_map`, `current_x`, `current_y`, `saved_map`, `saved_x`, `saved_y`, "
						"`font`, `show_equip`, `allow_party` "
						"FROM `characters` WHERE id = ?";

	try {
		auto s = server->get_mysql_client()->getSession();
		auto record = s.sql(query).bind(char_id).execute().fetchOne();

		if (record) {
			set_id(char_id);
			set_account_id(record[0]);
			set_slot((uint16_t) record[1].get<int>());
			set_name(record[2].get<std::string>());
			std::string gender = record[3].get<std::string>();
			if (gender.compare("M") == 0)
				set_gender(CHARACTER_GENDER_MALE);
			else if (gender.compare("F") == 0)
				set_gender(CHARACTER_GENDER_FEMALE);

			if (record[4].getType() > 0)
				set_deleted_at(record[4].get<long long>());

			set_unban_time(record[5]);
			set_pet_id(record[6]);
			set_homun_id(record[7]);
			set_elemental_id(record[8]);
			set_partner_aid(record[9]);
			set_father_aid(record[10]);
			set_mother_aid(record[11]);
			set_child_aid(record[12]);
			set_party_id(record[13]);
			set_guild_id(record[14]);
			set_rename_count(record[15].get<int>());
			set_last_unique_id(record[16].get<int64_t>());
			set_hotkey_row_index(record[17].get<int>());
			set_change_slot_count(record[18].get<int>());
			set_current_map(record[19]);
			set_current_x(record[20].get<int>());
			set_current_y(record[21].get<int>());
			set_saved_map(record[22]);
			set_saved_x(record[23].get<int>());
			set_saved_y(record[24].get<int>());
			set_font(record[25].get<int>());
			set_show_equip(record[26].get<int>());
			set_allow_party(record[27].get<int>());

			s.close();
			return true;
		}
		s.close();
	} catch (const mysqlx::Error &e) {
		CoreLog->warn("Character::load: {}", e.what());
	}

	return false;
}

bool Character::load_all(Server *server, uint32_t char_id)
{
	if (!load(server, char_id))
		return false;

	set_status_model(std::make_shared<Status>(char_id));

	if (!get_status_model()->load(server, char_id))
		return false;

	set_inventory_model(std::make_shared<Inventory>(char_id));

	if (!get_inventory_model()->load(server, char_id))
		return false;

	return true;
}

/**
 * @brief Save this model to the database in its current state.
 * @param[in|out] server   instance of the server object used to borrow mysql connections.
 */
bool Character::save(Server *server)
{
	try {
		auto s = server->get_mysql_client()->getSession();
		auto table = s.getDefaultSchema().getTable("characters");
		auto q = table.update()
			.set("account_id", get_account_id())
			.set("slot", get_slot())
			.set("name", get_name())
			.set("online", is_online())
			.set("gender", get_gender() == CHARACTER_GENDER_MALE ? "M" : "F")
			.set("unban_time", get_unban_time())
			.set("pet_id", get_pet_id())
			.set("homun_id", get_homun_id())
			.set("elemental_id", get_elemental_id())
			.set("partner_aid", get_partner_aid())
			.set("father_aid", get_father_aid())
			.set("mother_aid", get_mother_aid())
			.set("child_aid", get_child_aid())
			.set("party_id", get_party_id())
			.set("guild_id", get_guild_id())
			.set("rename_count", get_rename_count())
			.set("last_unique_id", get_last_unique_id())
			.set("hotkey_row_index", get_hotkey_row_index())
			.set("change_slot_count", get_change_slot_count())
			.set("current_map", get_current_map())
			.set("current_x", get_current_x())
			.set("current_y", get_current_y())
			.set("saved_map", get_saved_map())
			.set("saved_x", get_saved_x())
			.set("saved_y", get_saved_y())
			.set("font", get_font())
			.set("show_equip", get_show_equip())
			.set("allow_party", get_allow_party());

		if (get_deleted_at())
			q.set("deleted_at", mysqlx::internal::expr("FROM_UNIXTIME(" + std::to_string(get_deleted_at()) + ")"));

			q.where("id = :id")
			.bind("id", get_id())
			.execute();
		s.close();
		return true;
	} catch (const mysqlx::Error &e) {
		CoreLog->warn("Character::save: {}", e.what());
	}

	return false;
}

bool Character::create(Server *server)
{
	int char_id = 0;
	std::string query = "SELECT `id` FROM `characters` ORDER BY `id` DESC LIMIT 1;";

	try {
		auto s = server->get_mysql_client()->getSession();
		auto record = s.sql(query).execute().fetchOne();

		if (record) {
			char_id = record[0].get<int>() + 1;
		} else {
			char_id = 1;
		}

		set_id(char_id);

		std::string gender = get_gender() == CHARACTER_GENDER_MALE ? "M" : "F";

		auto table = s.getDefaultSchema().getTable("characters");
		table.insert("id", "account_id", "slot", "name", "gender", "unban_time",
					 "pet_id", "homun_id", "elemental_id",
					 "partner_aid", "father_aid", "mother_aid", "child_aid",
					 "party_id", "guild_id",
					 "rename_count", "last_unique_id", "hotkey_row_index", "change_slot_count",
					 "current_map", "current_x", "current_y", "saved_map", "saved_x", "saved_y",
					 "font", "show_equip", "allow_party")
			.values(char_id, get_account_id(), get_slot(), get_name(), gender, get_unban_time(),
					 get_pet_id(), get_homun_id(), get_elemental_id(),
					 get_partner_aid(), get_father_aid(), get_mother_aid(), get_child_aid(),
					 get_party_id(), get_guild_id(),
					 get_rename_count(), get_last_unique_id(), get_hotkey_row_index(), get_change_slot_count(),
					 get_current_map(), get_current_x(), get_current_y(), get_saved_map(), get_saved_x(), get_saved_y(),
					 get_font(), get_show_equip(), get_allow_party())
			.execute();

	} catch (const mysqlx::Error &e) {
		CoreLog->warn("Character::create: {}", e.what());
		return false;
	}

	int save_mask = 0x0;

	set_status_model(std::make_shared<Status>(char_id));
	save_mask |= CHAR_SAVE_STATUS_DATA;

	set_inventory_model(std::make_shared<Inventory>(char_id));
	save_mask |= CHAR_SAVE_INVENTORY_DATA;

	save(server, save_mask);

	return true;
}

uint32_t Character::save(Server *server, uint32_t type)
{
	if ((type & CHAR_SAVE_BASE_DATA) && save(server) == false)
		type &= ~CHAR_SAVE_BASE_DATA;

	if ((type & CHAR_SAVE_STATUS_DATA) && get_status_model()->save(server) == false)
		type &= ~CHAR_SAVE_STATUS_DATA;

	if ((type & CHAR_SAVE_INVENTORY_DATA) && get_inventory_model()->save(server) == false)
		type &= ~CHAR_SAVE_INVENTORY_DATA;

	return type;
}
