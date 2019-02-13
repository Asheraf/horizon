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

#ifndef HORIZON_ZONE_RAGEXE_20170412_PACKET_CZ_SEARCH_STORE_INFO_HPP
#define HORIZON_ZONE_RAGEXE_20170412_PACKET_CZ_SEARCH_STORE_INFO_HPP

#include "Server/Zone/Packets/Ragexe/20170412/PacketsRagexe20170412.hpp"
#include "Server/Zone/Packets/Ragexe/20170405/Structs/PACKET_CZ_SEARCH_STORE_INFO.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe20170412
{
struct PACKET_CZ_SEARCH_STORE_INFO : public Horizon::Zone::Ragexe20170405::PACKET_CZ_SEARCH_STORE_INFO
{
	PACKET_CZ_SEARCH_STORE_INFO(uint16_t packet_id = CZ_SEARCH_STORE_INFO) : Horizon::Zone::Ragexe20170405::PACKET_CZ_SEARCH_STORE_INFO(packet_id) { }

	virtual PacketBuffer serialize() override
	{
		return Ragexe20170405::PACKET_CZ_SEARCH_STORE_INFO::serialize();
	}

	virtual void deserialize(PacketBuffer &buf) override
	{
		Ragexe20170405::PACKET_CZ_SEARCH_STORE_INFO::deserialize(buf);
	}

	virtual Ragexe20170405::PACKET_CZ_SEARCH_STORE_INFO & operator << (PacketBuffer &right) override
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right) override 
	{
		return right = serialize();
	}

	/* Size: 2 bytes */
	/* Changed from -1 in version 20170405 to 2 */
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_20170412_PACKET_CZ_SEARCH_STORE_INFO_HPP */
