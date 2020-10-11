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

#ifndef HORIZON_ZONE_CZ_USE_ITEM2_HPP
#define HORIZON_ZONE_CZ_USE_ITEM2_HPP

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
#if PACKET_VERSION >= 20090406
	ID_CZ_USE_ITEM2 = 0x0439
#elif PACKET_VERSION >= 20090401
	ID_CZ_USE_ITEM2 = 0x0439
#elif PACKET_VERSION >= 20090218
	ID_CZ_USE_ITEM2 = 0x0439
#elif PACKET_VERSION >= 20090211
	ID_CZ_USE_ITEM2 = 0x0439
#elif PACKET_VERSION >= 20090129
	ID_CZ_USE_ITEM2 = 0x0439
#elif PACKET_VERSION >= 20090120
	ID_CZ_USE_ITEM2 = 0x0439
#elif PACKET_VERSION >= 20090114
	ID_CZ_USE_ITEM2 = 0x0439
#elif PACKET_VERSION >= 20090107
	ID_CZ_USE_ITEM2 = 0x0439
#elif PACKET_VERSION >= 20081217
	ID_CZ_USE_ITEM2 = 0x0439
#elif PACKET_VERSION >= 20081119
	ID_CZ_USE_ITEM2 = 0x0439
#elif PACKET_VERSION >= 20081112
	ID_CZ_USE_ITEM2 = 0x0439
#elif PACKET_VERSION >= 20081105
	ID_CZ_USE_ITEM2 = 0x0439
#elif PACKET_VERSION >= 20081022
	ID_CZ_USE_ITEM2 = 0x0439
#elif PACKET_VERSION >= 20081015
	ID_CZ_USE_ITEM2 = 0x0439
#elif PACKET_VERSION >= 20081008
	ID_CZ_USE_ITEM2 = 0x0439
#elif PACKET_VERSION >= 20081001
	ID_CZ_USE_ITEM2 = 0x0439
#elif PACKET_VERSION >= 20080924
	ID_CZ_USE_ITEM2 = 0x0439
#elif PACKET_VERSION >= 20080917
	ID_CZ_USE_ITEM2 = 0x0439
#elif PACKET_VERSION >= 20080910
	ID_CZ_USE_ITEM2 = 0x0439
#elif PACKET_VERSION >= 0
	ID_CZ_USE_ITEM2 = 0x0439
#endif
};
/**
 * @brief Main object for the aegis packet: CZ_USE_ITEM2
 * Size : 8 @ 0
 *
 */ 
class CZ_USE_ITEM2 : public Base::NetworkPacket<ZoneSocket>
{
public:
	CZ_USE_ITEM2(std::shared_ptr<ZoneSocket> sock);
	~CZ_USE_ITEM2();


	void handle(ByteBuffer &buf);

private:
	void deserialize(ByteBuffer &buf) override;

protected:
	/* Structure Goes Here */
};
}
}
}
#endif /* HORIZON_ZONE_CZ_USE_ITEM2_HPP */
