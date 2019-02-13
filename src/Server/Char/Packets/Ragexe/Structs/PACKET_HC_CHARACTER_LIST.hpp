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

#ifndef HORIZON_CHAR_RAGEXE_PACKET_HC_CHARACTER_LIST_HPP
#define HORIZON_CHAR_RAGEXE_PACKET_HC_CHARACTER_LIST_HPP


#include "Server/Char/Packets/Ragexe/Packets.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Char
{
namespace Ragexe
{
struct PACKET_HC_CHARACTER_LIST : public Packet
{
	PACKET_HC_CHARACTER_LIST(uint16_t packet_id = HC_CHARACTER_LIST) : Packet(packet_id) { }

	virtual PacketBuffer serialize()
	{
		return PacketBuffer(HC_CHARACTER_LIST);
	}

	virtual void deserialize(PacketBuffer &/*buf*/) { }

	virtual PACKET_HC_CHARACTER_LIST & operator << (PacketBuffer &right)
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right)
	{
		return right = serialize();
	}

	/* Size: -1 bytes */
	struct character_list_data : public PACKET_HC_ACCEPT_ENTER::character_list_data
	{
		character_list_data() : PACKET_HC_ACCEPT_ENTER::character_list_data() { }
	};
};
}
}
}

#endif /* HORIZON_CHAR_RAGEXE_PACKET_HC_CHARACTER_LIST_HPP */
