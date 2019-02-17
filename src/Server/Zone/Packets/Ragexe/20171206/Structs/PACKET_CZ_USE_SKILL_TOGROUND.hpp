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

#ifndef HORIZON_ZONE_RAGEXE_20171206_PACKET_CZ_USE_SKILL_TOGROUND_HPP
#define HORIZON_ZONE_RAGEXE_20171206_PACKET_CZ_USE_SKILL_TOGROUND_HPP

#include "Server/Zone/Packets/Ragexe/20171206/PacketsRagexe20171206.hpp"
#include "Server/Zone/Packets/Ragexe/Structs/PACKET_CZ_USE_SKILL_TOGROUND.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe20171206
{
struct PACKET_CZ_USE_SKILL_TOGROUND : public Horizon::Zone::Ragexe::PACKET_CZ_USE_SKILL_TOGROUND
{
	PACKET_CZ_USE_SKILL_TOGROUND(uint16_t packet_id = CZ_USE_SKILL_TOGROUND) : Horizon::Zone::Ragexe::PACKET_CZ_USE_SKILL_TOGROUND(packet_id) { }

	virtual PacketBuffer serialize() override
	{
		return Ragexe::PACKET_CZ_USE_SKILL_TOGROUND::serialize();
	}

	virtual void deserialize(PacketBuffer &buf) override
	{
		Ragexe::PACKET_CZ_USE_SKILL_TOGROUND::deserialize(buf);
	}

	virtual Ragexe::PACKET_CZ_USE_SKILL_TOGROUND & operator << (PacketBuffer &right) override
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right) override
	{
		return right = serialize();
	}

	/* Size: 10 bytes */
	/* Changed from 11 in version 0 to 10 */
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_20171206_PACKET_CZ_USE_SKILL_TOGROUND_HPP */
