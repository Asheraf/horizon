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

#ifndef HORIZON_CH_ENTER_HPP
#define HORIZON_CH_ENTER_HPP

#include "Server/Common/Configuration/Horizon.hpp"
#include "Server/Common/Base/NetworkPacket.hpp"

namespace Horizon
{
namespace Char
{
class CharSession;
enum {
	ID_CH_ENTER = 0x0065
};
/**
 * @brief Main object for the aegis packet: CH_ENTER
 * Size : 17 @ 0
 *
 */ 
class CH_ENTER : public Base::NetworkPacket<CharSession>
{
public:
	CH_ENTER(std::shared_ptr<CharSession> s);
	virtual ~CH_ENTER();

	void deliver();
	ByteBuffer &serialize();
	virtual void handle(ByteBuffer &&buf) override;
	void deserialize(ByteBuffer &buf);

	// 0065 <account id>.L <login id1>.L <login id2>.L <???>.W <sex>.B
	uint32_t _account_id{0};
	uint32_t _auth_code{0};
	uint32_t _account_level{0};
	uint16_t _unknown{0};
	uint8_t _gender{0};
};
}
}

#endif /* HORIZON_CH_ENTER_HPP */
