/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 *
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

#include "Query.hpp"
#include "Server/Char/Char.hpp"
#include "Server/Char/Socket/CharSocket.hpp"
#include "Server/Common/Models/GameAccount.hpp"
#include "Server/Common/Models/Character/Character.hpp"
#include "Server/Common/Models/Character/Status.hpp"

#include <mysqlx/xdevapi.h>

using namespace Horizon::Models;

Horizon::Char::Database::Query::Query()
{
	InitializeQueryStrings();
}

Horizon::Char::Database::Query::~Query()
{
	//
}

void Horizon::Char::Database::Query::InitializeQueryStrings()
{
	addQueryString(SELECT_ALL_CHARS_BY_AID,
		"SELECT c.id, c.account_id, c.slot, c.name, c.online, c.gender, c.unban_time, "
		"c.font, c.show_equip, c.allow_party, "
	    "c.current_map, c.current_x, c.current_y, c.saved_map, c.saved_x, c.saved_y, "
	    "c.rename_count, c.last_unique_id, c.hotkey_row_index, c.change_slot_count, "
	    "c.party_id, c.guild_id, "
	    "c.partner_aid, c.father_aid, c.mother_aid, c.child_aid, "
	    "c.pet_id, c.homun_id, c.elemental_id, "
		"csd.job_id, csd.base_level, csd.job_level, csd.base_experience, csd.job_experience, "
		"csd.zeny, csd.strength, csd.agility, csd.vitality, csd.intelligence, csd.dexterity, csd.luck, "
		"csd.maximum_hp, csd.hp, csd.maximum_sp, csd.sp, csd.status_points, csd.skill_points, csd.body_state, "
		"csd.virtue, csd.honor, csd.manner, "
		"csd.hair_style_id, csd.hair_color_id, csd.cloth_color_id, csd.body_id, csd.weapon_id, csd.shield_id, "
		"csd.head_top_view_id, csd.head_mid_view_id, csd.head_bottom_view_id, csd.robe_view_id "
		"FROM `characters` c "
		"INNER JOIN `character_status_data` csd ON c.id = csd.id "
		"WHERE c.account_id = ? AND c.deleted_at IS NULL");
	addQueryString(CHECK_EXISTING_CHAR_BY_NAME,
		"SELECT COUNT(*) FROM `characters` WHERE `name` = ?");
}

std::shared_ptr<Character::Character>
Horizon::Char::Database::Query::CreateCharacterModelFromResult(uint32_t account_id, mysqlx::Row record)
{
	int char_id = record[0];

	Character::Character c(char_id);
	Character::Status csd(char_id);

	// Character
	c.set_id(char_id);
	c.set_account_id(account_id);
	c.set_slot(record[2].get<int>());
	c.set_name(record[3]);
	std::string gender = record[5];
	if (gender == "M")
		c.set_gender(CHARACTER_GENDER_MALE);
	else if (gender == "F")
		c.set_gender(CHARACTER_GENDER_FEMALE);
	c.set_font(record[6].get<int>());
	c.set_show_equip(record[7].get<int>());
	c.set_allow_party(record[8].get<int>());
	c.set_unban_time(record[9]);
	c.set_current_map(record[10]);
	c.set_current_x(record[11].get<int>());
	c.set_current_y(record[12].get<int>());
	c.set_saved_map(record[13]);
	c.set_saved_x(record[14].get<int>());
	c.set_saved_y(record[15].get<int>());
	c.set_rename_count(record[16].get<int>());
	c.set_last_unique_id(record[17]);
	c.set_hotkey_row_index(record[18].get<int>());
	c.set_change_slot_count(record[19].get<int>());
	c.set_party_id(record[20]);
	c.set_guild_id(record[21]);
	c.set_partner_aid(record[22]);
	c.set_father_aid(record[23]);
	c.set_mother_aid(record[24]);
	c.set_child_aid(record[25]);
	c.set_pet_id(record[26]);
	c.set_homun_id(record[27]);
	c.set_elemental_id(record[28]);
	// Status
	csd.set_character_id(char_id);
	csd.set_job_id(record[29].get<int>());
	csd.set_base_level(record[30].get<int>());
	csd.set_job_level(record[31].get<int>());
	csd.set_base_exp(record[32]);
	csd.set_job_exp(record[33]);
	csd.set_zeny(record[34]);
	csd.set_strength(record[35].get<int>());
	csd.set_agility(record[36].get<int>());
	csd.set_vitality(record[37].get<int>());
	csd.set_intelligence(record[38].get<int>());
	csd.set_dexterity(record[39].get<int>());
	csd.set_luck(record[40].get<int>());
	csd.set_max_hp(record[41]);
	csd.set_hp(record[42]);
	csd.set_max_sp(record[43]);
	csd.set_sp(record[44]);
	csd.set_status_points(record[45]);
	csd.set_skill_points(record[46]);
	csd.set_body_state(record[47]);
	csd.set_virtue(record[48].get<int>());
	csd.set_honor(record[49]);
	csd.set_manner(record[50].get<int>());
	csd.set_hair_style_id(record[51].get<int>());
	csd.set_hair_color_id(record[52].get<int>());
	csd.set_cloth_color_id(record[53].get<int>());
	csd.set_body_id(record[54].get<int>());
	csd.set_weapon_id(record[55].get<int>());
	csd.set_shield_id(record[56].get<int>());
	csd.set_head_top_view_id(record[57].get<int>());
	csd.set_head_mid_view_id(record[58].get<int>());
	csd.set_head_bottom_view_id(record[59].get<int>());
	csd.set_robe_view_id(record[60].get<int>());

	// Append to character.
	c.set_status_model(std::make_shared<Character::Status>(csd));

	return std::make_shared<Character::Character>(c);
}

int Horizon::Char::Database::Query::load_all_characters_for_account(std::shared_ptr<GameAccount> account)
{
	auto sql_session = CharServer->get_mysql_client()->getSession();

	boost::optional<std::string> query = getQueryString(SELECT_ALL_CHARS_BY_AID);

	if (!query)
		return 0;

	mysqlx::RowResult res = sql_session.sql(*query).bind(account->get_id()).execute();
	mysqlx::Row record;

	while ((record = res.fetchOne())) {
		account->add_character(CreateCharacterModelFromResult(account->get_id(), record));
	}

	sql_session.close();
	return res.count();
}

int Horizon::Char::Database::Query::CheckExistingCharByName(std::string name)
{
	auto sql_session = CharServer->get_mysql_client()->getSession();
	int found = 0;

	boost::optional<std::string> query = getQueryString(CHECK_EXISTING_CHAR_BY_NAME);

	if (!query)
		return -1;

	mysqlx::RowResult res = sql_session.sql(*query).bind(name).execute();
	mysqlx::Row record = res.fetchOne();

	if (record && record[0].get<int>() > 0)
		found = 1;

	return found;
}
