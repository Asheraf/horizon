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

#ifndef HORIZON_CHAR_RAGEXE_20170104_PACKET_HC_ACCEPT_MAKECHAR_HPP
#define HORIZON_CHAR_RAGEXE_20170104_PACKET_HC_ACCEPT_MAKECHAR_HPP

#include "Server/Char/Packets/Ragexe/20170104/PacketsRagexe20170104.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_HC_ACCEPT_MAKECHAR.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Char
{
namespace Ragexe20170104
{
struct PACKET_HC_ACCEPT_MAKECHAR : public Horizon::Char::Ragexe::PACKET_HC_ACCEPT_MAKECHAR
{
	PACKET_HC_ACCEPT_MAKECHAR(uint16_t packet_id = HC_ACCEPT_MAKECHAR) : Horizon::Char::Ragexe::PACKET_HC_ACCEPT_MAKECHAR(packet_id) { }

	virtual PacketBuffer serialize() override
	{
		return Ragexe::PACKET_HC_ACCEPT_MAKECHAR::serialize();
	}

	virtual void deserialize(PacketBuffer &buf) override
	{
		Ragexe::PACKET_HC_ACCEPT_MAKECHAR::deserialize(buf);
	}

	virtual Ragexe::PACKET_HC_ACCEPT_MAKECHAR & operator << (PacketBuffer &right) override
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right) override
	{
		return right = serialize();
	}

	/* Size: 149 bytes */
	/* Changed from 108 in version 0 to 149 */
};
}
}
}

#endif /* HORIZON_CHAR_RAGEXE_20170104_PACKET_HC_ACCEPT_MAKECHAR_HPP */
