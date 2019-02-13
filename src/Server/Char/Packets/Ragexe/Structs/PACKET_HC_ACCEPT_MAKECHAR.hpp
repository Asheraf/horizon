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

#ifndef HORIZON_CHAR_RAGEXE_PACKET_HC_ACCEPT_MAKECHAR_HPP
#define HORIZON_CHAR_RAGEXE_PACKET_HC_ACCEPT_MAKECHAR_HPP


#include "Server/Char/Packets/Ragexe/Packets.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_HC_ACCEPT_ENTER.hpp"
#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Char
{
namespace Ragexe
{
struct PACKET_HC_ACCEPT_MAKECHAR : public Packet
{
	PACKET_HC_ACCEPT_MAKECHAR(uint16_t packet_id = HC_ACCEPT_MAKECHAR) : Packet(packet_id) { }

	virtual PacketBuffer serialize()
	{
		PacketBuffer buf(HC_ACCEPT_MAKECHAR);
		character.serialize(buf);
		return buf;
	}

	virtual void deserialize(PacketBuffer &/*buf*/) { }

	virtual PACKET_HC_ACCEPT_MAKECHAR & operator << (PacketBuffer &right)
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right)
	{
		return right = serialize();
	}

	/* Size: 108 bytes */
	PACKET_HC_ACCEPT_ENTER::character_list_data character;
};
}
}
}

#endif /* HORIZON_CHAR_RAGEXE_PACKET_HC_ACCEPT_MAKECHAR_HPP */
