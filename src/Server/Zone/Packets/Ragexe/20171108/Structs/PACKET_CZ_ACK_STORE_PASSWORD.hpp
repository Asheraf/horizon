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

#ifndef HORIZON_ZONE_RAGEXE_20171108_PACKET_CZ_ACK_STORE_PASSWORD_HPP
#define HORIZON_ZONE_RAGEXE_20171108_PACKET_CZ_ACK_STORE_PASSWORD_HPP

#include "Server/Zone/Packets/Ragexe/20171108/PacketsRagexe20171108.hpp"
#include "Server/Zone/Packets/Ragexe/20171101/Structs/PACKET_CZ_ACK_STORE_PASSWORD.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe20171108
{
struct PACKET_CZ_ACK_STORE_PASSWORD : public Horizon::Zone::Ragexe20171101::PACKET_CZ_ACK_STORE_PASSWORD
{
	PACKET_CZ_ACK_STORE_PASSWORD(uint16_t packet_id = CZ_ACK_STORE_PASSWORD) : Horizon::Zone::Ragexe20171101::PACKET_CZ_ACK_STORE_PASSWORD(packet_id) { }

	virtual PacketBuffer serialize() override
	{
		return Ragexe20171101::PACKET_CZ_ACK_STORE_PASSWORD::serialize();
	}

	virtual void deserialize(PacketBuffer &buf) override
	{
		Ragexe20171101::PACKET_CZ_ACK_STORE_PASSWORD::deserialize(buf);
	}

	virtual Ragexe20171101::PACKET_CZ_ACK_STORE_PASSWORD & operator << (PacketBuffer &right) override
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right) override 
	{
		return right = serialize();
	}

	/* Size: 36 bytes */
	/* Changed from 2 in version 20171101 to 36 */
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_20171108_PACKET_CZ_ACK_STORE_PASSWORD_HPP */
