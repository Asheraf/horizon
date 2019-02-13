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

#ifndef HORIZON_COMMON_RAGEXE20131030_PACKETHANDLER_HPP
#define HORIZON_COMMON_RAGEXE20131030_PACKETHANDLER_HPP

#include "Server/Common/PacketBuffer.hpp"
#include "PacketHandlerRagexe20130612.hpp"
#include "Server/Common/Packets/Ragexe/Packets.hpp"

#include "Server/Common/Packets/Ragexe/PacketStructs.hpp"

namespace Horizon
{
namespace Common
{
namespace Ragexe20131030
{
enum packets
{
	SC_LOGIN_ANSWER_WITH_ID = 0x09e0,
};

#pragma pack(push, 1)
struct PACKET_SC_LOGIN_ANSWER_WITH_ID : public Horizon::Common::Ragexe::PACKET_SC_LOGIN_ANSWER_WITH_ID
{
	PACKET_SC_LOGIN_ANSWER_WITH_ID(uint16_t packet_id = SC_LOGIN_ANSWER_WITH_ID) : Horizon::Common::Ragexe::PACKET_SC_LOGIN_ANSWER_WITH_ID(packet_id) { }
};
#pragma pack(pop)
}

class CommonSocket;

class PacketHandlerRagexe20131030 : public PacketHandlerRagexe20130612
{
public:
	PacketHandlerRagexe20131030(std::shared_ptr<CommonSocket> socket);
	~PacketHandlerRagexe20131030();

	virtual void initialize_handlers() override;

};
}
}

#endif /* HORIZON_COMMON_Ragexe20131030_PACKETHANDLER_HPP */
