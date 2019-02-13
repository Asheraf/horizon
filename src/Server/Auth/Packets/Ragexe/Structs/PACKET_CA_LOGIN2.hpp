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

#ifndef HORIZON_AUTH_RAGEXE_PACKET_CA_LOGIN2_HPP
#define HORIZON_AUTH_RAGEXE_PACKET_CA_LOGIN2_HPP


#include "Server/Auth/Packets/Ragexe/Packets.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Auth
{
namespace Ragexe
{
struct PACKET_CA_LOGIN2 : public Packet
{
	PACKET_CA_LOGIN2(uint16_t packet_id = CA_LOGIN2) : Packet(packet_id) { }

	virtual PacketBuffer serialize()
	{
		return PacketBuffer(packet_id);
	}

	virtual void deserialize(PacketBuffer &buf)
	{
		buf >> packet_id;
		buf >> version;
		buf.read(username, sizeof(username));
		buf.read(password_md5, sizeof(password_md5));
		buf >> client_type;
	}

	virtual PACKET_CA_LOGIN2 & operator << (PacketBuffer &right)
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right)
	{
		return right = serialize();
	}

	/* Size: 47 bytes */

	uint32_t version{0};         ///< Client Version
	char username[24]{0};            ///< Username
	char password_md5[16]{0}; ///< Password hash
	uint8_t client_type{0};       ///< Client Type
};
}
}
}

#endif /* HORIZON_AUTH_RAGEXE_PACKET_CA_LOGIN2_HPP */
