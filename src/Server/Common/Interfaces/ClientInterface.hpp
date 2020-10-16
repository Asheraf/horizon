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

#ifndef HORIZON_CLIENTINTERFACE_HPP
#define HORIZON_CLIENTINTERFACE_HPP

#include <memory>

namespace Horizon
{

template <typename SessionType>
class ClientInterface
{
public:
	ClientInterface(std::shared_ptr<SessionType> s) : _session(s) { }
	~ClientInterface() { }

	std::shared_ptr<SessionType> get_session() { return _session.lock(); }
	void set_session(std::shared_ptr<SessionType> s) { _session = s; }

private:
	std::weak_ptr<SessionType> _session;
};

}

#endif /* HORIZON_CLIENTINTERFACE_HPP */
