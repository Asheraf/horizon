/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 * Copyright (c) 2018 Horizon Dev Team.
 *
 * Base Author - Sagun Khosla. (sagunxp@gmail.com)
 *
 * Under a proprietary license this file is not for use
 * or viewing without permission.
 **************************************************/

#ifndef HORIZON_CHAR_PACKETHANDLER20120307_HPP
#define HORIZON_CHAR_PACKETHANDLER20120307_HPP

#include <stdio.h>

#include "Server/Char/PacketHandler/PacketHandler.hpp"

class PacketBuffer;

namespace Horizon
{
namespace Char
{
namespace PacketVer20120307
{
enum packets
{
	CHAR_CREATE        = 0x970,
};
#pragma pack(push, 1)
struct PACKET_CHAR_CREATE : public Packet
{
	PACKET_CHAR_CREATE() : Packet(Horizon::Char::PacketVer20120307::CHAR_CREATE) {}
	// S 0970 <name>.24B <slot>.B <hair color>.W <hair style>.W
	char name[MAX_UNIT_NAME_LENGTH]{0};
	uint8_t slot{0};
	uint16_t hair_color{0};
	uint16_t hair_style{0};
};
#pragma pack(pop)
}
}
}

namespace Horizon
{
namespace Char
{
class CharSocket;
class PacketHandler20120307 : public PacketHandler
{
public:
	explicit PacketHandler20120307(std::shared_ptr<CharSocket> socket);
	virtual ~PacketHandler20120307();

	void initialize_handlers();
	void Handle_CHAR_CREATE(PacketBuffer &buf);
};
}
}
#endif /* HORIZON_CHAR_PACKETHANDLER20120307_HPP */
