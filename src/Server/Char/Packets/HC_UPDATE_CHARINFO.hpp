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

#ifndef HORIZON_HC_UPDATE_CHARINFO_HPP
#define HORIZON_HC_UPDATE_CHARINFO_HPP

#include "Server/Common/Configuration/Horizon.hpp"
#include "Server/Common/Base/NetworkPacket.hpp"

namespace Horizon
{
namespace Char
{
class CharSession;
enum {
#if PACKET_VERSION >= 20170906
	ID_HC_UPDATE_CHARINFO = 0x08e3
#elif PACKET_VERSION >= 20170830
	ID_HC_UPDATE_CHARINFO = 0x08e3
#elif PACKET_VERSION >= 20170104
	ID_HC_UPDATE_CHARINFO = 0x08e3
#elif PACKET_VERSION >= 20140820
	ID_HC_UPDATE_CHARINFO = 0x08e3
#elif PACKET_VERSION >= 20140625
	ID_HC_UPDATE_CHARINFO = 0x08e3
#elif PACKET_VERSION >= 20140108
	ID_HC_UPDATE_CHARINFO = 0x08e3
#elif PACKET_VERSION >= 20111101
	ID_HC_UPDATE_CHARINFO = 0x08e3
#elif PACKET_VERSION >= 20111025
	ID_HC_UPDATE_CHARINFO = 0x08e3
#elif PACKET_VERSION >= 20111017
	ID_HC_UPDATE_CHARINFO = 0x08e3
#elif PACKET_VERSION >= 0
	ID_HC_UPDATE_CHARINFO = 0x08e3
#endif
};
/**
 * @brief Main object for the aegis packet: HC_UPDATE_CHARINFO
 * Size : 157 @ 0
 *
 */ 
class HC_UPDATE_CHARINFO : public Base::NetworkPacket<CharSession>
{
public:
	HC_UPDATE_CHARINFO(std::shared_ptr<CharSession> s);
	virtual ~HC_UPDATE_CHARINFO();


	void deliver();
	ByteBuffer &serialize();
	virtual void handle(ByteBuffer &&buf) override;
	void deserialize(ByteBuffer &buf);

protected:
	/* Structure Goes Here */
};
}
}

#endif /* HORIZON_HC_UPDATE_CHARINFO_HPP */
