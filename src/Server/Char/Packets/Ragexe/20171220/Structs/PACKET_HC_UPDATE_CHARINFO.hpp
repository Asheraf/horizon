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

#ifndef HORIZON_CHAR_RAGEXE_20171220_PACKET_HC_UPDATE_CHARINFO_HPP
#define HORIZON_CHAR_RAGEXE_20171220_PACKET_HC_UPDATE_CHARINFO_HPP

#include "Server/Char/Packets/Ragexe/20171220/PacketsRagexe20171220.hpp"
#include "Server/Char/Packets/Ragexe/20171220/Structs/PACKET_HC_UPDATE_CHARINFO.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Char
{
namespace Ragexe20171220
{
struct PACKET_HC_UPDATE_CHARINFO : public Packet
{
	PACKET_HC_UPDATE_CHARINFO(uint16_t packet_id = HC_UPDATE_CHARINFO) : Packet(packet_id) { }

	virtual PacketBuffer serialize()
	{
		return PacketBuffer(packet_id);
	}

	virtual void deserialize(PacketBuffer &/*buf*/) { }

	virtual PACKET_HC_UPDATE_CHARINFO & operator << (PacketBuffer &right)
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right)
	{
		return right = serialize();
	}

	/* Size: 157 bytes */
	/* Changed from 149 in version 20170104 to 157 */
};
}
}
}

#endif /* HORIZON_CHAR_RAGEXE_20171220_PACKET_HC_UPDATE_CHARINFO_HPP */
