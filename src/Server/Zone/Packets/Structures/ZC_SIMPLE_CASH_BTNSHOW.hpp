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

#ifndef HORIZON_ZONE_ZC_SIMPLE_CASH_BTNSHOW_HPP
#define HORIZON_ZONE_ZC_SIMPLE_CASH_BTNSHOW_HPP

#include "Server/Common/Configuration/Horizon.hpp"
#include "Server/Common/Base/NetworkPacket.hpp"

namespace Horizon
{
namespace Zone
{
class AuthSocket;
namespace Packet
{

enum {
#if PACKET_VERSION >= 20100113
	ID_ZC_SIMPLE_CASH_BTNSHOW = 0x080d
#elif PACKET_VERSION >= 0
	ID_ZC_SIMPLE_CASH_BTNSHOW = 0x080d
#endif
};
/**
 * @brief Main object for the aegis packet: ZC_SIMPLE_CASH_BTNSHOW
 * Size : 3 @ 0
 *
 */ 
class ZC_SIMPLE_CASH_BTNSHOW : public Base::NetworkPacket<ZoneSocket>
{
public:
	ZC_SIMPLE_CASH_BTNSHOW(std::shared_ptr<ZoneSocket> sock);
	~ZC_SIMPLE_CASH_BTNSHOW();


	void prepare();

private:
	ByteBuffer serialize() override;

protected:
	/* Structure Goes Here */
};
}
}
}
#endif /* HORIZON_ZONE_ZC_SIMPLE_CASH_BTNSHOW_HPP */
