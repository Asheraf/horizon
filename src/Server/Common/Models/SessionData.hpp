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
		pkt.game_account_id = getGameAccountID();
		pkt.auth_code = getAuthCode();
		pkt.client_type = getClientType();
		pkt.client_version = getClientVersion();
		pkt.group_id = getGroupID();
		pkt.character_slots = getCharacterSlots();

		return *this;
	}

	/**
	 * Serialize into struct.
	 */
	SessionData &operator << (PACKET_INTER_SESSION &pkt)
	{
		setGameAccountID(pkt.game_account_id);
		setAuthCode(pkt.auth_code);
		setClientVersion(pkt.client_version);
		setClientType(pkt.client_type);
		setCharacterSlots(pkt.character_slots);
		setGroupID(pkt.group_id);
		
		return *this;
	}

	/* Auth Code */
	uint32_t getAuthCode() const { return _auth_code; }
	void setAuthCode(uint32_t code) { _auth_code = code; }
	/* Client Version */
	uint32_t getClientVersion() const { return _client_version; }
	void setClientVersion(uint32_t version) { _client_version = version; }
	/* Client Type */
	uint8_t getClientType() const { return _client_type; }
	void setClientType(uint8_t type) { _client_type = type; }
	/* Game Account ID */
	uint32_t getGameAccountID() const { return _game_account_id; }
	void setGameAccountID(uint32_t account_id) { _game_account_id = account_id; }
	/* Character Slots */
	uint32_t getCharacterSlots() const { return _character_slots; }
	void setCharacterSlots(uint32_t slots) { _character_slots = slots; }
	/* Group ID */
	uint32_t getGroupID() const { return _group_id; }
	void setGroupID(uint32_t id) { _group_id = id; }
	/* Connect Time (Zone Only) */
	uint32_t getConnectTime() const { return _connect_time; }
	void setConnectTime(uint32_t time) { _connect_time = time; }

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
