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
namespace Game
{
	class Entity;
}
namespace PacketVer20141022
{
enum packets
{
	/* */
	CZ_ENTER               = 0x093b,
	CZ_REQUEST_TIME        = 0x035f,
	CZ_REQNAME             = 0x096a,
	CZ_REQUEST_MOVE        = 0x0437,
	CZ_ACK_STORE_PASSWORD  = 0x0438,
	CZ_REQUEST_ACT         = 0x0369,
};

#pragma pack(push, 1)
struct PACKET_ZC_NOTIFY_STANDENTRY10 : public Horizon::Zone::PACKET_ZC_NOTIFY_STANDENTRY10
{
	PACKET_ZC_NOTIFY_STANDENTRY10() : Horizon::Zone::PACKET_ZC_NOTIFY_STANDENTRY10(ZC_NOTIFY_STANDENTRY10) { }
};

struct PACKET_CZ_ENTER : public Horizon::Zone::PACKET_CZ_ENTER
{
	PACKET_CZ_ENTER() : Horizon::Zone::PACKET_CZ_ENTER(CZ_ENTER) { }
};
struct PACKET_CZ_REQUEST_ACT : public Horizon::Zone::PACKET_CZ_REQUEST_ACT
{
	PACKET_CZ_REQUEST_ACT() : Horizon::Zone::PACKET_CZ_REQUEST_ACT(CZ_REQUEST_ACT) { }
};
struct PACKET_CZ_REQUEST_MOVE : public Horizon::Zone::PACKET_CZ_REQUEST_MOVE
{
	PACKET_CZ_REQUEST_MOVE() : Horizon::Zone::PACKET_CZ_REQUEST_MOVE(CZ_REQUEST_MOVE) { }
};
struct PACKET_CZ_CHANGE_DIR : public Horizon::Zone::PACKET_CZ_CHANGE_DIR
{
	PACKET_CZ_CHANGE_DIR() : Horizon::Zone::PACKET_CZ_CHANGE_DIR(CZ_CHANGE_DIR) { }
};
	
#pragma pack(pop)
}

class ZoneSocket;

class PacketHandler20141022 : public PacketHandler
{
public:
	PacketHandler20141022(std::shared_ptr<ZoneSocket> socket);
	~PacketHandler20141022();

	virtual void initialize_handlers() override;

	void Handle_CZ_CHANGE_DIRECTION(PacketBuffer &buf) override;
	void Handle_CZ_CHANGE_DIRECTION2(PacketBuffer &buf) override;

	void Send_ZC_NOTIFY_STANDENTRY10(Game::Entity *entity) override;
};
}
}
#endif /* HORIZON_ZONE_PACKETHANDLER20141022_HPP */
