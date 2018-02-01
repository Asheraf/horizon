//
// Created by SagunKho on 01/02/2018.
//

#ifndef HORIZON_MODELS_CHARACTERS_UISETTINGS_HPP
#define HORIZON_MODELS_CHARACTERS_UISETTINGS_HPP

#include "Server/Common/Horizon.hpp"
#include "Server/Common/Server.hpp"
#include "Core/Database/MySqlConnection.hpp"

namespace Horizon
{
namespace Models
{
namespace Characters
{
class UISettings
{
public:
	UISettings() {}
	~UISettings() {}

	/**
	 * Load all fields from the database into this instance.
	 * @param server
	 * @param char_id
	 * @return
	 */
	bool LoadFromDatabase(Server *server, uint32_t char_id)
	{
		std::string query = "SELECT * FROM character_ui_settings WHERE char_id = ?";
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
				setFont((uint8_t) res->getUInt("font"));
				setShowEquip((uint8_t) res->getUInt("show_equip"));
				setAllowParty((uint8_t) res->getUInt("allow_party"));

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
	void setCharacterId(uint32_t character_id) { UISettings::character_id = character_id; }
	/* Font */
	uint8_t getFont() const { return font; }
	void setFont(uint8_t font) { UISettings::font = font; }
	/* Show Equip */
	uint8_t getShowEquip() const { return show_equip; }
	void setShowEquip(uint8_t show_equip) { UISettings::show_equip = show_equip; }
	/* Allow Party */
	uint8_t getAllowParty() const { return allow_party; }
	void setAllowParty(uint8_t allow_party) { UISettings::allow_party = allow_party; }
private:
	uint32_t character_id;
	uint8_t font;
	uint8_t show_equip;
	uint8_t allow_party;
};
}
}
}
#endif // HORIZON_MODELS_CHARACTERS_UISETTINGS_HPP
