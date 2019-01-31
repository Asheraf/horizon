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

#ifndef HORIZON_CHAR_PACKETHANDLER_HPP
#define HORIZON_CHAR_PACKETHANDLER_HPP

#include "Server/Common/PacketBuffer.hpp"
#include "Server/Common/Base/PacketHandler/PacketHandler.hpp"
#include "Server/Char/PacketHandler/Packets.hpp"

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

using namespace Horizon::Models::Character;

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
	virtual bool Handle_CH_CONNECT(PACKET_CH_CONNECT &pkt);
	virtual bool Handle_CH_KEEP_ALIVE(PacketBuffer &buf);
	virtual bool Handle_CH_CREATE(PacketBuffer &buf);
	virtual bool Handle_CH_DELETE_START(PacketBuffer &buf);
	virtual bool Handle_CH_DELETE_ACCEPT(PacketBuffer &buf);
	virtual bool Handle_CH_DELETE_CANCEL(PacketBuffer &buf);
	virtual bool Handle_CH_SELECT(PacketBuffer &buf);
	/**
	 * Senders
	 */
	virtual void Send_HC_CONNECT_ERROR(character_connect_errors error);
	virtual void Send_HC_ACCOUNT_ID();
	virtual void Send_HC_SLOT_INFO_ACK();
	virtual void Send_HC_CHAR_LIST_ACK();
	virtual void Send_HC_RESEND_CHAR_LIST();
	virtual void Send_HC_BAN_LIST_ACK();
	virtual void Send_HC_PINCODE_STATE_ACK();
	virtual void Send_HC_CREATE_SUCCESS_ACK(std::shared_ptr<Character> character);
	virtual void Send_HC_DELETE_START_ACK(uint32_t character_id, character_delete_result result, time_t deletion_date);
	virtual void Send_HC_DELETE_ACCEPT_ACK(uint32_t character_id, character_delete_accept_result result);
	virtual void Send_HC_DELETE_CANCEL_ACK(uint32_t character_id, bool success);
	virtual void Send_HC_CREATE_ERROR_ACK(char_create_error_types error);
	virtual void Send_HC_SEND_ZONE_INFO(std::shared_ptr<Character> character);

	bool session_has_expired() { return !_last_ping_time ? false : std::difftime(std::time(0), _last_ping_time) > 20; }
private:
	std::time_t _last_ping_time{0};
};
}
}

#endif // HORIZON_CHAR_PACKETHANDLER_HPP
