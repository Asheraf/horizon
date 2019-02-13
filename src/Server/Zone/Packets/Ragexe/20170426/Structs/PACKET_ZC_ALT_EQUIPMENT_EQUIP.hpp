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

#ifndef HORIZON_ZONE_RAGEXE_20170426_PACKET_ZC_ALT_EQUIPMENT_EQUIP_HPP
#define HORIZON_ZONE_RAGEXE_20170426_PACKET_ZC_ALT_EQUIPMENT_EQUIP_HPP

#include "Server/Zone/Packets/Ragexe/20170426/PacketsRagexe20170426.hpp"
#include "Server/Zone/Packets/Ragexe/20170104/Structs/PACKET_ZC_ALT_EQUIPMENT_EQUIP.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe20170426
{
struct PACKET_ZC_ALT_EQUIPMENT_EQUIP : public Horizon::Zone::Ragexe20170104::PACKET_ZC_ALT_EQUIPMENT_EQUIP
{
	PACKET_ZC_ALT_EQUIPMENT_EQUIP(uint16_t packet_id = ZC_ALT_EQUIPMENT_EQUIP) : Horizon::Zone::Ragexe20170104::PACKET_ZC_ALT_EQUIPMENT_EQUIP(packet_id) { }

	virtual PacketBuffer serialize() override
	{
		return Ragexe20170104::PACKET_ZC_ALT_EQUIPMENT_EQUIP::serialize();
	}

	virtual void deserialize(PacketBuffer &buf) override
	{
		Ragexe20170104::PACKET_ZC_ALT_EQUIPMENT_EQUIP::deserialize(buf);
	}

	virtual Ragexe20170104::PACKET_ZC_ALT_EQUIPMENT_EQUIP & operator << (PacketBuffer &right) override
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right) override 
	{
		return right = serialize();
	}

	/* Size: 10 bytes */
	/* Changed from 12 in version 20170104 to 10 */
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_20170426_PACKET_ZC_ALT_EQUIPMENT_EQUIP_HPP */
