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

#ifndef HORIZON_ZONE_RAGEXE_PACKET_CZ_REQ_GUILD_MENU_HPP
#define HORIZON_ZONE_RAGEXE_PACKET_CZ_REQ_GUILD_MENU_HPP


#include "Server/Zone/Packets/Ragexe/Packets.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe
{
struct PACKET_CZ_REQ_GUILD_MENU : public Packet
{
	PACKET_CZ_REQ_GUILD_MENU(uint16_t packet_id = CZ_REQ_GUILD_MENU) : Packet(packet_id) { }

	virtual PacketBuffer serialize()
	{
		return PacketBuffer(packet_id);
	}

	virtual void deserialize(PacketBuffer &buf)
	{
		uint32_t type;
		buf >> packet_id;
		buf >> type;
		info_type = (cz_req_guild_menu_types) type;
	}

	virtual PACKET_CZ_REQ_GUILD_MENU & operator << (PacketBuffer &right)
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right)
	{
		return right = serialize();
	}

	/* Size: 6 bytes */
	cz_req_guild_menu_types info_type{CZ_REQ_GUILD_BASIC_INFO};
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_PACKET_CZ_REQ_GUILD_MENU_HPP */
