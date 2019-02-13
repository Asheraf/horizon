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

#ifndef HORIZON_CHAR_RAGEXE_20170228_PACKET_HC_NOTIFY_ZONESVR_HPP
#define HORIZON_CHAR_RAGEXE_20170228_PACKET_HC_NOTIFY_ZONESVR_HPP

#include "Server/Char/Packets/Ragexe/20170228/PacketsRagexe20170228.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_HC_NOTIFY_ZONESVR.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Char
{
namespace Ragexe20170228
{
struct PACKET_HC_NOTIFY_ZONESVR : public Horizon::Char::Ragexe::PACKET_HC_NOTIFY_ZONESVR
{
	PACKET_HC_NOTIFY_ZONESVR(uint16_t packet_id = HC_NOTIFY_ZONESVR) : Horizon::Char::Ragexe::PACKET_HC_NOTIFY_ZONESVR(packet_id) { }

	virtual PacketBuffer serialize() override
	{
		return Ragexe::PACKET_HC_NOTIFY_ZONESVR::serialize();
	}

	virtual void deserialize(PacketBuffer &buf) override
	{
		Ragexe::PACKET_HC_NOTIFY_ZONESVR::deserialize(buf);
	}

	virtual Ragexe::PACKET_HC_NOTIFY_ZONESVR & operator << (PacketBuffer &right) override
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

#endif /* HORIZON_CHAR_RAGEXE_20170228_PACKET_HC_NOTIFY_ZONESVR_HPP */
