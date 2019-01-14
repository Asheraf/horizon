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
		"SELECT * FROM `characters` c "
		"INNER JOIN `character_status_data` csd ON c.id = csd.id "
		"INNER JOIN `character_ui_settings` cus ON c.id = cus.id "
		"INNER JOIN `character_view_data` cvd ON c.id = cvd.id "
		"INNER JOIN `character_position_data` cpd ON c.id = cpd.id "
		"INNER JOIN `character_misc_data` cmd ON c.id = cmd.id "
		"INNER JOIN `character_group_data` cgd ON c.id = cgd.id "
		"INNER JOIN `character_family_data` cfd ON c.id = cfd.id "
		"INNER JOIN `character_companion_data` ccd ON c.id = ccd.id "
		"INNER JOIN `character_access_data` cad ON c.id = cad.id "
		"WHERE c.account_id = ? AND c.deleted = 0");
	addQueryString(CHECK_EXISTING_CHAR_BY_NAME,
		"SELECT * FROM `characters` WHERE `name` = ?");
}

std::shared_ptr<Horizon::Models::Character::Character>
Horizon::Char::Database::Query::CreateCharacterModelFromResult(uint32_t account_id, sql::ResultSet *res)
{
	Horizon::Models::Character::Character c;
	Horizon::Models::Character::Status csd;
	Horizon::Models::Character::UISettings cus;
	Horizon::Models::Character::View cvd;
	Horizon::Models::Character::Position cpd;
	Horizon::Models::Character::Misc cmd;
	Horizon::Models::Character::Group cgd;
	Horizon::Models::Character::Family cfd;
	Horizon::Models::Character::Companion ccd;
	Horizon::Models::Character::Access cad;

	int char_id = res->getInt("id");

	// Character
	c.set_character_id(char_id);
	c.set_account_id(account_id);
	c.set_name(res->getString("name"));
	c.set_slot(res->getInt("slot"));
	std::string gender = res->getString("gender");
	if (gender == "M")
		c.set_gender(CHARACTER_GENDER_MALE);
	else if (gender == "F")
		c.set_gender(CHARACTER_GENDER_FEMALE);
	// Status
	csd.set_character_id(char_id);
	csd.set_job_class(res->getInt("job_class"));
	csd.set_base_level(res->getInt("base_level"));
	csd.set_job_level(res->getInt("job_level"));
	csd.set_base_exp(res->getInt64("base_experience"));
	csd.set_job_exp(res->getInt64("job_experience"));
	csd.set_zeny(res->getInt("zeny"));
	csd.set_strength(res->getInt("strength"));
	csd.set_agility(res->getInt("agility"));
	csd.set_vitality(res->getInt("vitality"));
	csd.set_intelligence(res->getInt("intelligence"));
	csd.set_dexterity(res->getInt("dexterity"));
	csd.set_luck(res->getInt("luck"));
	csd.set_max_hp(res->getInt("maximum_hp"));
	csd.set_hp(res->getInt("hp"));
	csd.set_max_sp(res->getInt("maximum_sp"));
	csd.set_sp(res->getInt("sp"));
	csd.set_status_points(res->getInt("status_points"));
	csd.set_skill_points(res->getInt("skill_points"));
	csd.set_body_state(res->getInt("body_state"));
	csd.set_virtue(res->getInt("virtue"));
	csd.set_honor(res->getInt("honor"));
	csd.set_manner(res->getInt("manner"));
	// UI Settings
	cus.set_character_id(char_id);
	cus.set_font(res->getInt("font"));
	cus.set_show_equip(res->getInt("show_equip"));
	cus.set_allow_party(res->getInt("allow_party"));
	// View
	cvd.set_character_id(char_id);
	cvd.set_hair_style_id(res->getInt("hair_style_id"));
	cvd.set_hair_color_id(res->getInt("hair_color_id"));
	cvd.set_cloth_color_id(res->getInt("cloth_color_id"));
	cvd.set_body_id(res->getInt("body_id"));
	cvd.set_weapon_id(res->getInt("weapon_id"));
	cvd.set_shield_id(res->getInt("shield_id"));
	cvd.set_head_top_view_id(res->getInt("head_top_view_id"));
	cvd.set_head_mid_view_id(res->getInt("head_mid_view_id"));
	cvd.set_head_bottom_view_id(res->getInt("head_bottom_view_id"));
	cvd.set_robe_view_id(res->getInt("robe_view_id"));
	// Position
	cpd.set_character_id(char_id);
	cpd.set_current_map(res->getString("current_map"));
	cpd.set_current_x(res->getInt("current_x"));
	cpd.set_current_y(res->getInt("current_y"));
	cpd.set_saved_map(res->getString("saved_map"));
	cpd.set_saved_x(res->getInt("saved_x"));
	cpd.set_saved_y(res->getInt("saved_y"));
	// Misc
	cmd.set_character_id(char_id);
	cmd.set_rename_count(res->getInt("rename_count"));
	cmd.set_unique_item_counter(res->getInt64("unique_item_counter"));
	cmd.set_hotkey_row_index(res->getInt("hotkey_row_index"));
	cmd.set_change_slot_count(res->getInt("change_slot_count"));
	// Group
	cgd.set_character_id(char_id);
	cgd.set_party_id(res->getInt("party_id"));
	cgd.set_guild_id(res->getInt("guild_id"));
	// Family
	cfd.set_character_id(char_id);
	cfd.set_partner_aid(res->getInt("partner_aid"));
	cfd.set_father_aid(res->getInt("father_aid"));
	cfd.set_mother_aid(res->getInt("mother_aid"));
	cfd.set_child_aid(res->getInt("child_aid"));
	// Companion
	ccd.set_character_id(char_id);
	ccd.set_pet_id(res->getInt("pet_id"));
	ccd.set_homun_id(res->getInt("homun_id"));
	ccd.set_elemental_id(res->getInt("elemental_id"));
	// Access
	cad.set_character_id(char_id);
	cad.set_unban_time(res->getInt("unban_time"));
	cad.set_delete_date(res->getInt("delete_date"));

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
	auto sql = CharServer->mysql_borrow();
	boost::optional<std::string> query = getQueryString(SELECT_ALL_CHARS_BY_AID);
	int results = 0;

	if (!query)
		return 0;

	try {
		sql::PreparedStatement *pstmt = sql->getConnection()->prepareStatement(*query);
		pstmt->setInt(1, account->get_id());
		sql::ResultSet *res = pstmt->executeQuery();

		while (res != nullptr && res->next()) {
			account->add_character(CreateCharacterModelFromResult(account->get_id(), res));
			++results;
		}
		delete pstmt;
		delete res;
	} catch (sql::SQLException &e) {
		DBLog->error("SQLException: {}", e.what());
	}

	CharServer->mysql_unborrow(sql);
	return results;
}

int Horizon::Char::Database::Query::CheckExistingCharByName(std::string name)
{
	auto sql = CharServer->mysql_borrow();
	int found = 0;
	boost::optional<std::string> query = getQueryString(CHECK_EXISTING_CHAR_BY_NAME);

	if (!query)
		return -1;

	try {
		sql::PreparedStatement *pstmt = sql->getConnection()->prepareStatement(*query);
		pstmt->setString(1, name);
		sql::ResultSet *res = pstmt->executeQuery();

		if (res != nullptr && res->next())
			found = 1;

		delete pstmt;
		delete res;
	} catch (sql::SQLException &e) {
		DBLog->error("SQLException: {}", e.what());
	}

	return found;
}
