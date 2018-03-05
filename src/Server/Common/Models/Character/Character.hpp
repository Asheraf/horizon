/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 * Copyright (c) 2018 Horizon Dev Team.
 *
 * Base Author - Sagun Khosla. (sagunxp@gmail.com)
 *
 * Under a proprietary license this file is not for use
 * or viewing without permission.
 **************************************************/

#ifndef HORIZON_MODELS_CHARACTERS_CHARACTER_HPP
#define HORIZON_MODELS_CHARACTERS_CHARACTER_HPP

#include "Server/Common/Horizon.hpp"
#include "Server/Common/Server.hpp"
#include "Server/Common/Models/Character/Access.hpp"
#include "Server/Common/Models/Character/Companion.hpp"
#include "Server/Common/Models/Character/Family.hpp"
#include "Server/Common/Models/Character/Group.hpp"
#include "Server/Common/Models/Character/Misc.hpp"
#include "Server/Common/Models/Character/Position.hpp"
#include "Server/Common/Models/Character/Status.hpp"
#include "Server/Common/Models/Character/UISettings.hpp"
#include "Server/Common/Models/Character/View.hpp"

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
namespace Character
{
class Character
{
public:
	Character() {}
	~Character() {}

	Character(int32_t account_id, std::string const &name, uint8_t slot, character_gender_types gender)
	: _account_id(account_id), _slot(slot), _name(name), _online(false), _gender(gender), _deleted(false)
	{
		//
	}

	/**
	 * Load all fields from the database into this instance.
	 * @param server
	 * @param char_id
	 * @return
	 */
	bool load(Server *server, uint32_t char_id)
	{
		std::string query = "SELECT * FROM characters WHERE id = ?";
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
				setGender((character_gender_types) res->getInt("gender"));
				setDeleted(res->getBoolean("deleted"));
				ret = true;
			}

			delete res;
			delete pstmt;
		} catch (sql::SQLException &e) {
			DBLog->error("Models::Character::Character::LoadFromDatabase: {}", e.what());
		}

		server->MySQLUnborrow(sql);

