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

#ifndef HORIZON_AUTH_RAGEXE_PACKET_CA_CONNECT_INFO_CHANGED_HPP
#define HORIZON_AUTH_RAGEXE_PACKET_CA_CONNECT_INFO_CHANGED_HPP


#include "Server/Auth/Packets/Ragexe/Packets.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Auth
{
namespace Ragexe
{
struct PACKET_CA_CONNECT_INFO_CHANGED : public Packet
{
	PACKET_CA_CONNECT_INFO_CHANGED(uint16_t packet_id = CA_CONNECT_INFO_CHANGED) : Packet(packet_id) { }

	virtual PacketBuffer serialize()
	{
		return PacketBuffer(packet_id);
	}

	virtual void deserialize(PacketBuffer &buf)
	{
		buf >> packet_id;
		buf.read(username, sizeof(username));
	}

	virtual PACKET_CA_CONNECT_INFO_CHANGED & operator << (PacketBuffer &right)
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right)
	{
		return right = serialize();
	}

	/* Size: 26 bytes */
	char username[24]{0};            ///< account.userid
};
}
}
}

#endif /* HORIZON_AUTH_RAGEXE_PACKET_CA_CONNECT_INFO_CHANGED_HPP */
