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
#include "Server/Common/Base/PacketHandler/InterPackets.hpp"
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
	 * Serialize into struct.
	 */
	SessionData &operator >> (PACKET_INTER_SESSION &pkt)
	{
		pkt.game_account_id = get_game_account_id();
		pkt.auth_code = get_auth_code();
		pkt.client_type = get_client_type();
		pkt.client_version = get_client_version();
		pkt.group_id = get_group_id();
		pkt.character_slots = get_character_slots();

		return *this;
	}

	/**
	 * Serialize into struct.
	 */
	SessionData &operator << (PACKET_INTER_SESSION &pkt)
	{
		set_game_account_id(pkt.game_account_id);
		set_auth_code(pkt.auth_code);
		set_client_version(pkt.client_version);
		set_client_type(pkt.client_type);
		set_character_slots(pkt.character_slots);
		set_group_id(pkt.group_id);
		
		return *this;
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
