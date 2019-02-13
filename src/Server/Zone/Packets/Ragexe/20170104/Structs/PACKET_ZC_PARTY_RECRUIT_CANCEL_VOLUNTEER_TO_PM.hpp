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

#ifndef HORIZON_ZONE_RAGEXE_20170104_PACKET_ZC_PARTY_RECRUIT_CANCEL_VOLUNTEER_TO_PM_HPP
#define HORIZON_ZONE_RAGEXE_20170104_PACKET_ZC_PARTY_RECRUIT_CANCEL_VOLUNTEER_TO_PM_HPP

#include "Server/Zone/Packets/Ragexe/20170104/PacketsRagexe20170104.hpp"
#include "Server/Zone/Packets/Ragexe/Structs/PACKET_ZC_PARTY_RECRUIT_CANCEL_VOLUNTEER_TO_PM.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe20170104
{
struct PACKET_ZC_PARTY_RECRUIT_CANCEL_VOLUNTEER_TO_PM : public Horizon::Zone::Ragexe::PACKET_ZC_PARTY_RECRUIT_CANCEL_VOLUNTEER_TO_PM
{
	PACKET_ZC_PARTY_RECRUIT_CANCEL_VOLUNTEER_TO_PM(uint16_t packet_id = ZC_PARTY_RECRUIT_CANCEL_VOLUNTEER_TO_PM) : Horizon::Zone::Ragexe::PACKET_ZC_PARTY_RECRUIT_CANCEL_VOLUNTEER_TO_PM(packet_id) { }

	virtual PacketBuffer serialize() override
	{
		return Ragexe::PACKET_ZC_PARTY_RECRUIT_CANCEL_VOLUNTEER_TO_PM::serialize();
	}

	virtual void deserialize(PacketBuffer &buf) override
	{
		Ragexe::PACKET_ZC_PARTY_RECRUIT_CANCEL_VOLUNTEER_TO_PM::deserialize(buf);
	}

	virtual Ragexe::PACKET_ZC_PARTY_RECRUIT_CANCEL_VOLUNTEER_TO_PM & operator << (PacketBuffer &right) override
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right) override
	{
		return right = serialize();
	}

	/* Size: 2 bytes */
	/* Changed from 6 in version 0 to 2 */
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_20170104_PACKET_ZC_PARTY_RECRUIT_CANCEL_VOLUNTEER_TO_PM_HPP */
