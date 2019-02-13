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

#ifndef HORIZON_ZONE_RAGEXE_PACKET_CZ_REQUEST_CHAT_HPP
#define HORIZON_ZONE_RAGEXE_PACKET_CZ_REQUEST_CHAT_HPP


#include "Server/Zone/Packets/Ragexe/Packets.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe
{
struct PACKET_CZ_REQUEST_CHAT : public Packet
{
	PACKET_CZ_REQUEST_CHAT(uint16_t packet_id = CZ_REQUEST_CHAT) : Packet(packet_id) { }

	~PACKET_CZ_REQUEST_CHAT()
	{
		if (message != nullptr)
			delete message;
	}

	virtual PacketBuffer serialize()
	{
		return PacketBuffer(packet_id);
	}

	virtual void deserialize(PacketBuffer &buf)
	{
		buf >> packet_id;
		buf >> packet_length;
		message = new char[packet_length - 4];
		buf.read(message, packet_length - 4);
	}

	virtual PACKET_CZ_REQUEST_CHAT & operator << (PacketBuffer &right)
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right)
	{
		return right = serialize();
	}

	/* Size: -1 bytes */
	uint16_t packet_length;
	char *message{nullptr};
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_PACKET_CZ_REQUEST_CHAT_HPP */
