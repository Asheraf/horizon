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

#ifndef HORIZON_ZONE_RAGEXE_20170405_PACKET_ZC_NOTIFY_EXP_HPP
#define HORIZON_ZONE_RAGEXE_20170405_PACKET_ZC_NOTIFY_EXP_HPP

#include "Server/Zone/Packets/Ragexe/20170405/PacketsRagexe20170405.hpp"
#include "Server/Zone/Packets/Ragexe/Structs/PACKET_ZC_NOTIFY_EXP.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe20170405
{
struct PACKET_ZC_NOTIFY_EXP : public Horizon::Zone::Ragexe::PACKET_ZC_NOTIFY_EXP
{
	PACKET_ZC_NOTIFY_EXP(uint16_t packet_id = ZC_NOTIFY_EXP) : Horizon::Zone::Ragexe::PACKET_ZC_NOTIFY_EXP(packet_id) { }

	virtual PacketBuffer serialize() override
	{
		return Ragexe::PACKET_ZC_NOTIFY_EXP::serialize();
	}

	virtual void deserialize(PacketBuffer &buf) override
	{
		Ragexe::PACKET_ZC_NOTIFY_EXP::deserialize(buf);
	}

	virtual Ragexe::PACKET_ZC_NOTIFY_EXP & operator << (PacketBuffer &right) override
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right) override
	{
		return right = serialize();
	}

	/* Size: 18 bytes */
	/* Changed from 14 in version 0 to 18 */
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_20170405_PACKET_ZC_NOTIFY_EXP_HPP */
