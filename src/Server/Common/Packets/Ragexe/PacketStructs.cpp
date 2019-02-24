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
namespace Horizon
{
namespace Common
{
#pragma pack(push, 1)
struct PACKET_AHC_GAME_GUARD : public Packet
{
	PACKET_AHC_GAME_GUARD() : Packet(AHC_GAME_GUARD) { }
};
struct PACKET_CAH_ACK_GAME_GUARD : public Packet
{
	PACKET_CAH_ACK_GAME_GUARD() : Packet(CAH_ACK_GAME_GUARD) { }
};
struct PACKET_CS_LOGIN_QUERY : public Packet
{
	PACKET_CS_LOGIN_QUERY() : Packet(CS_LOGIN_QUERY) { }
};
struct PACKET_CS_REQ_ENCRYPTION : public Packet
{
	PACKET_CS_REQ_ENCRYPTION() : Packet(CS_REQ_ENCRYPTION) { }
};
struct PACKET_SC_ACK_ENCRYPTION : public Packet
{
	PACKET_SC_ACK_ENCRYPTION() : Packet(SC_ACK_ENCRYPTION) { }
};
struct PACKET_SC_BILLING_INFO : public Packet
{
	PACKET_SC_BILLING_INFO() : Packet(SC_BILLING_INFO) { }
};
struct PACKET_SC_LOGIN_ANSWER : public Packet
{
	PACKET_SC_LOGIN_ANSWER() : Packet(SC_LOGIN_ANSWER) { }
};
struct PACKET_SC_LOGIN_ANSWER_WITH_ID : public Packet
{
	PACKET_SC_LOGIN_ANSWER_WITH_ID() : Packet(SC_LOGIN_ANSWER_WITH_ID) { }
};
struct PACKET_SC_LOGIN_ERROR : public Packet
{
	PACKET_SC_LOGIN_ERROR() : Packet(SC_LOGIN_ERROR) { }
};
struct PACKET_SC_NOTIFY_BAN : public Packet
{
	PACKET_SC_NOTIFY_BAN() : Packet(SC_NOTIFY_BAN) { }
};
struct PACKET_SC_SOCT : public Packet
{
	PACKET_SC_SOCT() : Packet(SC_SOCT) { }
};
#pragma pack(pop)
}

}

#endif /* HORIZON_COMMON_RAGEXE_PACKETSTRUCTS_HPP */
