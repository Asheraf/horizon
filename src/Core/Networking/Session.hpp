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

#ifndef HORIZON_NETWORKING_SESSION_HPP
#define HORIZON_NETWORKING_SESSION_HPP

#include "Core/Networking/Buffer/ByteBuffer.hpp"

#include <memory>

namespace Horizon
{
namespace Networking
{
template <class SocketType, class SessionType>
class Session : public std::enable_shared_from_this<SessionType>
{
public:
	Session(std::weak_ptr<SocketType> socket)
	: _socket(socket)
	{
		//
	}

	virtual ~Session()
	{
		//
	}

	/* Socket Type */
	std::shared_ptr<SocketType> get_socket() { return _socket.lock(); }
	void set_socket(std::weak_ptr<SocketType> socket) { _socket.swap(socket); }

	virtual void update(uint32_t diff) = 0;

	virtual void initialize() = 0;

private:
	std::weak_ptr<SocketType> _socket;
};
}
}

#endif /* HORIZON_NETWORKING_SESSION_HPP */
