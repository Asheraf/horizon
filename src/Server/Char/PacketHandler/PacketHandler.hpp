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
	virtual void Handle_CHAR_CONNECT(PACKET_CHAR_CONNECT &pkt);
	virtual void Handle_CHAR_KEEP_ALIVE(PacketBuffer &buf);
	virtual void Handle_CHAR_CREATE(PacketBuffer &buf);
	virtual void Handle_CHAR_DELETE_START(PacketBuffer &buf);
	virtual void Handle_CHAR_DELETE_ACCEPT(PacketBuffer &buf);
	virtual void Handle_CHAR_DELETE_CANCEL(PacketBuffer &buf);
	virtual void Handle_CHAR_SELECT(PacketBuffer &buf);
	/**
	 * Senders
	 */
	virtual void Send_CHAR_CONNECT_ERROR(character_connect_errors error);
	virtual void Send_CHAR_ACCOUNT_ID();
	virtual void Send_CHAR_SLOT_INFO_ACK();
	virtual void Send_CHAR_LIST_ACK();
	virtual void Send_CHAR_RESEND_CHAR_LIST();
	virtual void Send_CHAR_BAN_LIST_ACK();
	virtual void Send_CHAR_PINCODE_STATE_ACK();
	virtual void Send_CHAR_CREATE_SUCCESS_ACK(std::shared_ptr<Character> character);
	virtual void Send_CHAR_DELETE_START_ACK(uint32_t character_id, character_delete_result result, time_t deletion_date);
	virtual void Send_CHAR_DELETE_ACCEPT_ACK(uint32_t character_id, character_delete_accept_result result);
	virtual void Send_CHAR_DELETE_CANCEL_ACK(uint32_t character_id, bool success);
	virtual void Send_CHAR_CREATE_ERROR_ACK(char_create_error_types error);
	virtual void Send_CHAR_SEND_ZONE_INFO(std::shared_ptr<Character> character);
};
}
}

#endif // HORIZON_CHAR_PACKETHANDLER_HPP
