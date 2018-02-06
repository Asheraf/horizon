//
// Created by SagunKho on 31/01/2018.
//

#ifndef HORIZON_MODELS_CHARACTERS_STATUSDATA_HPP
#define HORIZON_MODELS_CHARACTERS_STATUSDATA_HPP

#include "Core/Database/MySqlConnection.hpp"
#include "Server/Common/Horizon.hpp"
#include "Server/Common/Server.hpp"

namespace Horizon
{
namespace Models
{
namespace Characters
{
class Status
{
public:
	Status() {}
	~Status() {}

	/**
	 * Load all fields from the database into this instance.
	 * @param server
	 * @param char_id
	 * @return
	 */
	bool LoadFromDatabase(Server *server, uint32_t char_id)
	{
		std::string query = "SELECT * FROM character_status_data WHERE char_id = ?";
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
			DBLog->error("Models::Characters::Status::LoadFromDatabase: {}", e.what());
		}

		server->MySQLUnborrow(sql);

		return ret;
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
	uint32_t character_id;
	uint16_t job_class;
	uint16_t base_level;
	uint16_t job_level;
	uint64_t base_experience;
	uint64_t job_experience;
	uint32_t zeny;
	uint16_t strength;
	uint16_t agility;
	uint16_t vitality;
	uint16_t intelligence;
	uint16_t dexterity;
	uint16_t luck;
	uint32_t maximum_hp, maximum_sp;
	uint32_t hp, sp;
	uint32_t status_points, skill_points;
	uint32_t body_state;
	int16_t virtue;
	uint32_t honor;
	int16_t manner;
};
}
}
}
#endif // HORIZON_MODELS_CHARACTERS_STATUSDATA_HPP
