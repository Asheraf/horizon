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

#ifndef HORIZON_COMMON_RE20131030_PACKETHANDLER_HPP
#define HORIZON_COMMON_RE20131030_PACKETHANDLER_HPP

#include "Server/Common/PacketBuffer.hpp"
#include "PacketHandlerRE20130612.hpp"
#include "Server/Common/Packets/RE/Packets.hpp"

#include "Server/Common/Packets/RE/PacketStructs.hpp"

namespace Horizon
{
namespace Common
{
namespace RE20131030
{
enum packets
{
	SC_LOGIN_ANSWER_WITH_ID = 0x09e0,
};

#pragma pack(push, 1)
struct PACKET_SC_LOGIN_ANSWER_WITH_ID : public Horizon::Common::RE::PACKET_SC_LOGIN_ANSWER_WITH_ID
{
	PACKET_SC_LOGIN_ANSWER_WITH_ID(uint16_t packet_id = SC_LOGIN_ANSWER_WITH_ID) : Horizon::Common::RE::PACKET_SC_LOGIN_ANSWER_WITH_ID(packet_id) { }
};
#pragma pack(pop)
}

class CommonSocket;

class PacketHandlerRE20131030 : public PacketHandlerRE20130612
{
public:
	PacketHandlerRE20131030(std::shared_ptr<CommonSocket> socket);
	~PacketHandlerRE20131030();

	virtual void initialize_handlers() override;

};
}
}

#endif /* HORIZON_COMMON_RE20131030_PACKETHANDLER_HPP */
