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

#ifndef HORIZON_ZONE_RAGEXE_PACKET_CZ_ENTER_HPP
#define HORIZON_ZONE_RAGEXE_PACKET_CZ_ENTER_HPP


#include "Server/Zone/Packets/Ragexe/Packets.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe
{
struct PACKET_CZ_ENTER : public Packet
{
	PACKET_CZ_ENTER(uint16_t packet_id = CZ_ENTER) : Packet(packet_id) { }

	virtual PacketBuffer serialize()
	{
		return PacketBuffer(packet_id);
	}

	virtual void deserialize(PacketBuffer &buf)
	{
		buf >> packet_id;
		buf >> account_id;
		buf >> char_id;
		buf >> auth_code;
		buf >> client_time;
		buf >> gender;
	}

	virtual PACKET_CZ_ENTER & operator << (PacketBuffer &right)
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right)
	{
		return right = serialize();
	}

	/* Size: 19 bytes */
	uint32_t account_id{0};
	uint32_t char_id{0};
	uint32_t auth_code{0};
	uint32_t client_time{0};
	uint8_t gender{0};
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_PACKET_CZ_ENTER_HPP */
