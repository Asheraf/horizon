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

#ifndef HORIZON_CA_LOGIN_HPP
#define HORIZON_CA_LOGIN_HPP

#include "Server/Common/Configuration/Horizon.hpp"
#include "Server/Common/Base/NetworkPacket.hpp"

namespace Horizon
{
namespace Auth
{
class AuthSession;
enum {
	ID_CA_LOGIN = 0x0064
};

/**
 * @brief Main object for the aegis packet: CA_LOGIN
 * Size : 55 @ 0
 *
 */ 
class CA_LOGIN : public Base::NetworkPacket<AuthSession>
{
public:
	CA_LOGIN(std::shared_ptr<AuthSession> s);
	virtual ~CA_LOGIN();


	void deliver();

	ByteBuffer &serialize();

	virtual void handle(ByteBuffer &&buf) override;

	void deserialize(ByteBuffer &buf);

protected:
	/* Structure Goes Here */
    uint32_t _version{0};       ///< Client Version Information
    char _username[24]{0};    ///< Username
    char _password[24]{0};    ///< Password
    uint8_t _client_type{0};    ///< Client Type
};
}
}
#endif /* HORIZON_CA_LOGIN_HPP */
