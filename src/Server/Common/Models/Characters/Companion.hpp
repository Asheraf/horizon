//
// Created by SagunKho on 01/02/2018.
//

#ifndef HORIZON_MODELS_CHARACTERS_COMPANION_HPP
#define HORIZON_MODELS_CHARACTERS_COMPANION_HPP

#include "Server/Common/Horizon.hpp"
#include "Server/Common/Server.hpp"
#include "Core/Database/MySqlConnection.hpp"

namespace Horizon
{
namespace Models
{
namespace Characters
{
class Companion
{
public:
	Companion() {}
	~Companion() {}

	/**
	 * Load all fields from the database into this instance.
	 * @param server
	 * @param char_id
	 * @return
	 */
	bool LoadFromDatabase(Server *server, uint32_t char_id)
	{
		std::string query = "SELECT * FROM character_companion_data WHERE char_id = ?";
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
				setPetId(res->getUInt("pet_id"));
				setHomunId(res->getUInt("homun_id"));
				setElementalId(res->getUInt("elemental_id"));
				ret = true;
			}

			delete res;
			delete pstmt;
		} catch (sql::SQLException &e) {
			DBLog->error("Models::Characters::Companion::LoadFromDatabase: {}", e.what());
		}

		server->MySQLUnborrow(sql);

		return ret;
	}
	/* Character Id */
	uint32_t getCharacterId() const { return character_id; }
	void setCharacterId(uint32_t character_id) { Companion::character_id = character_id; }
	/* Pet ID */
	uint32_t getPetId() const { return pet_id; }
	void setPetId(uint32_t pet_id) { Companion::pet_id = pet_id; }
	/* Homun ID */
	uint32_t getHomunId() const { return homun_id; }
	void setHomunId(uint32_t homun_id) { Companion::homun_id = homun_id; }
	/* Elemental ID */
	uint32_t getElementalId() const { return elemental_id; }
	void setElementalId(uint32_t elemental_id) { Companion::elemental_id = elemental_id; }
private:
	uint32_t character_id;
	uint32_t pet_id;
	uint32_t homun_id;
	uint32_t elemental_id;
};
}
}
}
#endif // HORIZON_MODELS_CHARACTERS_COMPANION_HPP
