//
// Created by SagunKho on 01/02/2018.
//

#ifndef HORIZON_MODELS_CHARACTERS_ACCESS_HPP
#define HORIZON_MODELS_CHARACTERS_ACCESS_HPP

#include "Server/Common/Horizon.hpp"
#include "Server/Common/Server.hpp"
#include "Core/Database/MySqlConnection.hpp"

namespace Horizon
{
namespace Models
{
namespace Characters
{
class Access
{
public:
	Access() {}
	~Access() {}

	/**
	 * Load all fields from the database into this instance.
	 * @param server
	 * @param char_id
	 * @return
	 */
	bool LoadFromDatabase(Server *server, uint32_t char_id)
	{
		std::string query = "SELECT * FROM character_access_data WHERE char_id = ?";
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
				setUnbanTime(res->getUInt("unban_time"));
				setDeleteDate(res->getUInt("delete_date"));
				ret = true;
			}

			delete res;
			delete pstmt;
		} catch (sql::SQLException &e) {
			DBLog->error("Models::Characters::Access::LoadFromDatabase: {}", e.what());
		}

		server->MySQLUnborrow(sql);

		return ret;
	}

	/* Char ID */
	uint32_t getCharacterID() const { return character_id; }
	void setCharacterID(uint32_t character_id) { Access::character_id = character_id; }
	/* Unban Time */
	uint32_t getUnbanTime() const { return unban_time; }
	void setUnbanTime(uint32_t unban_time) { Access::unban_time = unban_time; }
	/* Account Delete Date */
	uint32_t getDeleteDate() const { return delete_date; }
	void setDeleteDate(uint32_t delete_date) { Access::delete_date = delete_date; }

private:
	uint32_t character_id;        ///< Character ID
	uint32_t unban_time;     ///< Time until character is unbanned.
	uint32_t delete_date;    ///< Date when the character may be deleted, if set for deletion.
};
}
}
}
#endif // HORIZON_MODELS_CHARACTERS_ACCESS_HPP
