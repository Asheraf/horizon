//
// Created by SagunKho on 01/02/2018.
//

#ifndef HORIZON_MODELS_CHARACTERS_MISCDATA_HPP
#define HORIZON_MODELS_CHARACTERS_MISCDATA_HPP

#include "Server/Common/Horizon.hpp"
#include "Server/Common/Server.hpp"
#include "Core/Database/MySqlConnection.hpp"

namespace Horizon
{
namespace Models
{
namespace Characters
{
class Misc
{
public:
	Misc() {}
	~Misc() {}

	/**
	 * Load all fields from the database into this instance.
	 * @param server
	 * @param char_id
	 * @return
	 */
	bool LoadFromDatabase(Server *server, uint32_t char_id)
	{
		std::string query = "SELECT * FROM character_misc_data WHERE char_id = ?";
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
				setRenameCount((uint8_t) res->getUInt("rename_count"));
				setUniqueItemCounter(res->getUInt("unique_item_counter"));
				setHotkeyrowIndex((uint16_t) res->getUInt("hotkey_row_index"));
				setChangeSlot((uint8_t) res->getUInt("change_slot"));
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
	uint32_t getCharacterId() const { return character_id; }
	void setCharacterId(uint32_t character_id) { Misc::character_id = character_id; }
	/* Character Rename Count */
	uint8_t getRenameCount() const { return rename_count; }
	void setRenameCount(uint8_t rename_count) { Misc::rename_count = rename_count; }
	/* Unique Item Counter */
	uint64_t getUniqueItemCounter() const { return unique_item_counter; }
	void setUniqueItemCounter(uint64_t unique_item_counter) { Misc::unique_item_counter = unique_item_counter; }
	/* Hotkey Row Index */
	uint8_t getHotkeyRowIndex() const { return hotkey_row_index; }
	void setHotkeyrowIndex(uint8_t hotkey_row_index) { Misc::hotkey_row_index = hotkey_row_index; }
	/* Change Slot Count */
	uint8_t getChangeSlotCount() const { return change_slot_count; }
	void setChangeSlot(uint8_t change_slot_count) { Misc::change_slot_count = change_slot_count; }
private:
	uint32_t character_id;
	uint8_t rename_count;
	uint64_t unique_item_counter;
	uint8_t hotkey_row_index;
	uint8_t change_slot_count;
};
}
}
}
#endif // HORIZON_MODELS_CHARACTERS_MISCDATA_HPP
