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

#ifndef HORIZON_ZONE_RAGEXE_20170228_PACKET_ZC_WARPLIST_HPP
#define HORIZON_ZONE_RAGEXE_20170228_PACKET_ZC_WARPLIST_HPP

#include "Server/Zone/Packets/Ragexe/20170228/PacketsRagexe20170228.hpp"
#include "Server/Zone/Packets/Ragexe/20170222/Structs/PACKET_ZC_WARPLIST.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe20170228
{
struct PACKET_ZC_WARPLIST : public Horizon::Zone::Ragexe20170222::PACKET_ZC_WARPLIST
{
	PACKET_ZC_WARPLIST(uint16_t packet_id = ZC_WARPLIST) : Horizon::Zone::Ragexe20170222::PACKET_ZC_WARPLIST(packet_id) { }

	virtual PacketBuffer serialize() override
	{
		return Ragexe20170222::PACKET_ZC_WARPLIST::serialize();
	}

	virtual void deserialize(PacketBuffer &buf) override
	{
		Ragexe20170222::PACKET_ZC_WARPLIST::deserialize(buf);
	}

	virtual Ragexe20170222::PACKET_ZC_WARPLIST & operator << (PacketBuffer &right) override
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right) override 
	{
		return right = serialize();
	}

	/* Size: -1 bytes */
	/* Changed from 116 in version 20170222 to -1 */
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_20170228_PACKET_ZC_WARPLIST_HPP */
