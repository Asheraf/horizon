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

#ifndef HORIZON_AC_REQ_LOGIN_CARDPASS_HPP
#define HORIZON_AC_REQ_LOGIN_CARDPASS_HPP

#include "Server/Common/Configuration/Horizon.hpp"
#include "Server/Common/Base/NetworkPacket.hpp"

namespace Horizon
{
namespace Auth
{
class AuthSession;
enum {
#if PACKET_VERSION >= 20060109
	ID_AC_REQ_LOGIN_CARDPASS = 0x0263
#elif PACKET_VERSION >= 0
	ID_AC_REQ_LOGIN_CARDPASS = 0x0263
#endif
};
/**
 * @brief Main object for the aegis packet: AC_REQ_LOGIN_CARDPASS
 * Size : 11 @ 0
 *
 */ 
class AC_REQ_LOGIN_CARDPASS : public Base::NetworkPacket<AuthSession>
{
public:
	AC_REQ_LOGIN_CARDPASS(std::shared_ptr<AuthSession> s);
	virtual ~AC_REQ_LOGIN_CARDPASS();


	void deliver();
	ByteBuffer &serialize();
	virtual void handle(ByteBuffer &&buf) override;
	void deserialize(ByteBuffer &buf);

protected:
	/* Structure Goes Here */
};
}
}

#endif /* HORIZON_AC_REQ_LOGIN_CARDPASS_HPP */
