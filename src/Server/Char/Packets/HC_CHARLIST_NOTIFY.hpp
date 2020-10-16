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

#ifndef HORIZON_HC_CHARLIST_NOTIFY_HPP
#define HORIZON_HC_CHARLIST_NOTIFY_HPP

#include "Server/Common/Configuration/Horizon.hpp"
#include "Server/Common/Base/NetworkPacket.hpp"

namespace Horizon
{
namespace Char
{
class CharSession;
enum {
#if PACKET_VERSION >= 20130327
	ID_HC_CHARLIST_NOTIFY = 0x09a0
#elif PACKET_VERSION >= 20130103
	ID_HC_CHARLIST_NOTIFY = 0x09a0
#elif PACKET_VERSION >= 20121212
	ID_HC_CHARLIST_NOTIFY = 0x09a0
#elif PACKET_VERSION >= 0
	ID_HC_CHARLIST_NOTIFY = 0x09a0
#endif
};
/**
 * @brief Main object for the aegis packet: HC_CHARLIST_NOTIFY
 * Size : 6 @ 0
 *
 */ 
class HC_CHARLIST_NOTIFY : public Base::NetworkPacket<CharSession>
{
public:
	HC_CHARLIST_NOTIFY(std::shared_ptr<CharSession> s);
	virtual ~HC_CHARLIST_NOTIFY();


	void deliver();
	ByteBuffer &serialize();
	virtual void handle(ByteBuffer &&buf) override;
	void deserialize(ByteBuffer &buf);

protected:
	/* Structure Goes Here */
};
}
}

#endif /* HORIZON_HC_CHARLIST_NOTIFY_HPP */
