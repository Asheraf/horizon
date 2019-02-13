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

#ifndef HORIZON_ZONE_RAGEXE_20170228_PACKET_ZC_NPCACK_SERVERMOVE_HPP
#define HORIZON_ZONE_RAGEXE_20170228_PACKET_ZC_NPCACK_SERVERMOVE_HPP

#include "Server/Zone/Packets/Ragexe/20170228/PacketsRagexe20170228.hpp"
#include "Server/Zone/Packets/Ragexe/Structs/PACKET_ZC_NPCACK_SERVERMOVE.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe20170228
{
struct PACKET_ZC_NPCACK_SERVERMOVE : public Horizon::Zone::Ragexe::PACKET_ZC_NPCACK_SERVERMOVE
{
	PACKET_ZC_NPCACK_SERVERMOVE(uint16_t packet_id = ZC_NPCACK_SERVERMOVE) : Horizon::Zone::Ragexe::PACKET_ZC_NPCACK_SERVERMOVE(packet_id) { }

	virtual PacketBuffer serialize() override
	{
		return Ragexe::PACKET_ZC_NPCACK_SERVERMOVE::serialize();
	}

	virtual void deserialize(PacketBuffer &buf) override
	{
		Ragexe::PACKET_ZC_NPCACK_SERVERMOVE::deserialize(buf);
	}

	virtual Ragexe::PACKET_ZC_NPCACK_SERVERMOVE & operator << (PacketBuffer &right) override
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right) override
	{
		return right = serialize();
	}

	/* Size: 156 bytes */
	/* Changed from 28 in version 0 to 156 */
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_20170228_PACKET_ZC_NPCACK_SERVERMOVE_HPP */
