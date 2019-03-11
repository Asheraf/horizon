/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 *
 * Copyright (c) 2019 Sagun K. (sagunxp@gmail.com).
 * Copyright (c) 2019 Horizon Dev Team.
 *
 * Base Author - Sagun K. (sagunxp@gmail.com)
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

#ifndef HORIZON_ZONE_RAGEXE_20171206_PACKET_ZC_LONGPAR_CHANGE_HPP
#define HORIZON_ZONE_RAGEXE_20171206_PACKET_ZC_LONGPAR_CHANGE_HPP

#include "Server/Zone/Packets/Ragexe/20171206/PacketsRagexe20171206.hpp"
#include "Server/Zone/Packets/Ragexe/Structs/PACKET_ZC_LONGPAR_CHANGE.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe20171206
{
struct PACKET_ZC_LONGPAR_CHANGE : public Horizon::Zone::Ragexe::PACKET_ZC_LONGPAR_CHANGE
{
	PACKET_ZC_LONGPAR_CHANGE(uint16_t packet_id = ZC_LONGPAR_CHANGE) : Horizon::Zone::Ragexe::PACKET_ZC_LONGPAR_CHANGE(packet_id) { }

	virtual PacketBuffer serialize() override
	{
		PacketBuffer buf(packet_id);
		buf << type << value;
		return buf;
	}

	virtual void deserialize(PacketBuffer &/*buf*/) override { }

	virtual PACKET_ZC_LONGPAR_CHANGE & operator << (PacketBuffer &right) override
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right) override
	{
		return right = serialize();
	}

	/* Size: 12 bytes */
	uint16_t type{0};
	uint64_t value{0};
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_20171206_PACKET_ZC_LONGPAR_CHANGE_HPP */
