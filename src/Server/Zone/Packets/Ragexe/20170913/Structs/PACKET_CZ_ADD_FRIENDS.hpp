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

#ifndef HORIZON_ZONE_RAGEXE_20170913_PACKET_CZ_ADD_FRIENDS_HPP
#define HORIZON_ZONE_RAGEXE_20170913_PACKET_CZ_ADD_FRIENDS_HPP

#include "Server/Zone/Packets/Ragexe/20170913/PacketsRagexe20170913.hpp"
#include "Server/Zone/Packets/Ragexe/20170906/Structs/PACKET_CZ_ADD_FRIENDS.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe20170913
{
struct PACKET_CZ_ADD_FRIENDS : public Horizon::Zone::Ragexe20170906::PACKET_CZ_ADD_FRIENDS
{
	PACKET_CZ_ADD_FRIENDS(uint16_t packet_id = CZ_ADD_FRIENDS) : Horizon::Zone::Ragexe20170906::PACKET_CZ_ADD_FRIENDS(packet_id) { }

	virtual PacketBuffer serialize() override
	{
		return Ragexe20170906::PACKET_CZ_ADD_FRIENDS::serialize();
	}

	virtual void deserialize(PacketBuffer &buf) override
	{
		Ragexe20170906::PACKET_CZ_ADD_FRIENDS::deserialize(buf);
	}

	virtual Ragexe20170906::PACKET_CZ_ADD_FRIENDS & operator << (PacketBuffer &right) override
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right) override 
	{
		return right = serialize();
	}

	/* Size: 2 bytes */
	/* Changed from 26 in version 20170906 to 2 */
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_20170913_PACKET_CZ_ADD_FRIENDS_HPP */
