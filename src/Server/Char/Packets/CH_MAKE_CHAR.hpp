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

#ifndef HORIZON_CH_MAKE_CHAR_HPP
#define HORIZON_CH_MAKE_CHAR_HPP

#include "Server/Common/Configuration/Horizon.hpp"
#include "Server/Common/Base/NetworkPacket.hpp"

namespace Horizon
{
namespace Char
{
class CharSession;
enum {
#if PACKET_VERSION >= 20150415
	ID_CH_MAKE_CHAR = 0x0a39
#elif PACKET_VERSION >= 20150211
	ID_CH_MAKE_CHAR = 0x0a39
#elif PACKET_VERSION >= 20120307
	ID_CH_MAKE_CHAR = 0x0970
#elif PACKET_VERSION >= 0
	ID_CH_MAKE_CHAR = 0x0067
#endif
};
/**
 * @brief Main object for the aegis packet: CH_MAKE_CHAR
 * Size : 37 @ 0
 *
 */ 
class CH_MAKE_CHAR : public Base::NetworkPacket<CharSession>
{
public:
	CH_MAKE_CHAR(std::shared_ptr<CharSession> s);
	virtual ~CH_MAKE_CHAR();

	void deliver();
	ByteBuffer &serialize();
	virtual void handle(ByteBuffer &&buf) override;
	void deserialize(ByteBuffer &buf);

protected:
	// S 0a39 <name>.24B <slot>.B <hair color>.W <hair style>.W <starting job class ID>.W <Unknown>.(W or 2 B's)??? <sex>.B
	char _name[MAX_UNIT_NAME_LENGTH]{0};
	uint8_t _slot{0};
	uint16_t _hair_color{0};
	uint16_t _hair_style{0};
#if PACKET_VERSION >= 20151001
	uint16_t _job_id{0};
	char _unknown_bytes[2]{0};
	uint8_t _gender{0};
#endif
};
}
}

#endif /* HORIZON_CH_MAKE_CHAR_HPP */
