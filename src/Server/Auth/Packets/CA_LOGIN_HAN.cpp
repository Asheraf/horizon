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

#include "CA_LOGIN_HAN.hpp"
#include "Server/Auth/Socket/AuthSocket.hpp"

using namespace Horizon;

CA_LOGIN_HAN::CA_LOGIN_HAN(std::shared_ptr<AuthSocket> sock)
 : Base::NetworkPacket<AuthSocket>(ID_CA_LOGIN_HAN, sock) { }

CA_LOGIN_HAN::~CA_LOGIN_HAN() { }

void CA_LOGIN_HAN::deliver()
{
}

ByteBuffer &CA_LOGIN_HAN::serialize()
{
	return buf();
}

void CA_LOGIN_HAN::handle(ByteBuffer &&buf)
{
}

void CA_LOGIN_HAN::deserialize(ByteBuffer &buf)
{
}

