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

#include "Query.hpp"
#include "Server/Char/Char.hpp"
#include "Server/Char/Socket/CharSocket.hpp"
#include "Server/Common/Models/GameAccount.hpp"
#include "Server/Common/Models/Character/Character.hpp"
#include "Server/Common/Models/Character/Status.hpp"
#include "Server/Common/Models/Character/UISettings.hpp"
#include "Server/Common/Models/Character/View.hpp"
#include "Server/Common/Models/Character/Position.hpp"
#include "Server/Common/Models/Character/Misc.hpp"
#include "Server/Common/Models/Character/Group.hpp"
#include "Server/Common/Models/Character/Family.hpp"
#include "Server/Common/Models/Character/Companion.hpp"
#include "Server/Common/Models/Character/Access.hpp"

#include <mysqlx/xdevapi.h>

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
		"SELECT c.id, c.account_id, c.slot, c.name, c.online, c.gender, c.deleted_at, "
		"csd.job_class, csd.base_level, csd.job_level, csd.base_experience, csd.job_experience, "
		"csd.zeny, csd.strength, csd.agility, csd.vitality, csd.intelligence, csd.dexterity, csd.luck, "
		"csd.maximum_hp, csd.hp, csd.maximum_sp, csd.sp, csd.status_points, csd.skill_points, csd.body_state, "
		"csd.virtue, csd.honor, csd.manner, "
		"cus.font, cus.show_equip, cus.allow_party, "
		"cvd.hair_style_id, cvd.hair_color_id, cvd.cloth_color_id, cvd.body_id, cvd.weapon_id, cvd.shield_id, "
		"cvd.head_top_view_id, cvd.head_mid_view_id, cvd.head_bottom_view_id, cvd.robe_view_id, "
		"cpd.current_map, cpd.current_x, cpd.current_y, cpd.saved_map, cpd.saved_x, cpd.saved_y, "
		"cmd.rename_count, cmd.unique_item_counter, cmd.hotkey_row_index, cmd.change_slot_count, "
		"cgd.party_id, cgd.guild_id, "
		"cfd.partner_aid, cfd.father_aid, cfd.mother_aid, cfd.child_aid, "
		"ccd.pet_id, ccd.homun_id, ccd.elemental_id, "
		"cad.unban_time, cad.delete_date "
		"FROM `characters` c "
		"INNER JOIN `character_status_data` csd ON c.id = csd.id "
		"INNER JOIN `character_ui_settings` cus ON c.id = cus.id "
		"INNER JOIN `character_view_data` cvd ON c.id = cvd.id "
		"INNER JOIN `character_position_data` cpd ON c.id = cpd.id "
		"INNER JOIN `character_misc_data` cmd ON c.id = cmd.id "
		"INNER JOIN `character_group_data` cgd ON c.id = cgd.id "
		"INNER JOIN `character_family_data` cfd ON c.id = cfd.id "
		"INNER JOIN `character_companion_data` ccd ON c.id = ccd.id "
		"INNER JOIN `character_access_data` cad ON c.id = cad.id "
		"WHERE c.account_id = ? AND c.deleted_at IS NULL");
	addQueryString(CHECK_EXISTING_CHAR_BY_NAME,
		"SELECT COUNT(*) FROM `characters` WHERE `name` = ?");
}

