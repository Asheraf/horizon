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

#ifndef HORIZON_ZONE_RAGEXE_20170927_PACKET_CZ_JOIN_BATTLE_FIELD_HPP
#define HORIZON_ZONE_RAGEXE_20170927_PACKET_CZ_JOIN_BATTLE_FIELD_HPP

#include "Server/Zone/Packets/Ragexe/20170927/PacketsRagexe20170927.hpp"
#include "Server/Zone/Packets/Ragexe/20170920/Structs/PACKET_CZ_JOIN_BATTLE_FIELD.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe20170927
{
struct PACKET_CZ_JOIN_BATTLE_FIELD : public Horizon::Zone::Ragexe20170920::PACKET_CZ_JOIN_BATTLE_FIELD
{
	PACKET_CZ_JOIN_BATTLE_FIELD(uint16_t packet_id = CZ_JOIN_BATTLE_FIELD) : Horizon::Zone::Ragexe20170920::PACKET_CZ_JOIN_BATTLE_FIELD(packet_id) { }

	virtual PacketBuffer serialize() override
	{
		return Ragexe20170920::PACKET_CZ_JOIN_BATTLE_FIELD::serialize();
	}

	virtual void deserialize(PacketBuffer &buf) override
	{
		Ragexe20170920::PACKET_CZ_JOIN_BATTLE_FIELD::deserialize(buf);
	}

	virtual Ragexe20170920::PACKET_CZ_JOIN_BATTLE_FIELD & operator << (PacketBuffer &right) override
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right) override 
	{
		return right = serialize();
	}

	/* Size: 2 bytes */
	/* Changed from 8 in version 20170920 to 2 */
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_20170927_PACKET_CZ_JOIN_BATTLE_FIELD_HPP */
