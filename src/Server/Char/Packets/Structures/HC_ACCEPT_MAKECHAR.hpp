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

#ifndef HORIZON_CHAR_HC_ACCEPT_MAKECHAR_HPP
#define HORIZON_CHAR_HC_ACCEPT_MAKECHAR_HPP

#include "Server/Common/Configuration/Horizon.hpp"
#include "Server/Common/Base/NetworkPacket.hpp"

namespace Horizon
{
namespace Char
{
class AuthSocket;
namespace Packet
{

enum {
#if PACKET_VERSION >= 20170906
	ID_HC_ACCEPT_MAKECHAR = 0x006d
#elif PACKET_VERSION >= 20170830
	ID_HC_ACCEPT_MAKECHAR = 0x006d
#elif PACKET_VERSION >= 20170104
	ID_HC_ACCEPT_MAKECHAR = 0x006d
#elif PACKET_VERSION >= 20140820
	ID_HC_ACCEPT_MAKECHAR = 0x006d
#elif PACKET_VERSION >= 20140625
	ID_HC_ACCEPT_MAKECHAR = 0x006d
#elif PACKET_VERSION >= 20140108
	ID_HC_ACCEPT_MAKECHAR = 0x006d
#elif PACKET_VERSION >= 20111101
	ID_HC_ACCEPT_MAKECHAR = 0x006d
#elif PACKET_VERSION >= 20111025
	ID_HC_ACCEPT_MAKECHAR = 0x006d
#elif PACKET_VERSION >= 20110928
	ID_HC_ACCEPT_MAKECHAR = 0x006d
#elif PACKET_VERSION >= 20110111
	ID_HC_ACCEPT_MAKECHAR = 0x006d
#elif PACKET_VERSION >= 20110104
	ID_HC_ACCEPT_MAKECHAR = 0x006d
#elif PACKET_VERSION >= 20100803
	ID_HC_ACCEPT_MAKECHAR = 0x006d
#elif PACKET_VERSION >= 20100728
	ID_HC_ACCEPT_MAKECHAR = 0x006d
#elif PACKET_VERSION >= 20100727
	ID_HC_ACCEPT_MAKECHAR = 0x006d
#elif PACKET_VERSION >= 20100720
	ID_HC_ACCEPT_MAKECHAR = 0x006d
#elif PACKET_VERSION >= 20100105
	ID_HC_ACCEPT_MAKECHAR = 0x006d
#elif PACKET_VERSION >= 20090617
	ID_HC_ACCEPT_MAKECHAR = 0x006d
#elif PACKET_VERSION >= 20090107
	ID_HC_ACCEPT_MAKECHAR = 0x006d
#elif PACKET_VERSION >= 20081217
	ID_HC_ACCEPT_MAKECHAR = 0x006d
#elif PACKET_VERSION >= 20080827
	ID_HC_ACCEPT_MAKECHAR = 0x006d
#elif PACKET_VERSION >= 20061030
	ID_HC_ACCEPT_MAKECHAR = 0x006d
#elif PACKET_VERSION >= 20061023
	ID_HC_ACCEPT_MAKECHAR = 0x006d
#elif PACKET_VERSION >= 20060102
	ID_HC_ACCEPT_MAKECHAR = 0x006d
#elif PACKET_VERSION >= 0
	ID_HC_ACCEPT_MAKECHAR = 0x006d
#endif
};
/**
 * @brief Main object for the aegis packet: HC_ACCEPT_MAKECHAR
 * Size : 110 @ 0
 *
 */ 
class HC_ACCEPT_MAKECHAR : public Base::NetworkPacket<CharSocket>
{
public:
	HC_ACCEPT_MAKECHAR(std::shared_ptr<CharSocket> sock);
	~HC_ACCEPT_MAKECHAR();


	void prepare();

private:
	ByteBuffer serialize() override;

protected:
	/* Structure Goes Here */
};
}
}
}
#endif /* HORIZON_CHAR_HC_ACCEPT_MAKECHAR_HPP */
