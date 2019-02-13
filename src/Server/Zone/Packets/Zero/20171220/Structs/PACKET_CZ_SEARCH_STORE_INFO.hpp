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

#ifndef HORIZON_ZONE_ZERO_20171220_PACKET_CZ_SEARCH_STORE_INFO_HPP
#define HORIZON_ZONE_ZERO_20171220_PACKET_CZ_SEARCH_STORE_INFO_HPP

#include "Server/Zone/Packets/Zero/20171220/PacketsZero20171220.hpp"
#include "Server/Zone/Packets/Zero/20171214/Structs/PACKET_CZ_SEARCH_STORE_INFO.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Zero20171220
{
struct PACKET_CZ_SEARCH_STORE_INFO : public Horizon::Zone::Zero20171214::PACKET_CZ_SEARCH_STORE_INFO
{
	PACKET_CZ_SEARCH_STORE_INFO(uint16_t packet_id = CZ_SEARCH_STORE_INFO) : Horizon::Zone::Zero20171214::PACKET_CZ_SEARCH_STORE_INFO(packet_id) { }

	virtual PacketBuffer serialize() override
	{
		return Zero20171214::PACKET_CZ_SEARCH_STORE_INFO::serialize();
	}

	virtual void deserialize(PacketBuffer &buf) override
	{
		Zero20171214::PACKET_CZ_SEARCH_STORE_INFO::deserialize(buf);
	}

	virtual Zero20171214::PACKET_CZ_SEARCH_STORE_INFO & operator << (PacketBuffer &right) override
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right) override 
	{
		return right = serialize();
	}

	/* Size: -1 bytes */
	/* Changed from 2 in version 20171214 to -1 */
};
}
}
}

#endif /* HORIZON_ZONE_ZERO_20171220_PACKET_CZ_SEARCH_STORE_INFO_HPP */
