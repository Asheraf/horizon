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

#ifndef HORIZON_MODELS_CHARACTERS_STATUSDATA_HPP
#define HORIZON_MODELS_CHARACTERS_STATUSDATA_HPP

#include "Core/Database/MySqlConnection.hpp"
#include "Server/Common/Horizon.hpp"
#include "Server/Common/Server.hpp"

namespace Horizon
{
namespace Models
{
namespace Character
{
class Status
{
public:
	Status() {}
	~Status() {}

	Status(uint32_t zeny)
	: base_level(1), job_level(1)
	{
		//
	}

	Status(uint32_t z, uint8_t str, uint8_t agi, uint8_t int_, uint8_t vit, uint8_t dex, uint8_t luk)
	: base_level(1), job_level(1), zeny(z), strength(str), agility(agi), vitality(vit), intelligence(int_), dexterity(dex), luck(luk)
	{
		//
	}

	/**
	 * Load all fields from the database into this instance.
	 * @param server
	 * @param char_id
	 * @return
	 */
	bool load(Server *server, uint32_t char_id)
	{
		std::string query = "SELECT * FROM `character_status_data` WHERE `id` = ?";
		auto sql = server->MySQLBorrow();
		bool ret = false;

		try {
			sql::PreparedStatement *pstmt = sql->getConnection()->prepareStatement(query);
			pstmt->setInt(1, char_id);
			sql::ResultSet *res = pstmt->executeQuery();

			if (res != nullptr && res->next()) {
				/**
				 * Create Game Account Data
				 */
				setCharacterID(char_id);
				setJobClass((uint16_t) res->getUInt("job_class"));
				setBaseLevel((uint16_t) res->getUInt("base_level"));
				setJobLevel((uint16_t) res->getUInt("job_level"));
				setBaseExperience(res->getUInt64("base_experience"));
				setJobExperience(res->getUInt64("job_experience"));
				setZeny(res->getUInt("zeny"));
				setStrength((uint16_t) res->getInt("strength"));
				setAgility((uint16_t) res->getInt("agility"));
				setVitality((uint16_t) res->getInt("vitality"));
				setIntelligence((uint16_t) res->getInt("intelligence"));
				setDexterity((uint16_t) res->getInt("dexterity"));
				setLuck((uint16_t) res->getInt("luck"));
				setMaximumHP(res->getUInt("maximum_hp"));
				setMaximumSP(res->getUInt("maximum_sp"));
				setHP(res->getUInt("hp"));
				setSP(res->getUInt("sp"));
				setStatusPoints(res->getUInt("status_points"));
				setSkillPoints(res->getUInt("skill_points"));
				setBodyState(res->getUInt("body_state"));
				setVirtue((int16_t) res->getInt("virtue"));
				setHonor(res->getUInt("honor"));
				setManner((int16_t) res->getInt("manner"));
				ret = true;
			}

			delete res;
			delete pstmt;
		} catch (sql::SQLException &e) {
			DBLog->error("Models::Character::Status::LoadFromDatabase: {}", e.what());
		}

		server->MySQLUnborrow(sql);

		return ret;
	}

	/**
	 * @brief Save this model to the database in its current state.
	 * @param[in|out] server   instance of the server object used to borrow mysql connections.
	 */
	void save(Server *server)
	{
		auto sql = server->MySQLBorrow();

		std::string query = "REPLACE INTO `character_status_data` "
			"(`id`, `job_class`, `base_level`, `job_level`, "
			"`base_experience`, `job_experience`, `zeny`, "
			"`strength`, `agility`, `vitality`, `intelligence`, `dexterity`, `luck`, "
			"`maximum_hp`, `maximum_sp`, `hp`, `sp`, `status_points`, `skill_points`, "
			"`body_state`, `virtue`, `honor`, `manner`) "
			"VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?);";

		try {
			sql::PreparedStatement *pstmt = sql->getConnection()->prepareStatement(query);
			pstmt->setInt(1, getCharacterID());
			pstmt->setInt(2, getJobClass());
			pstmt->setInt(3, getBaseLevel());
			pstmt->setInt(4, getJobLevel());
			pstmt->setInt64(5, getBaseExperience());
			pstmt->setInt64(6, getJobExperience());
			pstmt->setInt(7, getZeny());
			pstmt->setInt(8, getStrength());
			pstmt->setInt(9, getAgility());
			pstmt->setInt(10, getVitality());
			pstmt->setInt(11, getIntelligence());
			pstmt->setInt(12, getDexterity());
			pstmt->setInt(13, getLuck());
			pstmt->setInt(14, getMaximumHP());
			pstmt->setInt(15, getMaximumSP());
			pstmt->setInt(16, getSP());
			pstmt->setInt(17, getHP());
			pstmt->setInt(18, getStatusPoints());
			pstmt->setInt(19, getSkillPoints());
			pstmt->setInt(20, getBodyState());
			pstmt->setInt(21, getVirtue());
			pstmt->setInt(22, getHonor());
			pstmt->setInt(23, getManner());
			pstmt->executeUpdate();
			delete pstmt;
		} catch (sql::SQLException &e) {
			DBLog->error("SQLException: {}", e.what());
		}

		server->MySQLUnborrow(sql);
	}

