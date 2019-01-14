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
	: _base_level(1), _job_level(1), _zeny(zeny)
	{
		//
	}

	Status(uint32_t z, uint8_t str, uint8_t agi, uint8_t int_, uint8_t vit, uint8_t dex, uint8_t luk)
	: _base_level(1), _job_level(1), _zeny(z), _strength(str), _agility(agi), _vitality(vit), _intelligence(int_), _dexterity(dex), _luck(luk)
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
				set_job_class((uint16_t) res->getUInt("job_class"));
				set_base_level((uint16_t) res->getUInt("base_level"));
				set_job_level((uint16_t) res->getUInt("job_level"));
				set_base_exp(res->getUInt64("base_experience"));
				set_job_exp(res->getUInt64("job_experience"));
				set_zeny(res->getUInt("zeny"));
				set_strength((uint16_t) res->getInt("strength"));
				set_agility((uint16_t) res->getInt("agility"));
				set_vitality((uint16_t) res->getInt("vitality"));
				set_intelligence((uint16_t) res->getInt("intelligence"));
				set_dexterity((uint16_t) res->getInt("dexterity"));
				set_luck((uint16_t) res->getInt("luck"));
				set_max_hp(res->getUInt("maximum_hp"));
				set_max_sp(res->getUInt("maximum_sp"));
				set_hp(res->getUInt("hp"));
				set_sp(res->getUInt("sp"));
				set_status_points(res->getUInt("status_points"));
				set_skill_points(res->getUInt("skill_points"));
				set_body_state(res->getUInt("body_state"));
				set_virtue((int16_t) res->getInt("virtue"));
				set_honor(res->getUInt("honor"));
				set_manner((int16_t) res->getInt("manner"));
				ret = true;
			}

			delete res;
			delete pstmt;
		} catch (sql::SQLException &e) {
			DBLog->error("Models::Character::Status::LoadFromDatabase: {}", e.what());
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

		std::string query = "REPLACE INTO `character_status_data` "
			"(`id`, `job_class`, `base_level`, `job_level`, "
			"`base_experience`, `job_experience`, `zeny`, "
			"`strength`, `agility`, `vitality`, `intelligence`, `dexterity`, `luck`, "
			"`maximum_hp`, `maximum_sp`, `hp`, `sp`, `status_points`, `skill_points`, "
			"`body_state`, `virtue`, `honor`, `manner`) "
			"VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?);";

		try {
			sql::PreparedStatement *pstmt = sql->getConnection()->prepareStatement(query);
			pstmt->setInt(1, get_character_id());
			pstmt->setInt(2, get_job_class());
			pstmt->setInt(3, get_base_level());
			pstmt->setInt(4, get_job_level());
			pstmt->setInt64(5, get_base_exp());
			pstmt->setInt64(6, get_job_exp());
			pstmt->setInt(7, get_zeny());
			pstmt->setInt(8, get_strength());
			pstmt->setInt(9, get_agility());
			pstmt->setInt(10, get_vitality());
			pstmt->setInt(11, get_intelligence());
			pstmt->setInt(12, get_dexterity());
			pstmt->setInt(13, get_luck());
			pstmt->setInt(14, get_max_hp());
			pstmt->setInt(15, get_max_sp());
			pstmt->setInt(16, get_sp());
			pstmt->setInt(17, get_hp());
			pstmt->setInt(18, get_status_points());
			pstmt->setInt(19, get_skill_points());
			pstmt->setInt(20, get_body_state());
			pstmt->setInt(21, get_virtue());
			pstmt->setInt(22, get_honor());
			pstmt->setInt(23, get_manner());
			pstmt->executeUpdate();
			delete pstmt;
		} catch (sql::SQLException &e) {
			DBLog->error("SQLException: {}", e.what());
		}

		server->mysql_unborrow(sql);
	}

	/* Character ID */
	uint32_t get_character_id() const { return _character_id; }
	void set_character_id(uint32_t character_id) { _character_id = character_id; }
	/* Job Class */
	uint16_t get_job_class() const { return _job_class; }
	void set_job_class(uint16_t job_class) { _job_class = job_class; }
	/* Base Level */
	uint16_t get_base_level() const { return _base_level; }
	void set_base_level(uint16_t base_level) { _base_level = base_level; }
	/* Job Level */
	uint16_t get_job_level() const { return _job_level; }
	void set_job_level(uint16_t job_level) { _job_level = job_level; }
	/* Base Experience */
	uint64_t get_base_exp() const { return _base_experience; }
	void set_base_exp(uint64_t base_experience) { _base_experience = base_experience; }
	/* Job Experience */
	uint64_t get_job_exp() const { return _job_experience; }
	void set_job_exp(uint64_t job_experience) { _job_experience = job_experience; }
	/* Zeny */
	uint32_t get_zeny() const { return _zeny; }
	void set_zeny(uint32_t zeny) { _zeny = zeny; }
	/* Strength */
	uint16_t get_strength() const { return _strength; }
	void set_strength(uint16_t strength) { _strength = strength; }
	/* Agility */
	uint16_t get_agility() const { return _agility; }
	void set_agility(uint16_t agility) { _agility = agility; }
	/* Vitality */
	uint16_t get_vitality() const { return _vitality; }
	void set_vitality(uint16_t vitality) { _vitality = vitality; }
	/* Intelligence */
	uint16_t get_intelligence() const { return _intelligence; }
	void set_intelligence(uint16_t intelligence) { _intelligence = intelligence; }
	/* Dexterity */
	uint16_t get_dexterity() const { return _dexterity; }
	void set_dexterity(uint16_t dexterity) { _dexterity = dexterity; }
	/* Luck */
	uint16_t get_luck() const { return _luck; }
	void set_luck(uint16_t luck) { _luck = luck; }
	/* Maximum HP */
	uint32_t get_max_hp() const { return _maximum_hp; }
	void set_max_hp(uint32_t maximum_hp) { _maximum_hp = maximum_hp; }
	/* Maximum SP */
	uint32_t get_max_sp() const { return _maximum_sp; }
	void set_max_sp(uint32_t maximum_sp) { _maximum_sp = maximum_sp; }
	/* HP */
	uint32_t get_hp() const { return _hp; }
	void set_hp(uint32_t hp) { _hp = hp; }
	/* SP */
	uint32_t get_sp() const { return _sp; }
	void set_sp(uint32_t sp) { _sp = sp; }
	/* Status Point */
	uint32_t get_status_points() const { return _status_points; }
	void set_status_points(uint32_t status_points) { _status_points = status_points; }
	/* Skill Points */
	uint32_t get_skill_points() const { return _skill_points; }
	void set_skill_points(uint32_t skill_points) { _skill_points = skill_points; }
	/* Body State */
	uint32_t get_body_state() const { return _body_state; }
	void set_body_state(uint32_t body_state) { _body_state = body_state; }
	/* Virtue */
	int16_t get_virtue() const { return _virtue; }
	void set_virtue(int16_t virtue) { _virtue = virtue; }
	/* Honor */
	uint32_t get_honor() const { return _honor; }
	void set_honor(uint32_t honor) { _honor = honor; }
	/* Manner */
	int16_t get_manner() const { return _manner; }
	void set_manner(int16_t manner) { _manner = manner; }
private:
	uint32_t _character_id{0};
	uint16_t _job_class{0};
	uint16_t _base_level{0};
	uint16_t _job_level{0};
	uint64_t _base_experience{0};
	uint64_t _job_experience{0};
	uint32_t _zeny{0};
	uint16_t _strength{0};
	uint16_t _agility{0};
	uint16_t _vitality{0};
	uint16_t _intelligence{0};
	uint16_t _dexterity{0};
	uint16_t _luck{0};
	uint32_t _maximum_hp{0}, _maximum_sp{0};
	uint32_t _hp{0}, _sp{0};
	uint32_t _status_points{0}, _skill_points{0};
	uint32_t _body_state{0};
	int16_t _virtue{0};
	uint32_t _honor{0};
	int16_t _manner{0};
};
}
}
}
#endif // HORIZON_MODELS_CHARACTERS_STATUSDATA_HPP
