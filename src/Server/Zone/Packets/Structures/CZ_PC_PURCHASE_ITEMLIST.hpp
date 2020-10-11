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

#ifndef HORIZON_ZONE_CZ_PC_PURCHASE_ITEMLIST_HPP
#define HORIZON_ZONE_CZ_PC_PURCHASE_ITEMLIST_HPP

#include "Server/Common/Configuration/Horizon.hpp"
#include "Server/Common/Base/NetworkPacket.hpp"

namespace Horizon
{
namespace Zone
{
class AuthSocket;
namespace Packet
{

enum {
#if PACKET_VERSION >= 20090401
	ID_CZ_PC_PURCHASE_ITEMLIST = 0x00c8
#elif PACKET_VERSION >= 20090325
	ID_CZ_PC_PURCHASE_ITEMLIST = 0x00c8
#elif PACKET_VERSION >= 20090318
	ID_CZ_PC_PURCHASE_ITEMLIST = 0x00c8
#elif PACKET_VERSION >= 20090311
	ID_CZ_PC_PURCHASE_ITEMLIST = 0x00c8
#elif PACKET_VERSION >= 20090218
	ID_CZ_PC_PURCHASE_ITEMLIST = 0x00c8
#elif PACKET_VERSION >= 20090211
	ID_CZ_PC_PURCHASE_ITEMLIST = 0x00c8
#elif PACKET_VERSION >= 20090204
	ID_CZ_PC_PURCHASE_ITEMLIST = 0x00c8
#elif PACKET_VERSION >= 20090129
	ID_CZ_PC_PURCHASE_ITEMLIST = 0x00c8
#elif PACKET_VERSION >= 20090120
	ID_CZ_PC_PURCHASE_ITEMLIST = 0x00c8
#elif PACKET_VERSION >= 20090114
	ID_CZ_PC_PURCHASE_ITEMLIST = 0x00c8
#elif PACKET_VERSION >= 20090107
	ID_CZ_PC_PURCHASE_ITEMLIST = 0x00c8
#elif PACKET_VERSION >= 20081105
	ID_CZ_PC_PURCHASE_ITEMLIST = 0x00c8
#elif PACKET_VERSION >= 20081029
	ID_CZ_PC_PURCHASE_ITEMLIST = 0x00c8
#elif PACKET_VERSION >= 20081022
	ID_CZ_PC_PURCHASE_ITEMLIST = 0x00c8
#elif PACKET_VERSION >= 20080917
	ID_CZ_PC_PURCHASE_ITEMLIST = 0x00c8
#elif PACKET_VERSION >= 20080910
	ID_CZ_PC_PURCHASE_ITEMLIST = 0x00c8
#elif PACKET_VERSION >= 20080903
	ID_CZ_PC_PURCHASE_ITEMLIST = 0x00c8
#elif PACKET_VERSION >= 20080827
	ID_CZ_PC_PURCHASE_ITEMLIST = 0x00c8
#elif PACKET_VERSION >= 20080813
	ID_CZ_PC_PURCHASE_ITEMLIST = 0x00c8
#elif PACKET_VERSION >= 20080806
	ID_CZ_PC_PURCHASE_ITEMLIST = 0x00c8
#elif PACKET_VERSION >= 20080730
	ID_CZ_PC_PURCHASE_ITEMLIST = 0x00c8
#elif PACKET_VERSION >= 20080722
	ID_CZ_PC_PURCHASE_ITEMLIST = 0x00c8
#elif PACKET_VERSION >= 20080715
	ID_CZ_PC_PURCHASE_ITEMLIST = 0x00c8
#elif PACKET_VERSION >= 20080708
	ID_CZ_PC_PURCHASE_ITEMLIST = 0x00c8
#elif PACKET_VERSION >= 20080701
	ID_CZ_PC_PURCHASE_ITEMLIST = 0x00c8
#elif PACKET_VERSION >= 20080624
	ID_CZ_PC_PURCHASE_ITEMLIST = 0x00c8
#elif PACKET_VERSION >= 20080618
	ID_CZ_PC_PURCHASE_ITEMLIST = 0x00c8
#elif PACKET_VERSION >= 20080617
	ID_CZ_PC_PURCHASE_ITEMLIST = 0x00c8
#elif PACKET_VERSION >= 20080603
	ID_CZ_PC_PURCHASE_ITEMLIST = 0x00c8
#elif PACKET_VERSION >= 20080528
	ID_CZ_PC_PURCHASE_ITEMLIST = 0x00c8
#elif PACKET_VERSION >= 20080507
	ID_CZ_PC_PURCHASE_ITEMLIST = 0x00c8
#elif PACKET_VERSION >= 20080429
	ID_CZ_PC_PURCHASE_ITEMLIST = 0x00c8
#elif PACKET_VERSION >= 20080325
	ID_CZ_PC_PURCHASE_ITEMLIST = 0x00c8
#elif PACKET_VERSION >= 20080318
	ID_CZ_PC_PURCHASE_ITEMLIST = 0x00c8
#elif PACKET_VERSION >= 20080311
	ID_CZ_PC_PURCHASE_ITEMLIST = 0x00c8
#elif PACKET_VERSION >= 20080304
	ID_CZ_PC_PURCHASE_ITEMLIST = 0x00c8
#elif PACKET_VERSION >= 20080226
	ID_CZ_PC_PURCHASE_ITEMLIST = 0x00c8
#elif PACKET_VERSION >= 20080219
	ID_CZ_PC_PURCHASE_ITEMLIST = 0x00c8
#elif PACKET_VERSION >= 20080124
	ID_CZ_PC_PURCHASE_ITEMLIST = 0x00c8
#elif PACKET_VERSION >= 20080102
	ID_CZ_PC_PURCHASE_ITEMLIST = 0x00c8
#elif PACKET_VERSION >= 0
	ID_CZ_PC_PURCHASE_ITEMLIST = 0x00c8
#endif
};
/**
 * @brief Main object for the aegis packet: CZ_PC_PURCHASE_ITEMLIST
 * Size : -1 @ 0
 *
 */ 
class CZ_PC_PURCHASE_ITEMLIST : public Base::NetworkPacket<ZoneSocket>
{
public:
	CZ_PC_PURCHASE_ITEMLIST(std::shared_ptr<ZoneSocket> sock);
	~CZ_PC_PURCHASE_ITEMLIST();


	void handle(ByteBuffer &buf);

private:
	void deserialize(ByteBuffer &buf) override;

protected:
	/* Structure Goes Here */
};
}
}
}
#endif /* HORIZON_ZONE_CZ_PC_PURCHASE_ITEMLIST_HPP */
