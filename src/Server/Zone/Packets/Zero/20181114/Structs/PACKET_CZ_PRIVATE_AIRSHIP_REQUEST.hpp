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

#ifndef HORIZON_ZONE_ZERO_20181114_PACKET_CZ_PRIVATE_AIRSHIP_REQUEST_HPP
#define HORIZON_ZONE_ZERO_20181114_PACKET_CZ_PRIVATE_AIRSHIP_REQUEST_HPP

#include "Server/Zone/Packets/Zero/20181114/PacketsZero20181114.hpp"
#include "Server/Zone/Packets/Zero/Structs/PACKET_CZ_PRIVATE_AIRSHIP_REQUEST.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Zero20181114
{
struct PACKET_CZ_PRIVATE_AIRSHIP_REQUEST : public Horizon::Zone::Zero::PACKET_CZ_PRIVATE_AIRSHIP_REQUEST
{
	PACKET_CZ_PRIVATE_AIRSHIP_REQUEST(uint16_t packet_id = CZ_PRIVATE_AIRSHIP_REQUEST) : Horizon::Zone::Zero::PACKET_CZ_PRIVATE_AIRSHIP_REQUEST(packet_id) { }

	virtual PacketBuffer serialize() override
	{
		return Zero::PACKET_CZ_PRIVATE_AIRSHIP_REQUEST::serialize();
	}

	virtual void deserialize(PacketBuffer &buf) override
	{
		Zero::PACKET_CZ_PRIVATE_AIRSHIP_REQUEST::deserialize(buf);
	}

	virtual Zero::PACKET_CZ_PRIVATE_AIRSHIP_REQUEST & operator << (PacketBuffer &right) override
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right) override
	{
		return right = serialize();
	}

	/* Size: 22 bytes */
	/* Changed from 20 in version 0 to 22 */
};
}
}
}

#endif /* HORIZON_ZONE_ZERO_20181114_PACKET_CZ_PRIVATE_AIRSHIP_REQUEST_HPP */
