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

#ifndef HORIZON_COMMON_RAGEXE20080624_PACKETHANDLER_HPP
#define HORIZON_COMMON_RAGEXE20080624_PACKETHANDLER_HPP

#include "Server/Common/PacketBuffer.hpp"
#include "Server/Common/Packets/PacketHandler.hpp"
#include "Server/Common/Packets/Ragexe/Packets.hpp"

#include "Server/Common/Packets/Ragexe/PacketStructs.hpp"

namespace Horizon
{
namespace Common
{
namespace Ragexe20080624
{
enum packets
{
	AHC_GAME_GUARD = 0x03dd,
	CAH_ACK_GAME_GUARD = 0x03de,
};

#pragma pack(push, 1)
struct PACKET_AHC_GAME_GUARD : public Horizon::Common::Ragexe::PACKET_AHC_GAME_GUARD
{
	PACKET_AHC_GAME_GUARD(uint16_t packet_id = AHC_GAME_GUARD) : Horizon::Common::Ragexe::PACKET_AHC_GAME_GUARD(packet_id) { }
};
struct PACKET_CAH_ACK_GAME_GUARD : public Horizon::Common::Ragexe::PACKET_CAH_ACK_GAME_GUARD
{
	PACKET_CAH_ACK_GAME_GUARD(uint16_t packet_id = CAH_ACK_GAME_GUARD) : Horizon::Common::Ragexe::PACKET_CAH_ACK_GAME_GUARD(packet_id) { }
};
#pragma pack(pop)
}

class CommonSocket;

class PacketHandlerRagexe20080624 : public PacketHandler
{
public:
	PacketHandlerRagexe20080624(std::shared_ptr<CommonSocket> socket);
	~PacketHandlerRagexe20080624();

	virtual void initialize_handlers() override;

};
}
}

#endif /* HORIZON_COMMON_Ragexe20080624_PACKETHANDLER_HPP */
