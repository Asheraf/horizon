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

#ifndef HORIZON_ZONE_ZERO_20180213_PACKET_CZ_ADD_FRIENDS_HPP
#define HORIZON_ZONE_ZERO_20180213_PACKET_CZ_ADD_FRIENDS_HPP

#include "Server/Zone/Packets/Zero/20180213/PacketsZero20180213.hpp"
#include "Server/Zone/Packets/Zero/20180207/Structs/PACKET_CZ_ADD_FRIENDS.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Zero20180213
{
struct PACKET_CZ_ADD_FRIENDS : public Horizon::Zone::Zero20180207::PACKET_CZ_ADD_FRIENDS
{
	PACKET_CZ_ADD_FRIENDS(uint16_t packet_id = CZ_ADD_FRIENDS) : Horizon::Zone::Zero20180207::PACKET_CZ_ADD_FRIENDS(packet_id) { }

	virtual PacketBuffer serialize() override
	{
		return Zero20180207::PACKET_CZ_ADD_FRIENDS::serialize();
	}

	virtual void deserialize(PacketBuffer &buf) override
	{
		Zero20180207::PACKET_CZ_ADD_FRIENDS::deserialize(buf);
	}

	virtual Zero20180207::PACKET_CZ_ADD_FRIENDS & operator << (PacketBuffer &right) override
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right) override 
	{
		return right = serialize();
	}

	/* Size: 2 bytes */
	/* Changed from 26 in version 20180207 to 2 */
};
}
}
}

#endif /* HORIZON_ZONE_ZERO_20180213_PACKET_CZ_ADD_FRIENDS_HPP */
