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

#ifndef HORIZON_ZONE_ZERO_20171123_PACKET_CZ_USE_SKILL_TOGROUND_WITHTALKBOX2_HPP
#define HORIZON_ZONE_ZERO_20171123_PACKET_CZ_USE_SKILL_TOGROUND_WITHTALKBOX2_HPP

#include "Server/Zone/Packets/Zero/20171123/PacketsZero20171123.hpp"
#include "Server/Zone/Packets/Zero/20171115/Structs/PACKET_CZ_USE_SKILL_TOGROUND_WITHTALKBOX2.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Zero20171123
{
struct PACKET_CZ_USE_SKILL_TOGROUND_WITHTALKBOX2 : public Horizon::Zone::Zero20171115::PACKET_CZ_USE_SKILL_TOGROUND_WITHTALKBOX2
{
	PACKET_CZ_USE_SKILL_TOGROUND_WITHTALKBOX2(uint16_t packet_id = CZ_USE_SKILL_TOGROUND_WITHTALKBOX2) : Horizon::Zone::Zero20171115::PACKET_CZ_USE_SKILL_TOGROUND_WITHTALKBOX2(packet_id) { }

	virtual PacketBuffer serialize() override
	{
		return Zero20171115::PACKET_CZ_USE_SKILL_TOGROUND_WITHTALKBOX2::serialize();
	}

	virtual void deserialize(PacketBuffer &buf) override
	{
		Zero20171115::PACKET_CZ_USE_SKILL_TOGROUND_WITHTALKBOX2::deserialize(buf);
	}

	virtual Zero20171115::PACKET_CZ_USE_SKILL_TOGROUND_WITHTALKBOX2 & operator << (PacketBuffer &right) override
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right) override 
	{
		return right = serialize();
	}

	/* Size: 5 bytes */
	/* Changed from 2 in version 20171115 to 5 */
};
}
}
}

#endif /* HORIZON_ZONE_ZERO_20171123_PACKET_CZ_USE_SKILL_TOGROUND_WITHTALKBOX2_HPP */
