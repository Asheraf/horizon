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
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 **************************************************/

#ifndef HORIZON_COMMON_RE20130612_PACKETHANDLER_HPP
#define HORIZON_COMMON_RE20130612_PACKETHANDLER_HPP

#include "Server/Common/PacketBuffer.hpp"
#include "PacketHandlerRE20130605.hpp"
#include "Server/Common/Packets/RE/Packets.hpp"

#include "Server/Common/Packets/RE/PacketStructs.hpp"

namespace Horizon
{
namespace Common
{
namespace RE20130612
{
enum packets
{
	SC_LOGIN_ERROR = 0x09c7,
	SC_SOCT = 0x09c9,
};

#pragma pack(push, 1)
struct PACKET_SC_LOGIN_ERROR : public Horizon::Common::RE20130605::PACKET_SC_LOGIN_ERROR
{
	PACKET_SC_LOGIN_ERROR(uint16_t packet_id = SC_LOGIN_ERROR) : Horizon::Common::RE20130605::PACKET_SC_LOGIN_ERROR(packet_id) { }
};
struct PACKET_SC_SOCT : public Horizon::Common::RE::PACKET_SC_SOCT
{
	PACKET_SC_SOCT(uint16_t packet_id = SC_SOCT) : Horizon::Common::RE::PACKET_SC_SOCT(packet_id) { }
};
#pragma pack(pop)
}

class CommonSocket;

class PacketHandlerRE20130612 : public PacketHandlerRE20130605
{
public:
	PacketHandlerRE20130612(std::shared_ptr<CommonSocket> socket);
	~PacketHandlerRE20130612();

	virtual void initialize_handlers() override;

};
}
}

#endif /* HORIZON_COMMON_RE20130612_PACKETHANDLER_HPP */
