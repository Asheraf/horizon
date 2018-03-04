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
#include "Server/Char/Session/Session.hpp"
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

std::shared_ptr<Horizon::Models::Characters::Character>
Horizon::Char::Database::Query::CreateCharacterModelFromResult(uint32_t account_id, sql::ResultSet *res)
{
	Horizon::Models::Characters::Character c;
	Horizon::Models::Characters::Status csd;
	Horizon::Models::Characters::UISettings cus;
	Horizon::Models::Characters::View cvd;
	Horizon::Models::Characters::Position cpd;
	Horizon::Models::Characters::Misc cmd;
	Horizon::Models::Characters::Group cgd;
	Horizon::Models::Characters::Family cfd;
	Horizon::Models::Characters::Companion ccd;
	Horizon::Models::Characters::Access cad;

	int char_id = res->getInt("id");

	// Character
	c.setCharacterID(char_id);
	c.setAccountID(account_id);
	c.setName(res->getString("name"));
	c.setSlot(res->getInt("slot"));
	std::string gender = res->getString("gender");
	if (gender == "M")
		c.setGender(CHARACTER_GENDER_MALE);
	else if (gender == "F")
		c.setGender(CHARACTER_GENDER_FEMALE);
	// Status
	csd.setCharacterID(char_id);
	csd.setJobClass(res->getInt("job_class"));
	csd.setBaseLevel(res->getInt("base_level"));
	csd.setJobLevel(res->getInt("job_level"));
	csd.setBaseExperience(res->getInt64("base_experience"));
	csd.setJobExperience(res->getInt64("job_experience"));
	csd.setZeny(res->getInt("zeny"));
	csd.setStrength(res->getInt("strength"));
	csd.setAgility(res->getInt("agility"));
	csd.setVitality(res->getInt("vitality"));
	csd.setIntelligence(res->getInt("intelligence"));
	csd.setDexterity(res->getInt("dexterity"));
	csd.setLuck(res->getInt("luck"));
	csd.setMaximumHP(res->getInt("maximum_hp"));
	csd.setHP(res->getInt("hp"));
	csd.setMaximumSP(res->getInt("maximum_sp"));
	csd.setSP(res->getInt("sp"));
	csd.setStatusPoints(res->getInt("status_points"));
	csd.setSkillPoints(res->getInt("skill_points"));
	csd.setBodyState(res->getInt("body_state"));
	csd.setVirtue(res->getInt("virtue"));
	csd.setHonor(res->getInt("honor"));
	csd.setManner(res->getInt("manner"));
	// UI Settings
	cus.setCharacterID(char_id);
	cus.setFont(res->getInt("font"));
	cus.setShowEquip(res->getInt("show_equip"));
	cus.setAllowParty(res->getInt("allow_party"));
	// View
	cvd.setCharacterID(char_id);
	cvd.setHairStyleID(res->getInt("hair_style_id"));
	cvd.setHairColorID(res->getInt("hair_color_id"));
	cvd.setClothColorID(res->getInt("cloth_color_id"));
	cvd.setBodyID(res->getInt("body_id"));
	cvd.setWeaponID(res->getInt("weapon_id"));
	cvd.setShieldID(res->getInt("shield_id"));
	cvd.setHeadTopViewID(res->getInt("head_top_view_id"));
	cvd.setHeadMidViewID(res->getInt("head_mid_view_id"));
	cvd.setHeadBottomViewID(res->getInt("head_bottom_view_id"));
	cvd.setRobeViewID(res->getInt("robe_view_id"));
	// Position
	cpd.setCharacterID(char_id);
	cpd.setCurrentMap(res->getString("current_map"));
	cpd.setCurrentX(res->getInt("current_x"));
	cpd.setCurrentY(res->getInt("current_y"));
	cpd.setSavedMap(res->getString("saved_map"));
	cpd.setSavedX(res->getInt("saved_x"));
	cpd.setSavedY(res->getInt("saved_y"));
	// Misc
	cmd.setCharacterID(char_id);
	cmd.setRenameCount(res->getInt("rename_count"));
	cmd.setUniqueItemCounter(res->getInt64("unique_item_counter"));
	cmd.setHotkeyRowIndex(res->getInt("hotkey_row_index"));
	cmd.setChangeSlotCount(res->getInt("change_slot_count"));
	// Group
	cgd.setCharacterID(char_id);
	cgd.setPartyID(res->getInt("party_id"));
	cgd.setGuildID(res->getInt("guild_id"));
	// Family
	cfd.setCharacterID(char_id);
	cfd.setPartnerAID(res->getInt("partner_aid"));
	cfd.setFatherAID(res->getInt("father_aid"));
	cfd.setMotherAID(res->getInt("mother_aid"));
	cfd.setChildAID(res->getInt("child_aid"));
	// Companion
	ccd.setCharacterID(char_id);
	ccd.setPetID(res->getInt("pet_id"));
	ccd.setHomunID(res->getInt("homun_id"));
	ccd.setElementalID(res->getInt("elemental_id"));
	// Access
	cad.setCharacterID(char_id);
	cad.setUnbanTime(res->getInt("unban_time"));
	cad.setDeleteDate(res->getInt("delete_date"));

	// Append to character.
	c.setStatusData(std::make_shared<Horizon::Models::Characters::Status>(csd));
	c.setUISettingsData(std::make_shared<Horizon::Models::Characters::UISettings>(cus));
	c.setViewData(std::make_shared<Horizon::Models::Characters::View>(cvd));
	c.setPositionData(std::make_shared<Horizon::Models::Characters::Position>(cpd));
	c.setMiscData(std::make_shared<Horizon::Models::Characters::Misc>(cmd));
	c.setGroupData(std::make_shared<Horizon::Models::Characters::Group>(cgd));
	c.setFamilyData(std::make_shared<Horizon::Models::Characters::Family>(cfd));
	c.setCompanionData(std::make_shared<Horizon::Models::Characters::Companion>(ccd));
	c.setAccessData(std::make_shared<Horizon::Models::Characters::Access>(cad));

	return std::make_shared<Horizon::Models::Characters::Character>(c);
}

int Horizon::Char::Database::Query::AllCharactersByAccount(std::shared_ptr<GameAccount> account)
{
	auto sql = CharServer->MySQLBorrow();
	boost::optional<std::string> query = getQueryString(SELECT_ALL_CHARS_BY_AID);
	int results = 0;

	if (!query)
		return 0;

	try {
		sql::PreparedStatement *pstmt = sql->getConnection()->prepareStatement(*query);
		pstmt->setInt(1, account->getID());
		sql::ResultSet *res = pstmt->executeQuery();

		while (res != nullptr && res->next()) {
			account->addCharacter(CreateCharacterModelFromResult(account->getID(), res));
			++results;
		}
		delete pstmt;
		delete res;
	} catch (sql::SQLException &e) {
		DBLog->error("SQLException: {}", e.what());
	}

	CharServer->MySQLUnborrow(sql);
	return results;
}

int Horizon::Char::Database::Query::CheckExistingCharByName(std::string name)
{
	auto sql = CharServer->MySQLBorrow();
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
