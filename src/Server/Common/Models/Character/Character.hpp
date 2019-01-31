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
#include <mysqlx/xdevapi.h>

enum character_gender_types
{
	CHARACTER_GENDER_MALE,
	CHARACTER_GENDER_FEMALE
};

enum character_save_mask
{
	CHAR_SAVE_BASE_DATA         = 0x001,
	CHAR_SAVE_ACCESS_DATA       = 0x002,
	CHAR_SAVE_VIEW_DATA         = 0x004,
	CHAR_SAVE_FAMILY_DATA       = 0x008,
	CHAR_SAVE_COMPANION_DATA    = 0x010,
	CHAR_SAVE_MISC_DATA         = 0x020,
	CHAR_SAVE_POSITION_DATA     = 0x040,
	CHAR_SAVE_UI_SETTINGS_DATA  = 0x080,
	CHAR_SAVE_GROUP_DATA        = 0x100,
	CHAR_SAVE_STATUS_DATA       = 0x200,
	CHAR_SAVE_ALL               = 0xfff,
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
	Character(uint32_t char_id) : _character_id(char_id)
	{ }

	// Creation constructor without char_id.
	Character(uint32_t account_id, std::string const &name, uint8_t slot, character_gender_types gender)
	: _account_id(account_id), _slot(slot), _name(name), _online(false), _gender(gender), _deleted_at(0)
	{ }

	~Character() { }

	/**
	 * Load all fields from the database into this instance.
	 * @param server
	 * @param char_id
	 * @return
	 */
	bool load(Server *server, uint32_t char_id)
	{
		std::string query = "SELECT `account_id`, `slot`, `name`, `gender`, `deleted_at` FROM `characters` WHERE id = ?";

		try {
			auto s = server->get_mysql_client()->getSession();
			auto record = s.sql(query).bind(char_id).execute().fetchOne();

			if (record) {
				set_character_id(char_id);
				set_account_id(record[0]);
				set_slot((uint16_t) record[1].get<int>());
				set_name(record[2]);
				std::string gender = record[3].get<std::string>();
				if (gender.compare("M") == 0)
					set_gender(CHARACTER_GENDER_MALE);
				else if (gender.compare("F") == 0)
					set_gender(CHARACTER_GENDER_FEMALE);

				if (record[4].getType() > 0)
					set_deleted_at(record[4].get<long long>());

				s.close();
				return true;
			}
			s.close();
		} catch (const mysqlx::Error &e) {
			CoreLog->warn("Character::load: {}", e.what());
		}

		return false;
	}

	bool load_all(Server *server, uint32_t char_id)
	{
		if (!load(server, char_id))
			return false;

		set_status_data(std::make_shared<Status>(char_id));

		if (!get_status_data()->load(server, char_id))
			return false;

		set_access_data(std::make_shared<Access>(char_id));

		if (!get_access_data()->load(server, char_id))
			return false;

		set_view_data(std::make_shared<View>(char_id));

		if (!get_view_data()->load(server, char_id))
			return false;

		set_family_data(std::make_shared<Family>(char_id));

		if (!get_family_data()->load(server, char_id))
			return false;

		set_companion_data(std::make_shared<Companion>(char_id));

		if (!get_companion_data()->load(server, char_id))
			return false;

		set_group_data(std::make_shared<Group>(char_id));

		if (!get_group_data()->load(server, char_id))
			return false;

		set_misc_data(std::make_shared<Misc>(char_id));

		if (!get_misc_data()->load(server, char_id))
			return false;

		set_position_data(std::make_shared<Position>(char_id));

		if (!get_position_data()->load(server, char_id))
			return false;

		set_ui_settings(std::make_shared<UISettings>(char_id));

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
		try {
			auto s = server->get_mysql_client()->getSession();
			auto table = s.getDefaultSchema().getTable("characters");
			auto q = table.update()
				.set("account_id", get_account_id())
				.set("slot", get_slot())
				.set("name", get_name())
				.set("online", is_online())
				.set("gender", get_gender() == CHARACTER_GENDER_MALE ? "M" : "F");

			if (get_deleted_at())
				q.set("deleted_at", mysqlx::internal::expr("FROM_UNIXTIME(" + std::to_string(get_deleted_at()) + ")"));

				q.where("id = :id")
				.bind("id", get_character_id())
				.execute();
			s.close();
		} catch (const mysqlx::Error &e) {
			CoreLog->warn("Character::save: {}", e.what());
		}
	}

	void create(Server *server)
	{
		int char_id = 0;
		std::string query = "SELECT `id` FROM `characters` ORDER BY `id` DESC LIMIT 1;";

		try {
			auto s = server->get_mysql_client()->getSession();
			auto record = s.sql(query).execute().fetchOne();

			if (record) {
				char_id = record[0].get<int>() + 1;
			} else {
				char_id = 1;
			}

			set_character_id(char_id);

			std::string gender = get_gender() == CHARACTER_GENDER_MALE ? "M" : "F";

			auto table = s.getDefaultSchema().getTable("characters");
			table.insert("id", "account_id", "slot", "name", "gender")
				.values(char_id, get_account_id(), get_slot(), get_name(), gender)
				.execute();

		} catch (const mysqlx::Error &e) {
			CoreLog->warn("Character::create: {}", e.what());
		}

		int save_mask = 0x0;

		set_status_data(std::make_shared<Status>(char_id));
		save_mask |= CHAR_SAVE_STATUS_DATA;

		set_access_data(std::make_shared<Access>(char_id));
		save_mask |= CHAR_SAVE_ACCESS_DATA;

		set_view_data(std::make_shared<View>(char_id));
		save_mask |= CHAR_SAVE_VIEW_DATA;

		set_family_data(std::make_shared<Family>(char_id));
		save_mask |= CHAR_SAVE_FAMILY_DATA;

		set_companion_data(std::make_shared<Companion>(char_id));
		save_mask |= CHAR_SAVE_COMPANION_DATA;

		set_group_data(std::make_shared<Group>(char_id));
		save_mask |= CHAR_SAVE_GROUP_DATA;

		set_misc_data(std::make_shared<Misc>(char_id));
		save_mask |= CHAR_SAVE_MISC_DATA;

		set_position_data(std::make_shared<Position>(char_id));
		save_mask |= CHAR_SAVE_POSITION_DATA;

		set_ui_settings(std::make_shared<UISettings>(char_id));
		save_mask |= CHAR_SAVE_UI_SETTINGS_DATA;

		save(server, save_mask);
	}

	void save(Server *server, int type)
	{
		if (type & CHAR_SAVE_BASE_DATA)
			save(server);

		if (type & CHAR_SAVE_STATUS_DATA)
			get_status_data()->save(server);

		if (type & CHAR_SAVE_ACCESS_DATA)
			get_access_data()->save(server);

		if (type & CHAR_SAVE_VIEW_DATA)
			get_view_data()->save(server);

		if (type & CHAR_SAVE_FAMILY_DATA)
			get_family_data()->save(server);

		if (type & CHAR_SAVE_COMPANION_DATA)
			get_companion_data()->save(server);

		if (type & CHAR_SAVE_GROUP_DATA)
			get_group_data()->save(server);

		if (type & CHAR_SAVE_MISC_DATA)
			get_misc_data()->save(server);

		if (type & CHAR_SAVE_POSITION_DATA)
			get_position_data()->save(server);

		if (type & CHAR_SAVE_UI_SETTINGS_DATA)
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
	void set_deleted_at(std::time_t time) { _deleted_at = time; }
	bool get_deleted_at() { return _deleted_at; }

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
	std::time_t _deleted_at{0};

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
