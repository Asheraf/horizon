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

#ifndef HORIZON_SESSIONDATA_H
#define HORIZON_SESSIONDATA_H

#include "Server/Common/Horizon.hpp"
#include <ctime>

class SessionData
{
public:
	SessionData() { };
	~SessionData() { };

	SessionData(uint32_t _auth_code, uint32_t _client_version, uint8_t _client_type, uint32_t _game_account_id)
	: _auth_code(_auth_code), _game_account_id(_game_account_id), _client_version(_client_version), _client_type(_client_type)
	{
		//
	}

	/**
	 * Load all fields from the database into this instance.
	 * @param server
	 * @param char_id
	 * @return
	 */
	bool load(Server *server, uint32_t game_account_id)
	{
		std::string query = "SELECT `auth_code`, `client_version`, `client_type`, `character_slots`, `group_id`, `connect_time` FROM `session_data` WHERE game_account_id = ?";

		try {
			auto s = server->get_mysql_client()->getSession();
			auto record = s.sql(query).bind(game_account_id).execute().fetchOne();

			if (record) {
				set_game_account_id(game_account_id);
				set_auth_code(record[0].get<int>());
				set_client_version(record[1].get<int>());
				set_client_type(record[2].get<int>());
				set_character_slots(record[3].get<int>());
				set_group_id(record[4].get<int>());
				set_connect_time(record[5].get<int>());

				s.close();
				return true;
			}
			s.close();
		} catch (const mysqlx::Error &e) {
			CoreLog->warn("SessionData::load: {}", e.what());
		}

		return false;
	}

	void save(Server *server)
	{
		std::string query = "REPLACE INTO `session_data` (`auth_code`, `game_account_id`, `client_version`, `client_type`, `character_slots`, `group_id`, `connect_time`) VALUES (?, ?, ?, ?, ?, ?, ?)";

		try {
			auto s = server->get_mysql_client()->getSession();
			s.sql(query).bind(get_auth_code(),
							  get_game_account_id(),
							  get_client_version(),
							  get_client_type(),
							  get_character_slots(),
							  get_group_id(),
							  get_connect_time())
						.execute();
			s.close();
		} catch (const mysqlx::Error &e) {
			CoreLog->warn("SessionData::save: {}", e.what());
		}
	}

	void remove(Server *server)
	{
		std::string query = "DELETE FROM `session_data` WHERE game_account_id = ?";

		try {
			auto s = server->get_mysql_client()->getSession();
			s.sql(query).bind(get_game_account_id()).execute();
			s.close();
		} catch (const mysqlx::Error &e) {
			CoreLog->warn("SessionData::remove: {}", e.what());
		}
	}

	/* Auth Code */
	uint32_t get_auth_code() const { return _auth_code; }
	void set_auth_code(uint32_t code) { _auth_code = code; }
	/* Client Version */
	uint32_t get_client_version() const { return _client_version; }
	void set_client_version(uint32_t version) { _client_version = version; }
	/* Client Type */
	uint8_t get_client_type() const { return _client_type; }
	void set_client_type(uint8_t type) { _client_type = type; }
	/* Game Account ID */
	uint32_t get_game_account_id() const { return _game_account_id; }
	void set_game_account_id(uint32_t account_id) { _game_account_id = account_id; }
	/* Character Slots */
	uint32_t get_character_slots() const { return _character_slots; }
	void set_character_slots(uint32_t slots) { _character_slots = slots; }
	/* Group ID */
	uint32_t get_group_id() const { return _group_id; }
	void set_group_id(uint32_t id) { _group_id = id; }
	/* Connect Time (Zone Only) */
	uint32_t get_connect_time() const { return _connect_time; }
	void set_connect_time(uint32_t time) { _connect_time = time; }

private:
	uint32_t _auth_code;
	uint32_t _game_account_id;
	uint32_t _client_version;
	uint8_t _client_type;
	uint32_t _character_slots;
	uint32_t _group_id;
	uint32_t _connect_time;
};

#endif //HORIZON_SESSIONDATA_H
