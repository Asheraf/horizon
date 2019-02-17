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

#ifndef HORIZON_ZONE_RAGEXE_20171227_PACKET_ZC_PRNPC_STATE_HPP
#define HORIZON_ZONE_RAGEXE_20171227_PACKET_ZC_PRNPC_STATE_HPP

#include "Server/Zone/Packets/Ragexe/20171227/PacketsRagexe20171227.hpp"
#include "Server/Zone/Packets/Ragexe/Structs/PACKET_ZC_PRNPC_STATE.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe20171227
{
struct PACKET_ZC_PRNPC_STATE : public Horizon::Zone::Ragexe::PACKET_ZC_PRNPC_STATE
{
	PACKET_ZC_PRNPC_STATE(uint16_t packet_id = ZC_PRNPC_STATE) : Horizon::Zone::Ragexe::PACKET_ZC_PRNPC_STATE(packet_id) { }

	virtual PacketBuffer serialize() override
	{
		return Ragexe::PACKET_ZC_PRNPC_STATE::serialize();
	}

	virtual void deserialize(PacketBuffer &buf) override
	{
		Ragexe::PACKET_ZC_PRNPC_STATE::deserialize(buf);
	}

	virtual Ragexe::PACKET_ZC_PRNPC_STATE & operator << (PacketBuffer &right) override
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right) override
	{
		return right = serialize();
	}

	/* Size: 2 bytes */
	/* Changed from 4 in version 0 to 2 */
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_20171227_PACKET_ZC_PRNPC_STATE_HPP */
