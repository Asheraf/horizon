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

#ifndef HORIZON_ZONE_RAGEXE_20170524_PACKET_CZ_GANGSI_RANK_HPP
#define HORIZON_ZONE_RAGEXE_20170524_PACKET_CZ_GANGSI_RANK_HPP

#include "Server/Zone/Packets/Ragexe/20170524/PacketsRagexe20170524.hpp"
#include "Server/Zone/Packets/Ragexe/20170517/Structs/PACKET_CZ_GANGSI_RANK.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe20170524
{
struct PACKET_CZ_GANGSI_RANK : public Horizon::Zone::Ragexe20170517::PACKET_CZ_GANGSI_RANK
{
	PACKET_CZ_GANGSI_RANK(uint16_t packet_id = CZ_GANGSI_RANK) : Horizon::Zone::Ragexe20170517::PACKET_CZ_GANGSI_RANK(packet_id) { }

	virtual PacketBuffer serialize() override
	{
		return Ragexe20170517::PACKET_CZ_GANGSI_RANK::serialize();
	}

	virtual void deserialize(PacketBuffer &buf) override
	{
		Ragexe20170517::PACKET_CZ_GANGSI_RANK::deserialize(buf);
	}

	virtual Ragexe20170517::PACKET_CZ_GANGSI_RANK & operator << (PacketBuffer &right) override
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right) override 
	{
		return right = serialize();
	}

	/* Size: 4 bytes */
	/* Changed from 2 in version 20170517 to 4 */
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_20170524_PACKET_CZ_GANGSI_RANK_HPP */
