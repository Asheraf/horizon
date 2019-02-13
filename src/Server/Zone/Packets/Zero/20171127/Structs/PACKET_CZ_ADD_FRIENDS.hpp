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

#ifndef HORIZON_ZONE_ZERO_20171127_PACKET_CZ_ADD_FRIENDS_HPP
#define HORIZON_ZONE_ZERO_20171127_PACKET_CZ_ADD_FRIENDS_HPP

#include "Server/Zone/Packets/Zero/20171127/PacketsZero20171127.hpp"
#include "Server/Zone/Packets/Zero/20171123/Structs/PACKET_CZ_ADD_FRIENDS.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Zero20171127
{
struct PACKET_CZ_ADD_FRIENDS : public Horizon::Zone::Zero20171123::PACKET_CZ_ADD_FRIENDS
{
	PACKET_CZ_ADD_FRIENDS(uint16_t packet_id = CZ_ADD_FRIENDS) : Horizon::Zone::Zero20171123::PACKET_CZ_ADD_FRIENDS(packet_id) { }

	virtual PacketBuffer serialize() override
	{
		return Zero20171123::PACKET_CZ_ADD_FRIENDS::serialize();
	}

	virtual void deserialize(PacketBuffer &buf) override
	{
		Zero20171123::PACKET_CZ_ADD_FRIENDS::deserialize(buf);
	}

	virtual Zero20171123::PACKET_CZ_ADD_FRIENDS & operator << (PacketBuffer &right) override
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right) override 
	{
		return right = serialize();
	}

	/* Size: 26 bytes */
	/* Changed from 2 in version 20171123 to 26 */
};
}
}
}

#endif /* HORIZON_ZONE_ZERO_20171127_PACKET_CZ_ADD_FRIENDS_HPP */
