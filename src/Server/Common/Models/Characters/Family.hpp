//
// Created by SagunKho on 01/02/2018.
//

#ifndef HORIZON_MODELS_CHARACTERS_FAMILY_HPP
#define HORIZON_MODELS_CHARACTERS_FAMILY_HPP

#include "Server/Common/Horizon.hpp"
#include "Server/Common/Server.hpp"
#include "Core/Database/MySqlConnection.hpp"

namespace Horizon
{
namespace Models
{
namespace Characters
{
class Family
{
public:
	Family() {}
	~Family() {}

	/**
	 * Load all fields from the database into this instance.
	 * @param server
	 * @param char_id
	 * @return
	 */
	bool LoadFromDatabase(Server *server, uint32_t char_id)
	{
		std::string query = "SELECT * FROM character_family_data WHERE char_id = ?";
		auto sql = server->MySQLBorrow();
		bool ret = false;

		try {
			sql::PreparedStatement *pstmt = sql->sql_connection->prepareStatement(query);
			pstmt->setInt(1, char_id);
			sql::ResultSet *res = pstmt->executeQuery();

			if (res != nullptr && res->next()) {
				/**
				 * Create Game Account Data
				 */
				setCharacterId(char_id);
				setParterAid(res->getUInt("partner_aid"));
				setFatherAid(res->getUInt("father_aid"));
				setMotherAid(res->getUInt("mother_aid"));
				setChildAid(res->getUInt("child_aid"));
				ret = true;
			}

			delete res;
			delete pstmt;
		} catch (sql::SQLException &e) {
			DBLog->error("Models::Characters::Family::LoadFromDatabase: {}", e.what());
		}

		server->MySQLUnborrow(sql);

		return ret;
	}

	/* Character Id */
	uint32_t getCharacterId() const { return character_id; }
	void setCharacterId(uint32_t character_id) { Family::character_id = character_id; }
	/* Parter Account ID */
	uint32_t getParterAid() const { return parter_aid; }
	void setParterAid(uint32_t parter_aid) { Family::parter_aid = parter_aid; }
	/* Father Account ID */
	uint32_t getFatherAid() const { return father_aid; }
	void setFatherAid(uint32_t father_aid) { Family::father_aid = father_aid; }
	/* Mother Account ID */
	uint32_t getMotherAid() const { return mother_aid; }
	void setMotherAid(uint32_t mother_aid) { Family::mother_aid = mother_aid; }
	/* Child Account ID */
	uint32_t getChildAid() const { return child_aid; }
	void setChildAid(uint32_t child_aid) { Family::child_aid = child_aid; }

private:
	uint32_t character_id;
	uint32_t parter_aid;
	uint32_t father_aid;
	uint32_t mother_aid;
	uint32_t child_aid;
};
}
}
}
#endif // HORIZON_MODELS_CHARACTERS_FAMILY_HPP