std::shared_ptr<Horizon::Models::Character::Character>
Horizon::Char::Database::Query::CreateCharacterModelFromResult(uint32_t account_id, mysqlx::Row record)
{
	int char_id = record[0];

	Horizon::Models::Character::Character c(char_id);
	Horizon::Models::Character::Status csd(char_id);
	Horizon::Models::Character::UISettings cus(char_id);
	Horizon::Models::Character::View cvd(char_id);
	Horizon::Models::Character::Position cpd(char_id);
	Horizon::Models::Character::Misc cmd(char_id);
	Horizon::Models::Character::Group cgd(char_id);
	Horizon::Models::Character::Family cfd(char_id);
	Horizon::Models::Character::Companion ccd(char_id);
	Horizon::Models::Character::Access cad(char_id);

	// Character
	c.set_character_id(char_id);
	c.set_account_id(account_id);
	c.set_name(record[3]);
	c.set_slot(record[2].get<int>());
	std::string gender = record[5];
	if (gender == "M")
		c.set_gender(CHARACTER_GENDER_MALE);
	else if (gender == "F")
		c.set_gender(CHARACTER_GENDER_FEMALE);
	// Status
	csd.set_character_id(char_id);
	csd.set_job_class(record[7].get<int>());
	csd.set_base_level(record[8].get<int>());
	csd.set_job_level(record[9].get<int>());
	csd.set_base_exp(record[10]);
	csd.set_job_exp(record[11]);
	csd.set_zeny(record[12]);
	csd.set_strength(record[13].get<int>());
	csd.set_agility(record[14].get<int>());
	csd.set_vitality(record[15].get<int>());
	csd.set_intelligence(record[16].get<int>());
	csd.set_dexterity(record[17].get<int>());
	csd.set_luck(record[18].get<int>());
	csd.set_max_hp(record[19]);
	csd.set_hp(record[20]);
	csd.set_max_sp(record[21]);
	csd.set_sp(record[22]);
	csd.set_status_points(record[23]);
	csd.set_skill_points(record[24]);
	csd.set_body_state(record[25]);
	csd.set_virtue(record[26].get<int>());
	csd.set_honor(record[27]);
	csd.set_manner(record[28].get<int>());
	// UI Settings
	cus.set_character_id(char_id);
	cus.set_font(record[29].get<int>());
	cus.set_show_equip(record[30].get<int>());
	cus.set_allow_party(record[31].get<int>());
	// View
	cvd.set_character_id(char_id);
	cvd.set_hair_style_id(record[32].get<int>());
	cvd.set_hair_color_id(record[33].get<int>());
	cvd.set_cloth_color_id(record[34].get<int>());
	cvd.set_body_id(record[35].get<int>());
	cvd.set_weapon_id(record[36].get<int>());
	cvd.set_shield_id(record[37].get<int>());
	cvd.set_head_top_view_id(record[38].get<int>());
	cvd.set_head_mid_view_id(record[39].get<int>());
	cvd.set_head_bottom_view_id(record[40].get<int>());
	cvd.set_robe_view_id(record[41].get<int>());
	// Position
	cpd.set_character_id(char_id);
	cpd.set_current_map(record[42]);
	cpd.set_current_x(record[43].get<int>());
	cpd.set_current_y(record[44].get<int>());
	cpd.set_saved_map(record[45]);
	cpd.set_saved_x(record[46].get<int>());
	cpd.set_saved_y(record[47].get<int>());
	// Misc
	cmd.set_character_id(char_id);
	cmd.set_rename_count(record[48].get<int>());
	cmd.set_unique_item_counter(record[49]);
	cmd.set_hotkey_row_index(record[50].get<int>());
	cmd.set_change_slot_count(record[51].get<int>());
	// Group
	cgd.set_character_id(char_id);
	cgd.set_party_id(record[52]);
	cgd.set_guild_id(record[53]);
	// Family
	cfd.set_character_id(char_id);
	cfd.set_partner_aid(record[54]);
	cfd.set_father_aid(record[55]);
	cfd.set_mother_aid(record[56]);
	cfd.set_child_aid(record[57]);
	// Companion
	ccd.set_character_id(char_id);
	ccd.set_pet_id(record[58]);
	ccd.set_homun_id(record[59]);
	ccd.set_elemental_id(record[60]);
	// Access
	cad.set_character_id(char_id);
	cad.set_unban_time(record[61]);
	cad.set_delete_date(record[62]);

	// Append to character.
	c.set_status_data(std::make_shared<Horizon::Models::Character::Status>(csd));
	c.set_ui_settings(std::make_shared<Horizon::Models::Character::UISettings>(cus));
	c.set_view_data(std::make_shared<Horizon::Models::Character::View>(cvd));
	c.set_position_data(std::make_shared<Horizon::Models::Character::Position>(cpd));
	c.set_misc_data(std::make_shared<Horizon::Models::Character::Misc>(cmd));
	c.set_group_data(std::make_shared<Horizon::Models::Character::Group>(cgd));
	c.set_family_data(std::make_shared<Horizon::Models::Character::Family>(cfd));
	c.set_companion_data(std::make_shared<Horizon::Models::Character::Companion>(ccd));
	c.set_access_data(std::make_shared<Horizon::Models::Character::Access>(cad));

	return std::make_shared<Horizon::Models::Character::Character>(c);
}

int Horizon::Char::Database::Query::AllCharactersByAccount(std::shared_ptr<GameAccount> account)
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