		return ret;
	}

	bool loadAll(Server *server, uint32_t char_id)
	{
		if (!load(server, char_id))
			return false;

		if (getStatusData() == nullptr)
			setStatusData(std::make_shared<Status>());
		if (getAccessData() == nullptr)
			setAccessData(std::make_shared<Access>());
		if (getViewData() == nullptr)
			setViewData(std::make_shared<View>());
		if (getFamilyData() == nullptr)
			setFamilyData(std::make_shared<Family>());
		if (getCompanionData() == nullptr)
			setCompanionData(std::make_shared<Companion>());
		if (getGroupData() == nullptr)
			setGroupData(std::make_shared<Group>());
		if (getMiscData() == nullptr)
			setMiscData(std::make_shared<Misc>());
		if (getPositionData() == nullptr)
			setPositionData(std::make_shared<Position>());
		if (getUISettingsData() == nullptr)
			setUISettingsData(std::make_shared<UISettings>());

		if (!getStatusData()->load(server, char_id))
			return false;
		if (!getAccessData()->load(server, char_id))
			return false;
		if (!getViewData()->load(server, char_id))
			return false;
		if (!getFamilyData()->load(server, char_id))
			return false;
		if (!getCompanionData()->load(server, char_id))
			return false;
		if (!getGroupData()->load(server, char_id))
			return false;
		if (!getMiscData()->load(server, char_id))
			return false;
		if (!getPositionData()->load(server, char_id))
			return false;
		if (!getUISettingsData()->load(server, char_id))
			return false;

		return true;
	}

	/**
	 * @brief Save this model to the database in its current state.
	 * @param[in|out] server   instance of the server object used to borrow mysql connections.
	 */
	void save(Server *server)
	{
		auto sql = server->MySQLBorrow();
		std::string query = "REPLACE INTO `characters` "
		"(`id`, `account_id`, `slot`, `name`, `online`, `gender`, `deleted`) "
		"VALUES (?, ?, ?, ?, ?, ?, ?);";

		try {
			sql::PreparedStatement *pstmt = sql->getConnection()->prepareStatement(query);
			pstmt->setInt(1, getCharacterID());
			pstmt->setInt(2, getAccountID());
			pstmt->setInt(3, getSlot());
			pstmt->setString(4, getName());
			pstmt->setBoolean(5, isOnline());
			pstmt->setString(6, (getGender() == CHARACTER_GENDER_MALE ? "M" : "F"));
			pstmt->setBoolean(7, isDeleted());
			pstmt->executeUpdate();
			delete pstmt;
		} catch (sql::SQLException &e) {
			DBLog->error("SQLException: {}", e.what());
		}

		server->MySQLUnborrow(sql);
	}

	void create(Server *server)
	{
		int char_id = 0;
		auto sql = server->MySQLBorrow();
		std::string query = "SELECT `id` as max_id FROM `characters` ORDER BY `id` DESC LIMIT 1;";

		try {
			sql::PreparedStatement *pstmt = sql->getConnection()->prepareStatement(query);
			sql::ResultSet *res = pstmt->executeQuery();

			if (res != nullptr && res->next())
				char_id = res->getInt("max_id") + 1;

			delete pstmt;
			delete res;
		} catch (sql::SQLException &e) {
			DBLog->error("SQLException: {}", e.what());
		}

		if (char_id == 0) {
			DBLog->warn("unable to get char_id for new character.");
			return;
		}

		server->MySQLUnborrow(sql);

		if (getStatusData() == nullptr)
			setStatusData(std::make_shared<Status>());
		if (getAccessData() == nullptr)
			setAccessData(std::make_shared<Access>());
		if (getViewData() == nullptr)
			setViewData(std::make_shared<View>());
		if (getFamilyData() == nullptr)
			setFamilyData(std::make_shared<Family>());
		if (getCompanionData() == nullptr)
			setCompanionData(std::make_shared<Companion>());
		if (getGroupData() == nullptr)
			setGroupData(std::make_shared<Group>());
		if (getMiscData() == nullptr)
			setMiscData(std::make_shared<Misc>());
		if (getPositionData() == nullptr)
			setPositionData(std::make_shared<Position>());
		if (getUISettingsData() == nullptr)
			setUISettingsData(std::make_shared<UISettings>());

		setCharacterID(char_id);
		getStatusData()->setCharacterID(char_id);
		getAccessData()->setCharacterID(char_id);
		getViewData()->setCharacterID(char_id);
		getFamilyData()->setCharacterID(char_id);
		getCompanionData()->setCharacterID(char_id);
		getGroupData()->setCharacterID(char_id);
		getMiscData()->setCharacterID(char_id);
		getPositionData()->setCharacterID(char_id);
		getUISettingsData()->setCharacterID(char_id);
		saveAll(server);
	}

	void saveAll(Server *server)
	{
		save(server);
		getStatusData()->save(server);
		getAccessData()->save(server);
		getViewData()->save(server);
		getFamilyData()->save(server);
		getCompanionData()->save(server);
		getGroupData()->save(server);
		getMiscData()->save(server);
		getPositionData()->save(server);
		getUISettingsData()->save(server);
	}

	/* Character ID */
	uint32_t getCharacterID() const
	{
		return _character_id;
	}
	void setCharacterID(uint32_t id)
	{
		_character_id = id;
	}

	/* Account ID */
	uint32_t getAccountID() const { return _account_id; }
	void setAccountID(uint32_t id) { _account_id = id; }

	/* Slot */
	uint16_t getSlot() const { return _slot; }
	void setSlot(uint16_t slot) { _slot = slot; }

	/* Name */
	const std::string &getName() const { return _name; }
	void setName(const std::string &name) { _name = name; }

	/* Online */
	bool isOnline() const { return _online; }
	void setOnline() { _online = true; }
	void setOffline() { _online = false; }

	/* Gender */
	character_gender_types getGender() const { return _gender; }
	void setGender(character_gender_types gender) { _gender = gender; }

	/* Deleted */
	void setDeleted(bool deleted) { _deleted = deleted; }
	bool isDeleted() { return _deleted; }

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
	uint32_t _character_id{0};
	uint32_t _account_id{0};
	uint16_t _slot{0};
	std::string _name{""};
	bool _online{false};
	character_gender_types _gender{CHARACTER_GENDER_MALE};
	bool _deleted;

	std::shared_ptr<Access> _access_data{nullptr};
	std::shared_ptr<Companion> _companion_data{nullptr};
	std::shared_ptr<Family> _family_data{nullptr};
	std::shared_ptr<Group> _group_data{nullptr};
	std::shared_ptr<Misc> _misc_data{nullptr};
	std::shared_ptr<Position> _position_data{nullptr};
	std::shared_ptr<Status> _status_data{nullptr};
	std::shared_ptr<UISettings> _ui_settings{nullptr};
	std::shared_ptr<View> _view_data{nullptr};
};
}
}
}

#endif // HORIZON_MODELS_CHARACTERS_CHARACTER_HPP
