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

#ifndef HORIZON_ZONE_RAGEXE_20170405_PACKET_ZC_PAR_CHANGE_HPP
#define HORIZON_ZONE_RAGEXE_20170405_PACKET_ZC_PAR_CHANGE_HPP

#include "Server/Zone/Packets/Ragexe/20170405/PacketsRagexe20170405.hpp"
#include "Server/Zone/Packets/Ragexe/Structs/PACKET_ZC_PAR_CHANGE.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe20170405
{
struct PACKET_ZC_PAR_CHANGE : public Horizon::Zone::Ragexe::PACKET_ZC_PAR_CHANGE
{
	PACKET_ZC_PAR_CHANGE(uint16_t packet_id = ZC_PAR_CHANGE) : Horizon::Zone::Ragexe::PACKET_ZC_PAR_CHANGE(packet_id) { }

	virtual PacketBuffer serialize() override
	{
		return Ragexe::PACKET_ZC_PAR_CHANGE::serialize();
	}

	virtual void deserialize(PacketBuffer &buf) override
	{
		Ragexe::PACKET_ZC_PAR_CHANGE::deserialize(buf);
	}

	virtual Ragexe::PACKET_ZC_PAR_CHANGE & operator << (PacketBuffer &right) override
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right) override
	{
		return right = serialize();
	}

	/* Size: 12 bytes */
	/* Changed from 8 in version 0 to 12 */
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_20170405_PACKET_ZC_PAR_CHANGE_HPP */
