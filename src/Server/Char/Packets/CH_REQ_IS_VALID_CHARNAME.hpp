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

#ifndef HORIZON_CH_REQ_IS_VALID_CHARNAME_HPP
#define HORIZON_CH_REQ_IS_VALID_CHARNAME_HPP

#include "Server/Common/Configuration/Horizon.hpp"
#include "Server/Common/Base/NetworkPacket.hpp"

namespace Horizon
{
namespace Char
{
class CharSession;
enum {
#if PACKET_VERSION >= 20061030
	ID_CH_REQ_IS_VALID_CHARNAME = 0x028d
#elif PACKET_VERSION >= 20061023
	ID_CH_REQ_IS_VALID_CHARNAME = 0x028d
#elif PACKET_VERSION >= 0
	ID_CH_REQ_IS_VALID_CHARNAME = 0x028d
#endif
};
/**
 * @brief Main object for the aegis packet: CH_REQ_IS_VALID_CHARNAME
 * Size : 34 @ 0
 *
 */ 
class CH_REQ_IS_VALID_CHARNAME : public Base::NetworkPacket<CharSession>
{
public:
	CH_REQ_IS_VALID_CHARNAME(std::shared_ptr<CharSession> s);
	virtual ~CH_REQ_IS_VALID_CHARNAME();


	void deliver();
	ByteBuffer &serialize();
	virtual void handle(ByteBuffer &&buf) override;
	void deserialize(ByteBuffer &buf);

protected:
	/* Structure Goes Here */
};
}
}

#endif /* HORIZON_CH_REQ_IS_VALID_CHARNAME_HPP */
