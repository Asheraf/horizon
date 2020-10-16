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

#include "CA_LOGIN.hpp"

#include "Server/Auth/Auth.hpp"
#include "Server/Auth/Interface/AuthClientInterface.hpp"
#include "Server/Auth/Session/AuthSession.hpp"

#include <string>

using namespace Horizon::Auth;

CA_LOGIN::CA_LOGIN(std::shared_ptr<AuthSession> s)
 : Base::NetworkPacket<AuthSession>(ID_CA_LOGIN, s) { }

CA_LOGIN::~CA_LOGIN() { }

void CA_LOGIN::deliver()
{
}

ByteBuffer &CA_LOGIN::serialize()
{
	return buf();
}

void CA_LOGIN::handle(ByteBuffer &&buf)
{
    deserialize(buf);
	
	get_session()->clif()->process_login(_username, _password, _version, _client_type);
}

void CA_LOGIN::deserialize(ByteBuffer &buf)
{
    buf >> _packet_id;
    buf >> _version;
    buf.read(_username, sizeof(_username));
    buf.read(_password, sizeof(_password));
    buf >> _client_type;
}

