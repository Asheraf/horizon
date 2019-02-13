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

#ifndef HORIZON_ZONE_RAGEXE_20180829_PACKET_ZC_INVENTORY_START_HPP
#define HORIZON_ZONE_RAGEXE_20180829_PACKET_ZC_INVENTORY_START_HPP

#include "Server/Zone/Packets/Ragexe/20180829/PacketsRagexe20180829.hpp"
#include "Server/Zone/Packets/Ragexe/Structs/PACKET_ZC_INVENTORY_START.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe20180829
{
struct PACKET_ZC_INVENTORY_START : public Horizon::Zone::Ragexe::PACKET_ZC_INVENTORY_START
{
	PACKET_ZC_INVENTORY_START(uint16_t packet_id = ZC_INVENTORY_START) : Horizon::Zone::Ragexe::PACKET_ZC_INVENTORY_START(packet_id) { }

	virtual PacketBuffer serialize() override
	{
		return Ragexe::PACKET_ZC_INVENTORY_START::serialize();
	}

	virtual void deserialize(PacketBuffer &buf) override
	{
		Ragexe::PACKET_ZC_INVENTORY_START::deserialize(buf);
	}

	virtual Ragexe::PACKET_ZC_INVENTORY_START & operator << (PacketBuffer &right) override
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right) override
	{
		return right = serialize();
	}

	/* Size: 26 bytes */
	/* Changed from -1 in version 0 to 26 */
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_20180829_PACKET_ZC_INVENTORY_START_HPP */
