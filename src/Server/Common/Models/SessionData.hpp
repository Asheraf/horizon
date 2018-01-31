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

	SessionData(int _auth_code, uint32_t _client_version, uint8_t _client_type, uint32_t _game_account_id)
		: _auth_code(_auth_code), _client_version(_client_version), _client_type(_client_type), _game_account_id(
		_game_account_id)
	{
		//
	}

	/* Auth Code */
	int getAuthCode() const { return _auth_code; }
	void setAuthCode(int auth_code) { SessionData::_auth_code = auth_code; }
	/* Client Version */
	uint32_t getClientVersion() const { return _client_version; }
	void setClientVersion(uint32_t client_version) { SessionData::_client_version = client_version; }
	/* Client Type */
	uint8_t getClientType() const { return _client_type; }
	void setClientType(uint8_t client_type) { SessionData::_client_type = client_type; }
	/* Game Account ID */
	uint32_t getGameAccountId() const { return _game_account_id; }
	void setGameAccountId(uint32_t game_account_id) { SessionData::_game_account_id = game_account_id; }
	/* Character Slots */
	uint32_t getCharacterSlots() const { return _character_slots; }
	void setSharacterSlots(uint32_t _character_slots) { SessionData::_character_slots = _character_slots; }
	/* Group ID */
	uint32_t getGroupId() const { return _group_id; }
	void setGroupId(uint32_t _group_id) { SessionData::_group_id = _group_id; }

private:
	int _auth_code;
	uint32_t _game_account_id;
	uint32_t _client_version;
	uint8_t _client_type;
	uint32_t _character_slots;
	uint32_t _group_id;
};

#endif //HORIZON_SESSIONDATA_H
