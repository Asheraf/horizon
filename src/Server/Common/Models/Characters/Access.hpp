//
// Created by SagunKho on 01/02/2018.
//

#ifndef HORIZON_CHARACTERS_ACCESSDATA_HPP
#define HORIZON_CHARACTERS_ACCESSDATA_HPP

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
				setCharId(char_id);
				setUnbanTime(res->getUInt("unban_time"));
				setDeleteDate(res->getUInt("delete_date"));
				ret = true;
			}

			delete res;
			delete pstmt;
		} catch (sql::SQLException &e) {
			DBLog->error("GameAccount::VerifyCredentialsBCrypt: {}", e.what());
		}

		server->MySQLUnborrow(sql);

		return false;
	}

	/* Char ID */
	uint32_t getCharId() const { return char_id; }
	void setCharId(uint32_t char_id) { Access::char_id = char_id; }
	/* Unban Time */
	uint32_t getUnbanTime() const { return unban_time; }
	void setUnbanTime(uint32_t unban_time) { Access::unban_time = unban_time; }
	/* Account Delete Date */
	uint32_t getDeleteDate() const { return delete_date; }
	void setDeleteDate(uint32_t delete_date) { Access::delete_date = delete_date; }

private:
	uint32_t char_id;        ///< Character ID
	uint32_t unban_time;     ///< Time until character is unbanned.
	uint32_t delete_date;    ///< Date when the character may be deleted, if set for deletion.
};
}
}
}
#endif //HORIZON_CHARACTERACCESSDATA_HPP
