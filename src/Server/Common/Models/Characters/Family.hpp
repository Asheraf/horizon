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
				setCharacterID(char_id);
				setParterAID(res->getUInt("partner_aid"));
				setFatherAID(res->getUInt("father_aid"));
				setMotherAID(res->getUInt("mother_aid"));
				setChildAID(res->getUInt("child_aid"));
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
	uint32_t getCharacterID() const { return character_id; }
	void setCharacterID(uint32_t character_id) { Family::character_id = character_id; }
	/* Parter Account ID */
	uint32_t getParterAID() const { return parter_aid; }
	void setParterAID(uint32_t parter_aid) { Family::parter_aid = parter_aid; }
	/* Father Account ID */
	uint32_t getFatherAID() const { return father_aid; }
	void setFatherAID(uint32_t father_aid) { Family::father_aid = father_aid; }
	/* Mother Account ID */
	uint32_t getMotherAID() const { return mother_aid; }
	void setMotherAID(uint32_t mother_aid) { Family::mother_aid = mother_aid; }
	/* Child Account ID */
	uint32_t getChildAID() const { return child_aid; }
	void setChildAID(uint32_t child_aid) { Family::child_aid = child_aid; }

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
