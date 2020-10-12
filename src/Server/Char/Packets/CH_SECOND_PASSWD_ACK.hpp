/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 * Copyright (c) 2020- Horizon Dev Team.
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

#ifndef HORIZON_CH_SECOND_PASSWD_ACK_HPP
#define HORIZON_CH_SECOND_PASSWD_ACK_HPP

#include "Server/Common/Configuration/Horizon.hpp"
#include "Server/Common/Base/NetworkPacket.hpp"

namespace Horizon
{
namespace Char
{
class CharSocket;
enum {
#if PACKETVER >= 20110308
	ID_CH_SECOND_PASSWD_ACK = 0x08b8
#elif PACKETVER >= 20110215
	ID_CH_SECOND_PASSWD_ACK = 0x08b8
#elif PACKETVER >= 0
	ID_CH_SECOND_PASSWD_ACK = 0x08b8
#endif
};
/**
 * @brief Main object for the aegis packet: CH_SECOND_PASSWD_ACK
 * Size : 10 @ 0
 *
 */ 
class CH_SECOND_PASSWD_ACK : public Base::NetworkPacket<CharSocket>
{
public:
	CH_SECOND_PASSWD_ACK(std::shared_ptr<CharSocket> sock);
	virtual ~CH_SECOND_PASSWD_ACK();


	void deliver();
	ByteBuffer &serialize();
	virtual void handle(ByteBuffer &&buf) override;
	void deserialize(ByteBuffer &buf);

protected:
	/* Structure Goes Here */
};
}
}

#endif /* HORIZON_CH_SECOND_PASSWD_ACK_HPP */