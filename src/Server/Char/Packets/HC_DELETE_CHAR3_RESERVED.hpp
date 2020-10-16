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

#ifndef HORIZON_HC_DELETE_CHAR3_RESERVED_HPP
#define HORIZON_HC_DELETE_CHAR3_RESERVED_HPP

#include "Server/Common/Configuration/Horizon.hpp"
#include "Server/Common/Base/NetworkPacket.hpp"

namespace Horizon
{
namespace Char
{

class CharSession;
enum {
#if PACKET_VERSION >= 20100713
	ID_HC_DELETE_CHAR3_RESERVED = 0x0828
#elif PACKET_VERSION >= 0
	ID_HC_DELETE_CHAR3_RESERVED = 0x0828
#endif
};
/**
 * @brief Main object for the aegis packet: HC_DELETE_CHAR3_RESERVED
 * Size : 14 @ 0
 *
 */ 
class HC_DELETE_CHAR3_RESERVED : public Base::NetworkPacket<CharSession>
{
public:
	HC_DELETE_CHAR3_RESERVED(std::shared_ptr<CharSession> s);
	virtual ~HC_DELETE_CHAR3_RESERVED();

	void deliver(uint32_t char_id, character_delete_result res, uint32_t date);
	ByteBuffer &serialize();
	virtual void handle(ByteBuffer &&buf) override;
	void deserialize(ByteBuffer &buf);

protected:
	/* Size: 14 bytes */
	uint32_t _character_id{0};
	character_delete_result _result{ CHAR_DEL_RESULT_UNKNOWN };
	uint32_t _deletion_date{0};
};
}
}

#endif /* HORIZON_HC_DELETE_CHAR3_RESERVED_HPP */
