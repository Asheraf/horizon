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

#ifndef HORIZON_ZONE_ZERO_20171214_PACKET_CZ_GANGSI_RANK_HPP
#define HORIZON_ZONE_ZERO_20171214_PACKET_CZ_GANGSI_RANK_HPP

#include "Server/Zone/Packets/Zero/20171214/PacketsZero20171214.hpp"
#include "Server/Zone/Packets/Zero/20171213/Structs/PACKET_CZ_GANGSI_RANK.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Zero20171214
{
struct PACKET_CZ_GANGSI_RANK : public Horizon::Zone::Zero20171213::PACKET_CZ_GANGSI_RANK
{
	PACKET_CZ_GANGSI_RANK(uint16_t packet_id = CZ_GANGSI_RANK) : Horizon::Zone::Zero20171213::PACKET_CZ_GANGSI_RANK(packet_id) { }

	virtual PacketBuffer serialize() override
	{
		return Zero20171213::PACKET_CZ_GANGSI_RANK::serialize();
	}

	virtual void deserialize(PacketBuffer &buf) override
	{
		Zero20171213::PACKET_CZ_GANGSI_RANK::deserialize(buf);
	}

	virtual Zero20171213::PACKET_CZ_GANGSI_RANK & operator << (PacketBuffer &right) override
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right) override 
	{
		return right = serialize();
	}

	/* Size: 2 bytes */
	/* Changed from 4 in version 20171213 to 2 */
};
}
}
}

#endif /* HORIZON_ZONE_ZERO_20171214_PACKET_CZ_GANGSI_RANK_HPP */
