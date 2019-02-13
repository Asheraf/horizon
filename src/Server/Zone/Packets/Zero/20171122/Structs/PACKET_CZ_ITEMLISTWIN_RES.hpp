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

#ifndef HORIZON_ZONE_ZERO_20171122_PACKET_CZ_ITEMLISTWIN_RES_HPP
#define HORIZON_ZONE_ZERO_20171122_PACKET_CZ_ITEMLISTWIN_RES_HPP

#include "Server/Zone/Packets/Zero/20171122/PacketsZero20171122.hpp"
#include "Server/Zone/Packets/Zero/20171121/Structs/PACKET_CZ_ITEMLISTWIN_RES.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Zero20171122
{
struct PACKET_CZ_ITEMLISTWIN_RES : public Horizon::Zone::Zero20171121::PACKET_CZ_ITEMLISTWIN_RES
{
	PACKET_CZ_ITEMLISTWIN_RES(uint16_t packet_id = CZ_ITEMLISTWIN_RES) : Horizon::Zone::Zero20171121::PACKET_CZ_ITEMLISTWIN_RES(packet_id) { }

	virtual PacketBuffer serialize() override
	{
		return Zero20171121::PACKET_CZ_ITEMLISTWIN_RES::serialize();
	}

	virtual void deserialize(PacketBuffer &buf) override
	{
		Zero20171121::PACKET_CZ_ITEMLISTWIN_RES::deserialize(buf);
	}

	virtual Zero20171121::PACKET_CZ_ITEMLISTWIN_RES & operator << (PacketBuffer &right) override
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right) override 
	{
		return right = serialize();
	}

	/* Size: -1 bytes */
	/* Changed from 2 in version 20171121 to -1 */
};
}
}
}

#endif /* HORIZON_ZONE_ZERO_20171122_PACKET_CZ_ITEMLISTWIN_RES_HPP */
