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

#ifndef HORIZON_ZONE_PACKETHANDLER20141022_HPP
#define HORIZON_ZONE_PACKETHANDLER20141022_HPP

#include <stdio.h>

#include "Server/Common/PacketBuffer.hpp"
#include "Server/Zone/PacketHandler/PacketHandler.hpp"

namespace Horizon
{
namespace Zone
{
namespace PacketVer20141022
{
enum packets
{
	CZ_ENTER               = 0x093b,
	CZ_REQUEST_TIME        = 0x035f,
	CZ_REQNAME             = 0x096a,
};
#pragma pack(push, 1)
struct PACKET_CZ_ENTER : public Packet
{
	PACKET_CZ_ENTER() : Packet(CZ_ENTER) { }
	uint32_t account_id;
	uint32_t char_id;
	uint32_t auth_code;
	uint32_t client_time;
	uint8_t gender;
};
#pragma pack(pop)
}

class Session;

class PacketHandler20141022 : public PacketHandler
{
public:
	PacketHandler20141022(std::shared_ptr<Session> session);
	~PacketHandler20141022();

	virtual void InitializeHandlers();
	/**
	 * Handlers
	 */
	virtual void Handle_CZ_ENTER(PacketVer20141022::PACKET_CZ_ENTER &pkt);
};
}
}
#endif /* HORIZON_ZONE_PACKETHANDLER20141022_HPP */
