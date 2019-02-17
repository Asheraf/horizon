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
 * Base Author - Sagun Khosla. (sagunxp@gmail.com)
 *
 * Under a proprietary license this file is not for use
 * or viewing without permission.
 **************************************************/

#ifndef HORIZON_CHAR_PACKETHANDLER_HPP
#define HORIZON_CHAR_PACKETHANDLER_HPP

#include "Server/Common/PacketBuffer.hpp"
#include "Server/Common/Base/PacketHandler/PacketHandler.hpp"

#include <memory>

namespace Horizon
{
	namespace Models
	{
		namespace Character
		{
			class Character;
		}
	}
}

class PacketBuffer;
class SessionData;

namespace Horizon
{
namespace Char
{
class CharSocket;
class PacketHandler : public Horizon::Base::PacketHandler<CharSocket>
{
public:
	explicit PacketHandler(std::shared_ptr<CharSocket> socket);
	virtual ~PacketHandler();

	virtual void initialize_handlers();
	/**
	 * Handlers
	 */
	virtual bool Handle_CH_ENTER(PacketBuffer &pkt);
	virtual bool Handle_CH_UNKNOWN_PING(PacketBuffer &buf);
	virtual bool Handle_CH_MAKE_CHAR(PacketBuffer &buf);
	virtual bool Handle_CH_DELETE_CHAR(PacketBuffer &buf);
	virtual bool Handle_CH_DELETE_CHAR3(PacketBuffer &buf);
	virtual bool Handle_CH_DELETE_CHAR3_RESERVED(PacketBuffer &buf);
	virtual bool Handle_CH_DELETE_CHAR3_CANCEL(PacketBuffer &buf);
	virtual bool Handle_CH_SELECT_CHAR(PacketBuffer &buf);

	virtual character_delete_result delete_character(uint32_t character_id);
	/**
	 * Senders
	 */
	virtual void Send_HC_REFUSE_ENTER(character_connect_errors error);
	virtual void Send_HC_ACCOUNT_ID();
	virtual void Send_HC_ACCEPT_ENTER2();
	virtual void Send_HC_ACCEPT_ENTER();
	virtual void Send_HC_BLOCK_CHARACTER();
	virtual void Send_HC_SECOND_PASSWD_LOGIN();
	virtual void Send_HC_ACCEPT_MAKECHAR(std::shared_ptr<Horizon::Models::Character::Character> character);
	virtual void Send_HC_DELETE_CHAR3_RESERVED(uint32_t character_id, character_delete_result result, time_t deletion_date);
	virtual void Send_HC_DELETE_CHAR3(uint32_t character_id, character_delete_accept_result result);
	virtual void Send_HC_DELETE_CHAR3_CANCEL(uint32_t character_id, bool success);
	virtual void Send_HC_REFUSE_MAKECHAR(char_create_error_types error);
	virtual void Send_HC_NOTIFY_ZONESVR(std::shared_ptr<Horizon::Models::Character::Character> character);

	bool session_has_expired() { return !_last_ping_time ? false : std::difftime(std::time(0), _last_ping_time) > 20; }
private:
	std::time_t _last_ping_time{0};
};
}
}

#endif // HORIZON_CHAR_PACKETHANDLER_HPP
