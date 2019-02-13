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

#ifndef HORIZON_ZONE_RAGEXE_20181121_PACKET_ZC_OFFLINE_STORE_VISIBLE_HPP
#define HORIZON_ZONE_RAGEXE_20181121_PACKET_ZC_OFFLINE_STORE_VISIBLE_HPP

#include "Server/Zone/Packets/Ragexe/20181121/PacketsRagexe20181121.hpp"
#include "Server/Zone/Packets/Ragexe/20180829/Structs/PACKET_ZC_OFFLINE_STORE_VISIBLE.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe20181121
{
struct PACKET_ZC_OFFLINE_STORE_VISIBLE : public Horizon::Zone::Ragexe20180829::PACKET_ZC_OFFLINE_STORE_VISIBLE
{
	PACKET_ZC_OFFLINE_STORE_VISIBLE(uint16_t packet_id = ZC_OFFLINE_STORE_VISIBLE) : Horizon::Zone::Ragexe20180829::PACKET_ZC_OFFLINE_STORE_VISIBLE(packet_id) { }

	virtual PacketBuffer serialize() override
	{
		return Ragexe20180829::PACKET_ZC_OFFLINE_STORE_VISIBLE::serialize();
	}

	virtual void deserialize(PacketBuffer &buf) override
	{
		Ragexe20180829::PACKET_ZC_OFFLINE_STORE_VISIBLE::deserialize(buf);
	}

	virtual Ragexe20180829::PACKET_ZC_OFFLINE_STORE_VISIBLE & operator << (PacketBuffer &right) override
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right) override 
	{
		return right = serialize();
	}

	/* Size: 63 bytes */
	/* Changed from 59 in version 20180829 to 63 */
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_20181121_PACKET_ZC_OFFLINE_STORE_VISIBLE_HPP */
