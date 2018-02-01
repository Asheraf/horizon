//
// Created by SagunKho on 01/02/2018.
//

#ifndef HORIZON_MODELS_CHARACTERS_POSITION_HPP
#define HORIZON_MODELS_CHARACTERS_POSITION_HPP

#include "Server/Common/Horizon.hpp"
#include "Server/Common/Server.hpp"
#include "Core/Database/MySqlConnection.hpp"

namespace Horizon
{
namespace Models
{
namespace Characters
{
class Position
{
public:
	Position() {}
	~Position() {}

	/**
	 * Load all fields from the database into this instance.
	 * @param server
	 * @param char_id
	 * @return
	 */
	bool LoadFromDatabase(Server *server, uint32_t char_id)
	{
		std::string query = "SELECT * FROM character_position_data WHERE char_id = ?";
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
				setCurrentMap(res->getString("current_map"));
				setCurrentX((uint16_t) res->getInt("current_x"));
				setCurrentY((uint16_t) res->getInt("current_y"));
				setSavedMap(res->getString("saved_map"));
				setSavedX((uint16_t) res->getInt("saved_x"));
				setSavedY((uint16_t) res->getInt("saved_y"));

				ret = true;
			}

			delete res;
			delete pstmt;
		} catch (sql::SQLException &e) {
			DBLog->error("Models::Characters::Misc::LoadFromDatabase: {}", e.what());
		}

		server->MySQLUnborrow(sql);

		return ret;
	}

	/* Character ID */
	uint32_t getCharacterID() const { return character_id; }
	void setCharacterID(uint32_t character_id) { Position::character_id = character_id; }
	/* Current Map */
	const std::string &getCurrentMap() const { return current_map; }
	void setCurrentMap(const std::string &current_map) { Position::current_map = current_map; }
	/* Current X */
	uint16_t getCurrentX() const { return current_x; }
	void setCurrentX(uint16_t current_x) { Position::current_x = current_x; }
	/* Current Y */
	uint16_t getCurrentY() const { return current_y; }
	void setCurrentY(uint16_t current_y) { Position::current_y = current_y; }
	/* Saved Map */
	const std::string &getSavedMap() const { return saved_map; }
	void setSavedMap(const std::string &saved_map) { Position::saved_map = saved_map; }
	/* Saved X */
	uint16_t getSavedX() const { return saved_x; }
	void setSavedX(uint16_t saved_x) { Position::saved_x = saved_x; }
	/* Saved Y */
	uint16_t getSavedY() const { return saved_y; }
	void setSavedY(uint16_t saved_y) { Position::saved_y = saved_y; }

private:
	uint32_t character_id;
	std::string current_map;
	uint16_t current_x, current_y;
	std::string saved_map;
	uint16_t saved_x, saved_y;
};
}
}
}
#endif // HORIZON_MODELS_CHARACTERS_POSITION_HPP
