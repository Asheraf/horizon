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

#ifndef HORIZON_CHAR_RAGEXE_PACKET_HC_DELETE_CHAR3_CANCEL_HPP
#define HORIZON_CHAR_RAGEXE_PACKET_HC_DELETE_CHAR3_CANCEL_HPP


#include "Server/Char/Packets/Ragexe/Packets.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Char
{
namespace Ragexe
{
struct PACKET_HC_DELETE_CHAR3_CANCEL : public Packet
{
	PACKET_HC_DELETE_CHAR3_CANCEL(uint16_t packet_id = HC_DELETE_CHAR3_CANCEL) : Packet(packet_id) { }

	virtual PacketBuffer serialize()
	{
		PacketBuffer buf(HC_DELETE_CHAR3_CANCEL);
		buf << character_id;
		buf << result;
		return buf;
	}

	virtual void deserialize(PacketBuffer &/*buf*/) { }

	virtual PACKET_HC_DELETE_CHAR3_CANCEL & operator << (PacketBuffer &right)
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right)
	{
		return right = serialize();
	}

	/* Size: 10 bytes */
	uint32_t character_id{0};
	uint32_t result{0}; // either 1 or 2.
};
}
}
}

#endif /* HORIZON_CHAR_RAGEXE_PACKET_HC_DELETE_CHAR3_CANCEL_HPP */
