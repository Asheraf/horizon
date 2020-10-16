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

#ifndef HORIZON_HC_DELETE_CHAR3_CANCEL_HPP
#define HORIZON_HC_DELETE_CHAR3_CANCEL_HPP

#include "Server/Common/Configuration/Horizon.hpp"
#include "Server/Common/Base/NetworkPacket.hpp"

namespace Horizon
{
namespace Char
{

enum hc_delete_cancel_result : uint32_t {
	CHAR3_DEL_CANCEL_SUCCESS = 1,
	CHAR3_DEL_CANCEL_FAILURE = 2
};

class CharSession;
enum {
#if PACKET_VERSION >= 20100720
	ID_HC_DELETE_CHAR3_CANCEL = 0x082c
#elif PACKET_VERSION >= 20100713
	ID_HC_DELETE_CHAR3_CANCEL = 0x082c
#elif PACKET_VERSION >= 0
	ID_HC_DELETE_CHAR3_CANCEL = 0x082c
#endif
};
/**
 * @brief Main object for the aegis packet: HC_DELETE_CHAR3_CANCEL
 * Size : 10 @ 0
 *
 */ 
class HC_DELETE_CHAR3_CANCEL : public Base::NetworkPacket<CharSession>
{
public:
	HC_DELETE_CHAR3_CANCEL(std::shared_ptr<CharSession> s);
	virtual ~HC_DELETE_CHAR3_CANCEL();

	void deliver(uint32_t char_id, hc_delete_cancel_result result);
	ByteBuffer &serialize();
	virtual void handle(ByteBuffer &&buf) override;
	void deserialize(ByteBuffer &buf);

protected:
	uint32_t _character_id{0};
	hc_delete_cancel_result _result{0}; // either 1 or 2.
};
}
}

#endif /* HORIZON_HC_DELETE_CHAR3_CANCEL_HPP */
