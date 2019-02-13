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

#ifndef HORIZON_ZONE_RAGEXE_20170920_PACKET_ZC_ACK_REQNAME_HPP
#define HORIZON_ZONE_RAGEXE_20170920_PACKET_ZC_ACK_REQNAME_HPP

#include "Server/Zone/Packets/Ragexe/20170920/PacketsRagexe20170920.hpp"
#include "Server/Zone/Packets/Ragexe/Structs/PACKET_ZC_ACK_REQNAME.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe20170920
{
struct PACKET_ZC_ACK_REQNAME : public Horizon::Zone::Ragexe::PACKET_ZC_ACK_REQNAME
{
	PACKET_ZC_ACK_REQNAME(uint16_t packet_id = ZC_ACK_REQNAME) : Horizon::Zone::Ragexe::PACKET_ZC_ACK_REQNAME(packet_id) { }

	virtual PacketBuffer serialize() override
	{
		return Ragexe::PACKET_ZC_ACK_REQNAME::serialize();
	}

	virtual void deserialize(PacketBuffer &buf) override
	{
		Ragexe::PACKET_ZC_ACK_REQNAME::deserialize(buf);
	}

	virtual Ragexe::PACKET_ZC_ACK_REQNAME & operator << (PacketBuffer &right) override
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right) override
	{
		return right = serialize();
	}

	/* Size: 58 bytes */
	/* Changed from 30 in version 0 to 58 */
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_20170920_PACKET_ZC_ACK_REQNAME_HPP */
