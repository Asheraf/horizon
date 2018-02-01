//
// Created by SagunKho on 31/01/2018.
//

#ifndef HORIZON_MODELS_CHARACTERS_CHARACTER_HPP
#define HORIZON_MODELS_CHARACTERS_CHARACTER_HPP

#include "Server/Common/Horizon.hpp"
#include <string>
#include <Server/Common/Server.hpp>

enum character_gender_types
{
	CHARACTER_GENDER_MALE,
	CHARACTER_GENDER_FEMALE
};

namespace Horizon
{
namespace Models
{
namespace Characters
{
class Character
{
public:
	Character() {}
	~Character() {}

	/**
	 * Load all fields from the database into this instance.
	 * @param server
	 * @param char_id
	 * @return
	 */
	bool LoadFromDatabase(Server *server, uint32_t char_id)
	{
		std::string query = "SELECT * FROM characters WHERE char_id = ?";
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
				setAccount_id(res->getUInt("account_id"));
				setSlot((uint16_t) res->getUInt("slot"));
				setName(res->getString("name"));
				setOnline(res->getBoolean("online"));
				setGender((character_gender_types) res->getInt("gender"));
				ret = true;
			}

			delete res;
			delete pstmt;
		} catch (sql::SQLException &e) {
			DBLog->error("Models::Characters::GameAccount::LoadFromDatabase: {}", e.what());
		}

		server->MySQLUnborrow(sql);

		return ret;
	}
	/* Character ID */
	uint32_t getCharacterId() const { return character_id; }
	void setCharacterId(uint32_t character_id) { Character::character_id = character_id; }
	/* Account ID */
	uint32_t getAccount_id() const { return account_id; }
	void setAccount_id(uint32_t account_id) { Character::account_id = account_id; }
	/* Slot */
	uint16_t getSlot() const { return slot; }
	void setSlot(uint16_t slot) { Character::slot = slot; }
	/* Name */
	const std::string &getName() const { return name; }
	void setName(const std::string &name) { Character::name = name; }
	/* Is Online */
	bool isOnline() const { return online; }
	void setOnline(bool online) { Character::online = online; }
	/* Gender */
	character_gender_types getGender() const { return gender; }
	void setGender(character_gender_types gender) { Character::gender = gender; }

private:
	uint32_t character_id;
	uint32_t account_id;
	uint16_t slot;
	std::string name;
	bool online;
	character_gender_types gender;
};
}
}
}

#endif // HORIZON_MODELS_CHARACTERS_CHARACTER_HPP
