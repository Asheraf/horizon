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
 * Base Author - Sxyz (sagunxp@gmail.com)
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

#ifndef HORIZON_COMMON_RAGEXE_PACKETSTRUCTS_HPP
#define HORIZON_COMMON_RAGEXE_PACKETSTRUCTS_HPP

#include "Packets.hpp"


namespace Horizon
{
namespace Common
{
namespace Ragexe
{
#pragma pack(push, 1)
struct PACKET_AHC_GAME_GUARD : public Packet
{
	PACKET_AHC_GAME_GUARD(uint16_t packet_id = AHC_GAME_GUARD) : Packet(packet_id) { }
	/* Size: 18 bytes */
};
struct PACKET_CAH_ACK_GAME_GUARD : public Packet
{
	PACKET_CAH_ACK_GAME_GUARD(uint16_t packet_id = CAH_ACK_GAME_GUARD) : Packet(packet_id) { }
	/* Size: 18 bytes */
};
struct PACKET_CS_LOGIN_QUERY : public Packet
{
	PACKET_CS_LOGIN_QUERY(uint16_t packet_id = CS_LOGIN_QUERY) : Packet(packet_id) { }
	/* Size: 1042 bytes */
};
struct PACKET_CS_REQ_ENCRYPTION : public Packet
{
	PACKET_CS_REQ_ENCRYPTION(uint16_t packet_id = CS_REQ_ENCRYPTION) : Packet(packet_id) { }
	/* Size: 4 bytes */
};
struct PACKET_SC_ACK_ENCRYPTION : public Packet
{
	PACKET_SC_ACK_ENCRYPTION(uint16_t packet_id = SC_ACK_ENCRYPTION) : Packet(packet_id) { }
	/* Size: 2 bytes */
};
struct PACKET_SC_BILLING_INFO : public Packet
{
	PACKET_SC_BILLING_INFO(uint16_t packet_id = SC_BILLING_INFO) : Packet(packet_id) { }
	/* Size: 18 bytes */
};
struct PACKET_SC_LOGIN_ANSWER : public Packet
{
	PACKET_SC_LOGIN_ANSWER(uint16_t packet_id = SC_LOGIN_ANSWER) : Packet(packet_id) { }
	/* Size: -1 bytes */
};
struct PACKET_SC_LOGIN_ANSWER_WITH_ID : public Packet
{
	PACKET_SC_LOGIN_ANSWER_WITH_ID(uint16_t packet_id = SC_LOGIN_ANSWER_WITH_ID) : Packet(packet_id) { }
	/* Size: -1 bytes */
};
struct PACKET_SC_LOGIN_ERROR : public Packet
{
	PACKET_SC_LOGIN_ERROR(uint16_t packet_id = SC_LOGIN_ERROR) : Packet(packet_id) { }
	/* Size: 18 bytes */
};
struct PACKET_SC_NOTIFY_BAN : public Packet
{
	PACKET_SC_NOTIFY_BAN(uint16_t packet_id = SC_NOTIFY_BAN) : Packet(packet_id) { }
	/* Size: 3 bytes */
};
struct PACKET_SC_SOCT : public Packet
{
	PACKET_SC_SOCT(uint16_t packet_id = SC_SOCT) : Packet(packet_id) { }
	/* Size: -1 bytes */
};
#pragma pack(pop)
}

}
}

#endif /* HORIZON_COMMON_RAGEXE_PACKETSTRUCTS_HPP */
