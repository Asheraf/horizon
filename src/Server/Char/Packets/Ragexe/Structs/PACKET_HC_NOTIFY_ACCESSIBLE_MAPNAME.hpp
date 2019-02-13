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

#ifndef HORIZON_CHAR_RAGEXE_PACKET_HC_NOTIFY_ACCESSIBLE_MAPNAME_HPP
#define HORIZON_CHAR_RAGEXE_PACKET_HC_NOTIFY_ACCESSIBLE_MAPNAME_HPP


#include "Server/Char/Packets/Ragexe/Packets.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Char
{
namespace Ragexe
{
struct PACKET_HC_NOTIFY_ACCESSIBLE_MAPNAME : public Packet
{
	PACKET_HC_NOTIFY_ACCESSIBLE_MAPNAME(uint16_t packet_id = HC_NOTIFY_ACCESSIBLE_MAPNAME) : Packet(packet_id) { }

	virtual PacketBuffer serialize()
	{
		return PacketBuffer(packet_id);
	}

	virtual void deserialize(PacketBuffer &/*buf*/) { }

	virtual PACKET_HC_NOTIFY_ACCESSIBLE_MAPNAME & operator << (PacketBuffer &right)
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right)
	{
		return right = serialize();
	}

	/* Size: -1 bytes */
};
}
}
}

#endif /* HORIZON_CHAR_RAGEXE_PACKET_HC_NOTIFY_ACCESSIBLE_MAPNAME_HPP */
