/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 * Copyright (c) 2019 Horizon Dev Team.
 *
 * Base Author - Sxyz (sagunxp@gmail.com)
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 **************************************************/

#ifndef HORIZON_SESSIONDATA_HPP
#define HORIZON_SESSIONDATA_HPP

#include <ctime>
#include <cstdint>

class Server;

namespace Horizon
{
namespace Models
{
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
	bool load(Server *server, uint32_t game_account_id);

	bool save(Server *server);

	bool remove(Server *server);

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
}
}

#endif //HORIZON_SESSIONDATA_HPP
