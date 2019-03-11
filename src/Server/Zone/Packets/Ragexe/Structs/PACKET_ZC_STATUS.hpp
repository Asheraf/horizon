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

#ifndef HORIZON_ZONE_RAGEXE_PACKET_ZC_STATUS_HPP
#define HORIZON_ZONE_RAGEXE_PACKET_ZC_STATUS_HPP


#include "Server/Zone/Packets/Ragexe/Packets.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe
{
struct PACKET_ZC_STATUS : public Packet
{
	PACKET_ZC_STATUS(uint16_t packet_id = ZC_STATUS) : Packet(packet_id) { }

	virtual PacketBuffer serialize()
	{
		PacketBuffer buf(packet_id);
		data.serialize(buf);
		return buf;
	}

	virtual void deserialize(PacketBuffer &/*buf*/) { }

	virtual PACKET_ZC_STATUS & operator << (PacketBuffer &right)
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right)
	{
		return right = serialize();
	}

	/* Size: 44 bytes */
	struct status_data {
		virtual PacketBuffer serialize(PacketBuffer &buf)
		{
			buf << status_points;
			buf << strength;
			buf << strength_req_stats;
			buf << agility;
			buf << agility_req_stats;
			buf << vitality;
			buf << vitality_req_stats;
			buf << intelligence;
			buf << intelligence_req_stats;
			buf << dexterity;
			buf << dexterity_req_stats;
			buf << luck;
			buf << luck_req_stats;
			buf << status_atk;
			buf << equip_atk;
			buf << equip_matk;
			buf << status_matk;
			buf << soft_def;
			buf << hard_def;
			buf << soft_mdef;
			buf << hard_mdef;
			buf << hit;
			buf << flee;
			buf << perfect_dodge;
			buf << critical;
			buf << attack_speed;
			buf << plus_aspd; // always 0 apparently.

			return buf;
		}

		uint16_t status_points{0};
		uint8_t strength{1};
		uint8_t strength_req_stats{1};
		uint8_t agility{1};
		uint8_t agility_req_stats{1};
		uint8_t vitality{1};
		uint8_t vitality_req_stats{1};
		uint8_t intelligence{1};
		uint8_t intelligence_req_stats{1};
		uint8_t dexterity{1};
		uint8_t dexterity_req_stats{1};
		uint8_t luck{1};
		uint8_t luck_req_stats{1};
		uint16_t status_atk{1};
		uint16_t equip_atk{1};
		uint16_t status_matk{1};
		uint16_t equip_matk{1};
		uint16_t soft_def{1};
		uint16_t hard_def{1};
		uint16_t soft_mdef{1};
		uint16_t hard_mdef{1};
		uint16_t hit{1};
		uint16_t flee{1};
		uint16_t perfect_dodge{1};
		uint16_t critical{1};
		uint16_t attack_speed{0};
		uint16_t plus_aspd{0}; // always 0 apparently.
	} data;
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_PACKET_ZC_STATUS_HPP */
