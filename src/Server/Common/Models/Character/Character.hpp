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
		auto sql = server->mysql_borrow();
		bool ret = false;

		try {
			sql::PreparedStatement *pstmt = sql->getConnection()->prepareStatement(query);
			pstmt->setInt(1, char_id);
			sql::ResultSet *res = pstmt->executeQuery();

			if (res != nullptr && res->next()) {
				/**
				 * Create Game Account Data
				 */
				set_character_id(char_id);
				set_account_id(res->getUInt("account_id"));
				set_slot((uint16_t) res->getUInt("slot"));
				set_name(res->getString("name"));
				set_gender((character_gender_types) res->getInt("gender"));
				set_deleted(res->getBoolean("deleted"));
				ret = true;
			}

			delete res;
			delete pstmt;
		} catch (sql::SQLException &e) {
			DBLog->error("Models::Character::Character::LoadFromDatabase: {}", e.what());
		}

		server->mysql_unborrow(sql);

		return ret;
	}

	bool load_all(Server *server, uint32_t char_id)
	{
		if (!load(server, char_id))
			return false;

		if (get_status_data() == nullptr)
			set_status_data(std::make_shared<Status>());
		if (get_access_data() == nullptr)
			set_access_data(std::make_shared<Access>());
		if (get_view_data() == nullptr)
			set_view_data(std::make_shared<View>());
		if (get_family_data() == nullptr)
			set_family_data(std::make_shared<Family>());
		if (get_companion_data() == nullptr)
			set_companion_data(std::make_shared<Companion>());
		if (get_group_data() == nullptr)
			set_group_data(std::make_shared<Group>());
		if (get_misc_data() == nullptr)
			set_misc_data(std::make_shared<Misc>());
		if (get_position_data() == nullptr)
			set_position_data(std::make_shared<Position>());
		if (get_ui_settings() == nullptr)
			set_ui_settings(std::make_shared<UISettings>());

		if (!get_status_data()->load(server, char_id))
			return false;
		if (!get_access_data()->load(server, char_id))
			return false;
		if (!get_view_data()->load(server, char_id))
			return false;
		if (!get_family_data()->load(server, char_id))
			return false;
		if (!get_companion_data()->load(server, char_id))
			return false;
		if (!get_group_data()->load(server, char_id))
			return false;
		if (!get_misc_data()->load(server, char_id))
			return false;
		if (!get_position_data()->load(server, char_id))
			return false;
		if (!get_ui_settings()->load(server, char_id))
			return false;

		return true;
	}

	/**
	 * @brief Save this model to the database in its current state.
	 * @param[in|out] server   instance of the server object used to borrow mysql connections.
	 */
	void save(Server *server)
	{
		auto sql = server->mysql_borrow();
		std::string query = "REPLACE INTO `characters` "
		"(`id`, `account_id`, `slot`, `name`, `online`, `gender`, `deleted`) "
		"VALUES (?, ?, ?, ?, ?, ?, ?);";

		try {
			sql::PreparedStatement *pstmt = sql->getConnection()->prepareStatement(query);
			pstmt->setInt(1, get_character_id());
			pstmt->setInt(2, get_account_id());
			pstmt->setInt(3, get_slot());
			pstmt->setString(4, get_name());
			pstmt->setBoolean(5, is_online());
			pstmt->setString(6, (get_gender() == CHARACTER_GENDER_MALE ? "M" : "F"));
			pstmt->setBoolean(7, is_deleted());
			pstmt->executeUpdate();
			delete pstmt;
		} catch (sql::SQLException &e) {
			DBLog->error("SQLException: {}", e.what());
		}

		server->mysql_unborrow(sql);
	}

	void create(Server *server)
	{
		int char_id = 0;
		auto sql = server->mysql_borrow();
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

		server->mysql_unborrow(sql);

		if (get_status_data() == nullptr)
			set_status_data(std::make_shared<Status>());
		if (get_access_data() == nullptr)
			set_access_data(std::make_shared<Access>());
		if (get_view_data() == nullptr)
			set_view_data(std::make_shared<View>());
		if (get_family_data() == nullptr)
			set_family_data(std::make_shared<Family>());
		if (get_companion_data() == nullptr)
			set_companion_data(std::make_shared<Companion>());
		if (get_group_data() == nullptr)
			set_group_data(std::make_shared<Group>());
		if (get_misc_data() == nullptr)
			set_misc_data(std::make_shared<Misc>());
		if (get_position_data() == nullptr)
			set_position_data(std::make_shared<Position>());
		if (get_ui_settings() == nullptr)
			set_ui_settings(std::make_shared<UISettings>());

		set_character_id(char_id);
		get_status_data()->set_character_id(char_id);
		get_access_data()->set_character_id(char_id);
		get_view_data()->set_character_id(char_id);
		get_family_data()->set_character_id(char_id);
		get_companion_data()->set_character_id(char_id);
		get_group_data()->set_character_id(char_id);
		get_misc_data()->set_character_id(char_id);
		get_position_data()->set_character_id(char_id);
		get_ui_settings()->set_character_id(char_id);
		save_all(server);
	}

	void save_all(Server *server)
	{
		save(server);
		get_status_data()->save(server);
		get_access_data()->save(server);
		get_view_data()->save(server);
		get_family_data()->save(server);
		get_companion_data()->save(server);
		get_group_data()->save(server);
		get_misc_data()->save(server);
		get_position_data()->save(server);
		get_ui_settings()->save(server);
	}

	/* Character ID */
	uint32_t get_character_id() const
	{
		return _character_id;
	}
	void set_character_id(uint32_t id)
	{
		_character_id = id;
	}

	/* Account ID */
	uint32_t get_account_id() const { return _account_id; }
	void set_account_id(uint32_t id) { _account_id = id; }

	/* Slot */
	uint16_t get_slot() const { return _slot; }
	void set_slot(uint16_t slot) { _slot = slot; }

	/* Name */
	const std::string &get_name() const { return _name; }
	void set_name(const std::string &name) { _name = name; }

	/* Online */
	bool is_online() const { return _online; }
	void set_online() { _online = true; }
	void set_offline() { _online = false; }

	/* Gender */
	character_gender_types get_gender() const { return _gender; }
	void set_gender(character_gender_types gender) { _gender = gender; }

	/* Deleted */
	void set_deleted(bool deleted) { _deleted = deleted; }
	bool is_deleted() { return _deleted; }

	/* Access Data*/
	const std::shared_ptr<Access> get_access_data() const { return _access_data; }
	void set_access_data(std::shared_ptr<Access> const &access) { _access_data = access; }

	/* Companion Data*/
	const std::shared_ptr<Companion> get_companion_data() const { return _companion_data; }
	void set_companion_data(std::shared_ptr<Companion> const &companion) { _companion_data = companion; }

	/* Family Data*/
	const std::shared_ptr<Family> get_family_data() const { return _family_data; }
	void set_family_data(std::shared_ptr<Family> const &family) { _family_data = family; }

	/* Group Data*/
	const std::shared_ptr<Group> get_group_data() const { return _group_data; }
	void set_group_data(std::shared_ptr<Group> const &group) { _group_data = group; }

	/* Misc Data*/
	const std::shared_ptr<Misc> get_misc_data() const { return _misc_data; }
	void set_misc_data(std::shared_ptr<Misc> const &misc) { _misc_data = misc; }

	/* Position Data*/
	const std::shared_ptr<Position> get_position_data() const { return _position_data; }
	void set_position_data(std::shared_ptr<Position> const &position) { _position_data = position; }

	/* Status Data*/
	const std::shared_ptr<Status> get_status_data() const { return _status_data; }
	void set_status_data(std::shared_ptr<Status> const &status) { _status_data = status; }

	/* UISettings Data*/
	const std::shared_ptr<UISettings> get_ui_settings() const { return _ui_settings; }
	void set_ui_settings(std::shared_ptr<UISettings> const &settings) { _ui_settings = settings; }

	/* View Data*/
	const std::shared_ptr<View> get_view_data() const { return _view_data; }
	void set_view_data(std::shared_ptr<View> const &view) { _view_data = view; }

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
