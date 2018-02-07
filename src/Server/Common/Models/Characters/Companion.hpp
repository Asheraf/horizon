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
	bool load(Server *server, uint32_t char_id)
	{
		std::string query = "SELECT * FROM character_companion_data WHERE char_id = ?";
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
				setPetID(res->getUInt("pet_id"));
				setHomunID(res->getUInt("homun_id"));
				setElementalID(res->getUInt("elemental_id"));
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

	/**
	 * @brief Save this model to the database in its current state.
	 * @param[in|out] server   instance of the server object used to borrow mysql connections.
	 */
	void save(Server *server)
	{
		auto sql = server->MySQLBorrow();

		std::string query = "REPLACE INTO `character_companion_data` "
			"(`id`, `pet_id`, `homun_id`, `elemental_id`) VALUES (?, ?, ?, ?);";

		try {
			sql::PreparedStatement *pstmt = sql->getConnection()->prepareStatement(query);
			pstmt->setInt(1, getCharacterID());
			pstmt->setInt(2, getPetID());
			pstmt->setInt(3, getHomunID());
			pstmt->setInt(4, getElementalID());
			pstmt->executeUpdate();
			delete pstmt;
		} catch (sql::SQLException &e) {
			DBLog->error("SQLException: {}", e.what());
		}

		server->MySQLUnborrow(sql);
	}
	
	/* Character Id */
	uint32_t getCharacterID() const { return character_id; }
	void setCharacterID(uint32_t character_id) { Companion::character_id = character_id; }
	/* Pet ID */
	uint32_t getPetID() const { return pet_id; }
	void setPetID(uint32_t pet_id) { Companion::pet_id = pet_id; }
	/* Homun ID */
	uint32_t getHomunID() const { return homun_id; }
	void setHomunID(uint32_t homun_id) { Companion::homun_id = homun_id; }
	/* Elemental ID */
	uint32_t getElementalID() const { return elemental_id; }
	void setElementalID(uint32_t elemental_id) { Companion::elemental_id = elemental_id; }
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
