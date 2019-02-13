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

#ifndef HORIZON_COMMON_RAGEXE20130612_PACKETHANDLER_HPP
#define HORIZON_COMMON_RAGEXE20130612_PACKETHANDLER_HPP

#include "Server/Common/PacketBuffer.hpp"
#include "PacketHandlerRagexe20130605.hpp"
#include "Server/Common/Packets/Ragexe/Packets.hpp"

#include "Server/Common/Packets/Ragexe/PacketStructs.hpp"

namespace Horizon
{
namespace Common
{
namespace Ragexe20130612
{
enum packets
{
	SC_LOGIN_ERROR = 0x09c7,
	SC_SOCT = 0x09c9,
};

#pragma pack(push, 1)
struct PACKET_SC_LOGIN_ERROR : public Horizon::Common::Ragexe20130605::PACKET_SC_LOGIN_ERROR
{
	PACKET_SC_LOGIN_ERROR(uint16_t packet_id = SC_LOGIN_ERROR) : Horizon::Common::Ragexe20130605::PACKET_SC_LOGIN_ERROR(packet_id) { }
};
struct PACKET_SC_SOCT : public Horizon::Common::Ragexe::PACKET_SC_SOCT
{
	PACKET_SC_SOCT(uint16_t packet_id = SC_SOCT) : Horizon::Common::Ragexe::PACKET_SC_SOCT(packet_id) { }
};
#pragma pack(pop)
}

class CommonSocket;

class PacketHandlerRagexe20130612 : public PacketHandlerRagexe20130605
{
public:
	PacketHandlerRagexe20130612(std::shared_ptr<CommonSocket> socket);
	~PacketHandlerRagexe20130612();

	virtual void initialize_handlers() override;

};
}
}

#endif /* HORIZON_COMMON_Ragexe20130612_PACKETHANDLER_HPP */
