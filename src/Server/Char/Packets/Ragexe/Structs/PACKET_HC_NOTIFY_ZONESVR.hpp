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

#ifndef HORIZON_CHAR_RAGEXE_PACKET_HC_NOTIFY_ZONESVR_HPP
#define HORIZON_CHAR_RAGEXE_PACKET_HC_NOTIFY_ZONESVR_HPP


#include "Server/Char/Packets/Ragexe/Packets.hpp"

#include "Server/Common/PacketBuffer.hpp"
#include "Server/Common/Client.hpp"


namespace Horizon
{
namespace Char
{
namespace Ragexe
{
struct PACKET_HC_NOTIFY_ZONESVR : public Packet
{
	PACKET_HC_NOTIFY_ZONESVR(uint16_t packet_id = HC_NOTIFY_ZONESVR) : Packet(packet_id) { }

	virtual PacketBuffer serialize()
	{
		PacketBuffer buf(HC_NOTIFY_ZONESVR);
		buf << char_id;
		buf.append(map_name, sizeof(map_name));
		buf << ip_address;
		buf << port;
		return buf;
	}

	virtual void deserialize(PacketBuffer &/*buf*/) { }

	virtual PACKET_HC_NOTIFY_ZONESVR & operator << (PacketBuffer &right)
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right)
	{
		return right = serialize();
	}

	/* Size: 28 bytes */
	uint32_t char_id{0};
	char map_name[MAP_NAME_LENGTH_EXT]{0};
	uint32_t ip_address{0};
	uint16_t port{0};
};
}
}
}

#endif /* HORIZON_CHAR_RAGEXE_PACKET_HC_NOTIFY_ZONESVR_HPP */
