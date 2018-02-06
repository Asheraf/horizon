//
// Created by SagunKho on 31/01/2018.
//

#ifndef HORIZON_MODELS_CHARACTERS_CHARACTER_HPP
#define HORIZON_MODELS_CHARACTERS_CHARACTER_HPP

#include "Server/Common/Horizon.hpp"
#include "Server/Common/Server.hpp"

#include <string>

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
class Access;
class Companion;
class Family;
class Group;
class Misc;
class Position;
class Status;
class UISettings;
class View;

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
			sql::PreparedStatement *pstmt = sql->getConnection()->prepareStatement(query);
			pstmt->setInt(1, char_id);
			sql::ResultSet *res = pstmt->executeQuery();

			if (res != nullptr && res->next()) {
				/**
				 * Create Game Account Data
				 */
				setCharacterID(char_id);
				setAccountID(res->getUInt("account_id"));
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
	uint32_t getCharacterID() const { return _character_id; }
	void setCharacterID(uint32_t id) { _character_id = id; }

	/* Account ID */
	uint32_t getAccountID() const { return _account_id; }
	void setAccountID(uint32_t id) { _account_id = id; }

	/* Slot */
	uint16_t getSlot() const { return _slot; }
	void setSlot(uint16_t slot) { _slot = slot; }

	/* Name */
	const std::string &getName() const { return _name; }
	void setName(const std::string &name) { _name = name; }

	/* Is Online */
	bool isOnline() const { return _online; }
	void setOnline(bool online) { _online = online; }

	/* Gender */
	character_gender_types getGender() const { return _gender; }
	void setGender(character_gender_types gender) { _gender = gender; }

	/* Access Data*/
	const std::shared_ptr<Access> getAccessData() const { return _access_data; }
	void setAccessData(std::shared_ptr<Access> const &access) { _access_data = access; }

	/* Companion Data*/
	const std::shared_ptr<Companion> getCompanionData() const { return _companion_data; }
	void setCompanionData(std::shared_ptr<Companion> const &companion) { _companion_data = companion; }

	/* Family Data*/
	const std::shared_ptr<Family> getFamilyData() const { return _family_data; }
	void setFamilyData(std::shared_ptr<Family> const &family) { _family_data = family; }

	/* Group Data*/
	const std::shared_ptr<Group> getGroupData() const { return _group_data; }
	void setGroupData(std::shared_ptr<Group> const &group) { _group_data = group; }

	/* Misc Data*/
	const std::shared_ptr<Misc> getMiscData() const { return _misc_data; }
	void setMiscData(std::shared_ptr<Misc> const &misc) { _misc_data = misc; }

	/* Position Data*/
	const std::shared_ptr<Position> getPositionData() const { return _position_data; }
	void setPositionData(std::shared_ptr<Position> const &position) { _position_data = position; }

	/* Status Data*/
	const std::shared_ptr<Status> getStatusData() const { return _status_data; }
	void setStatusData(std::shared_ptr<Status> const &status) { _status_data = status; }

	/* UISettings Data*/
	const std::shared_ptr<UISettings> getUISettingsData() const { return _ui_settings; }
	void setUISettingsData(std::shared_ptr<UISettings> const &settings) { _ui_settings = settings; }

	/* View Data*/
	const std::shared_ptr<View> getViewData() const { return _view_data; }
	void setViewData(std::shared_ptr<View> const &view) { _view_data = view; }

private:
	uint32_t _character_id;
	uint32_t _account_id;
	uint16_t _slot;
	std::string _name;
	bool _online;
	character_gender_types _gender;

	std::shared_ptr<Access> _access_data;
	std::shared_ptr<Companion> _companion_data;
	std::shared_ptr<Family> _family_data;
	std::shared_ptr<Group> _group_data;
	std::shared_ptr<Misc> _misc_data;
	std::shared_ptr<Position> _position_data;
	std::shared_ptr<Status> _status_data;
	std::shared_ptr<UISettings> _ui_settings;
	std::shared_ptr<View> _view_data;
};
}
}
}

#endif // HORIZON_MODELS_CHARACTERS_CHARACTER_HPP
