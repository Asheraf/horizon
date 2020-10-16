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

#ifndef HORIZON_HC_ACCEPT_ENTER_HPP
#define HORIZON_HC_ACCEPT_ENTER_HPP

#include "Server/Common/Configuration/Horizon.hpp"
#include "Server/Common/Base/NetworkPacket.hpp"

namespace Horizon
{
namespace Char
{
class CharSession;
enum {
	ID_HC_ACCEPT_ENTER = 0x006b
};

/**
 * @brief Main object for the aegis packet: HC_ACCEPT_ENTER
 * Size : -1 @ 0
 *
 */ 
class HC_ACCEPT_ENTER : public Base::NetworkPacket<CharSession>
{
public:
	HC_ACCEPT_ENTER(std::shared_ptr<CharSession> s);
	virtual ~HC_ACCEPT_ENTER();


	bool prepare_and_deliver(uint32_t account_id, uint8_t max_char_slots, uint8_t permitted_slots, uint8_t total_premium_slots);
	void deliver();
	virtual void handle(ByteBuffer &&buf) override;
	void deserialize(ByteBuffer &buf);

	/* Structure Goes Here */
	uint16_t _packet_length{24};
#if PACKET_VERSION >= 20100413
	uint8_t _max_char_slots{MAX_CHARACTER_SLOTS};
	uint8_t _permitted_slots{MAX_CHARACTER_SLOTS};
	// Total premium slots out of the max_char_slots which are premium. (if not permitted will show red)
	uint8_t _total_premium_slots{MAX_CHARACTER_SLOTS};
#endif
	uint8_t _unknown_bytes[20]{0}; ///< 20 Unknown bytes.
};
}
}

#endif /* HORIZON_HC_ACCEPT_ENTER_HPP */
