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

#ifndef HORIZON_AUTH_RAGEXE_PACKET_AC_REFUSE_LOGIN2_HPP
#define HORIZON_AUTH_RAGEXE_PACKET_AC_REFUSE_LOGIN2_HPP


#include "Server/Auth/Packets/Ragexe/Packets.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Auth
{
namespace Ragexe
{
struct PACKET_AC_REFUSE_LOGIN2 : public Packet
{
	PACKET_AC_REFUSE_LOGIN2(uint16_t packet_id = AC_REFUSE_LOGIN2) : Packet(packet_id) { }

	virtual PacketBuffer serialize()
	{
		PacketBuffer buf(AC_REFUSE_LOGIN2);

		buf << error_code;
		buf.append(block_date, sizeof(block_date));

		return buf;
	}

	virtual void deserialize(PacketBuffer &/*buf*/) { }

	virtual PACKET_AC_REFUSE_LOGIN2 & operator << (PacketBuffer &right)
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right)
	{
		return right = serialize();
	}

	/* Size: 26 bytes */
	uint32_t error_code{0};      ///< Error code
	char block_date[20]{0};    ///< Ban expiration date
};
}
}
}

#endif /* HORIZON_AUTH_RAGEXE_PACKET_AC_REFUSE_LOGIN2_HPP */
