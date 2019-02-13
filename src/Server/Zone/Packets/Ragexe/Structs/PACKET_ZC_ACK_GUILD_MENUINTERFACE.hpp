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

#ifndef HORIZON_ZONE_RAGEXE_PACKET_ZC_ACK_GUILD_MENUINTERFACE_HPP
#define HORIZON_ZONE_RAGEXE_PACKET_ZC_ACK_GUILD_MENUINTERFACE_HPP


#include "Server/Zone/Packets/Ragexe/Packets.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe
{
struct PACKET_ZC_ACK_GUILD_MENUINTERFACE : public Packet
{
	PACKET_ZC_ACK_GUILD_MENUINTERFACE(uint16_t packet_id = ZC_ACK_GUILD_MENUINTERFACE) : Packet(packet_id) { }

	virtual PacketBuffer serialize()
	{
		PacketBuffer buf(packet_id);

		buf << menu_interface_mask;

		return buf;
	}

	virtual void deserialize(PacketBuffer &/*buf*/) { }

	virtual PACKET_ZC_ACK_GUILD_MENUINTERFACE & operator << (PacketBuffer &right)
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right)
	{
		return right = serialize();
	}

	/* Size: 6 bytes */
	uint32_t menu_interface_mask{0};
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_PACKET_ZC_ACK_GUILD_MENUINTERFACE_HPP */
