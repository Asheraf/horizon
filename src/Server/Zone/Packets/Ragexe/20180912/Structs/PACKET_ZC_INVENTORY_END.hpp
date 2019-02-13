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

#ifndef HORIZON_ZONE_RAGEXE_20180912_PACKET_ZC_INVENTORY_END_HPP
#define HORIZON_ZONE_RAGEXE_20180912_PACKET_ZC_INVENTORY_END_HPP

#include "Server/Zone/Packets/Ragexe/20180912/PacketsRagexe20180912.hpp"
#include "Server/Zone/Packets/Ragexe/20180829/Structs/PACKET_ZC_INVENTORY_END.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe20180912
{
struct PACKET_ZC_INVENTORY_END : public Horizon::Zone::Ragexe20180829::PACKET_ZC_INVENTORY_END
{
	PACKET_ZC_INVENTORY_END(uint16_t packet_id = ZC_INVENTORY_END) : Horizon::Zone::Ragexe20180829::PACKET_ZC_INVENTORY_END(packet_id) { }

	virtual PacketBuffer serialize() override
	{
		return Ragexe20180829::PACKET_ZC_INVENTORY_END::serialize();
	}

	virtual void deserialize(PacketBuffer &buf) override
	{
		Ragexe20180829::PACKET_ZC_INVENTORY_END::deserialize(buf);
	}

	virtual Ragexe20180829::PACKET_ZC_INVENTORY_END & operator << (PacketBuffer &right) override
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right) override 
	{
		return right = serialize();
	}

	/* Size: 4 bytes */
	/* Changed from 3 in version 20180829 to 4 */
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_20180912_PACKET_ZC_INVENTORY_END_HPP */
