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

#ifndef HORIZON_COMMON_RE20130605_PACKETHANDLER_HPP
#define HORIZON_COMMON_RE20130605_PACKETHANDLER_HPP

#include "Server/Common/PacketBuffer.hpp"
#include "Server/Common/Packets/PacketHandler.hpp"
#include "Server/Common/Packets/RE/Packets.hpp"

#include "Server/Common/Packets/RE/PacketStructs.hpp"

namespace Horizon
{
namespace Common
{
namespace RE20130605
{
enum packets
{
	CS_LOGIN_QUERY = 0x09c5,
	SC_LOGIN_ANSWER = 0x09c6,
	SC_LOGIN_ERROR = 0x09c7,
};

#pragma pack(push, 1)
struct PACKET_CS_LOGIN_QUERY : public Horizon::Common::RE::PACKET_CS_LOGIN_QUERY
{
	PACKET_CS_LOGIN_QUERY(uint16_t packet_id = CS_LOGIN_QUERY) : Horizon::Common::RE::PACKET_CS_LOGIN_QUERY(packet_id) { }
};
struct PACKET_SC_LOGIN_ANSWER : public Horizon::Common::RE::PACKET_SC_LOGIN_ANSWER
{
	PACKET_SC_LOGIN_ANSWER(uint16_t packet_id = SC_LOGIN_ANSWER) : Horizon::Common::RE::PACKET_SC_LOGIN_ANSWER(packet_id) { }
};
struct PACKET_SC_LOGIN_ERROR : public Horizon::Common::RE::PACKET_SC_LOGIN_ERROR
{
	PACKET_SC_LOGIN_ERROR(uint16_t packet_id = SC_LOGIN_ERROR) : Horizon::Common::RE::PACKET_SC_LOGIN_ERROR(packet_id) { }
};
#pragma pack(pop)
}

class CommonSocket;

class PacketHandlerRE20130605 : public PacketHandler
{
public:
	PacketHandlerRE20130605(std::shared_ptr<CommonSocket> socket);
	~PacketHandlerRE20130605();

	virtual void initialize_handlers() override;

};
}
}

#endif /* HORIZON_COMMON_RE20130605_PACKETHANDLER_HPP */
