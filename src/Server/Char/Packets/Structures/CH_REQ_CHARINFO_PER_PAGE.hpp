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

#ifndef HORIZON_CHAR_CH_REQ_CHARINFO_PER_PAGE_HPP
#define HORIZON_CHAR_CH_REQ_CHARINFO_PER_PAGE_HPP

#include "Server/Common/Configuration/Horizon.hpp"
#include "Server/Common/Base/NetworkPacket.hpp"

namespace Horizon
{
namespace Char
{
class AuthSocket;
namespace Packet
{

enum {
#if PACKET_VERSION >= 20121024
	ID_CH_REQ_CHARINFO_PER_PAGE = 0x099c
#elif PACKET_VERSION >= 0
	ID_CH_REQ_CHARINFO_PER_PAGE = 0x099c
#endif
};
/**
 * @brief Main object for the aegis packet: CH_REQ_CHARINFO_PER_PAGE
 * Size : 6 @ 0
 *
 */ 
class CH_REQ_CHARINFO_PER_PAGE : public Base::NetworkPacket<CharSocket>
{
public:
	CH_REQ_CHARINFO_PER_PAGE(std::shared_ptr<CharSocket> sock);
	~CH_REQ_CHARINFO_PER_PAGE();


	void handle(ByteBuffer &buf);

private:
	void deserialize(ByteBuffer &buf) override;

protected:
	/* Structure Goes Here */
};
}
}
}
#endif /* HORIZON_CHAR_CH_REQ_CHARINFO_PER_PAGE_HPP */