	/* Character ID */
	uint32_t getCharacterID() const { return character_id; }
	void setCharacterID(uint32_t character_id) { Status::character_id = character_id; }
	/* Job Class */
	uint16_t getJobClass() const { return job_class; }
	void setJobClass(uint16_t job_class) { Status::job_class = job_class; }
	/* Base Level */
	uint16_t getBaseLevel() const { return base_level; }
	void setBaseLevel(uint16_t base_level) { Status::base_level = base_level; }
	/* Job Level */
	uint16_t getJobLevel() const { return job_level; }
	void setJobLevel(uint16_t job_level) { Status::job_level = job_level; }
	/* Base Experience */
	uint64_t getBaseExperience() const { return base_experience; }
	void setBaseExperience(uint64_t base_experience) { Status::base_experience = base_experience; }
	/* Job Experience */
	uint64_t getJobExperience() const { return job_experience; }
	void setJobExperience(uint64_t job_experience) { Status::job_experience = job_experience; }
	/* Zeny */
	uint32_t getZeny() const { return zeny; }
	void setZeny(uint32_t zeny) { Status::zeny = zeny; }
	/* Strength */
	uint16_t getStrength() const { return strength; }
	void setStrength(uint16_t strength) { Status::strength = strength; }
	/* Agility */
	uint16_t getAgility() const { return agility; }
	void setAgility(uint16_t agility) { Status::agility = agility; }
	/* Vitality */
	uint16_t getVitality() const { return vitality; }
	void setVitality(uint16_t vitality) { Status::vitality = vitality; }
	/* Intelligence */
	uint16_t getIntelligence() const { return intelligence; }
	void setIntelligence(uint16_t intelligence) { Status::intelligence = intelligence; }
	/* Dexterity */
	uint16_t getDexterity() const { return dexterity; }
	void setDexterity(uint16_t dexterity) { Status::dexterity = dexterity; }
	/* Luck */
	uint16_t getLuck() const { return luck; }
	void setLuck(uint16_t luck) { Status::luck = luck; }
	/* Maximum HP */
	uint32_t getMaximumHP() const { return maximum_hp; }
	void setMaximumHP(uint32_t maximum_hp) { Status::maximum_hp = maximum_hp; }
	/* Maximum SP */
	uint32_t getMaximumSP() const { return maximum_sp; }
	void setMaximumSP(uint32_t maximum_sp) { Status::maximum_sp = maximum_sp; }
	/* HP */
	uint32_t getHP() const { return hp; }
	void setHP(uint32_t hp) { Status::hp = hp; }
	/* SP */
	uint32_t getSP() const { return sp; }
	void setSP(uint32_t sp) { Status::sp = sp; }
	/* Status Point */
	uint32_t getStatusPoints() const { return status_points; }
	void setStatusPoints(uint32_t status_points) { Status::status_points = status_points; }
	/* Skill Points */
	uint32_t getSkillPoints() const { return skill_points; }
	void setSkillPoints(uint32_t skill_points) { Status::skill_points = skill_points; }
	/* Body State */
	uint32_t getBodyState() const { return body_state; }
	void setBodyState(uint32_t body_state) { Status::body_state = body_state; }
	/* Virtue */
	int16_t getVirtue() const { return virtue; }
	void setVirtue(int16_t virtue) { Status::virtue = virtue; }
	/* Honor */
	uint32_t getHonor() const { return honor; }
	void setHonor(uint32_t honor) { Status::honor = honor; }
	/* Manner */
	int16_t getManner() const { return manner; }
	void setManner(int16_t manner) { Status::manner = manner; }
private:
	uint32_t character_id{0};
	uint16_t job_class{0};
	uint16_t base_level{0};
	uint16_t job_level{0};
	uint64_t base_experience{0};
	uint64_t job_experience{0};
	uint32_t zeny{0};
	uint16_t strength{0};
	uint16_t agility{0};
	uint16_t vitality{0};
	uint16_t intelligence{0};
	uint16_t dexterity{0};
	uint16_t luck{0};
	uint32_t maximum_hp{0}, maximum_sp{0};
	uint32_t hp{0}, sp{0};
	uint32_t status_points{0}, skill_points{0};
	uint32_t body_state{0};
	int16_t virtue{0};
	uint32_t honor{0};
	int16_t manner{0};
};
}
}
}
#endif // HORIZON_MODELS_CHARACTERS_STATUSDATA_HPP
