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

#ifndef HORIZON_ZONE_RAGEXE_PACKET_ZC_NOTIFY_STANDENTRY10_HPP
#define HORIZON_ZONE_RAGEXE_PACKET_ZC_NOTIFY_STANDENTRY10_HPP


#include "Server/Zone/Packets/Ragexe/Packets.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe
{
struct PACKET_ZC_NOTIFY_STANDENTRY10 : public Packet
{
	PACKET_ZC_NOTIFY_STANDENTRY10(uint16_t packet_id = ZC_NOTIFY_STANDENTRY10) : Packet(packet_id) { }

	virtual PacketBuffer serialize()
	{
		PacketBuffer buf(packet_id);

		entry.serialize(buf);

		return buf;
	}

	virtual void deserialize(PacketBuffer &/*buf*/) { }

	virtual PACKET_ZC_NOTIFY_STANDENTRY10 & operator << (PacketBuffer &right)
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right)
	{
		return right = serialize();
	}

	/* Size: -1 bytes */
	struct zc_viewport_entry : public entity_viewport_entry
	{
		zc_viewport_entry() : entity_viewport_entry() { }

		virtual entity_viewport_entry operator = (entity_viewport_entry const &right) override
		{
			entity_viewport_entry::operator = (right);
			return *this;
		}

		virtual PacketBuffer serialize(PacketBuffer &buf)
		{
			char packed_pos[3]{0};

			buf << packet_length;
			buf << (uint8_t) unit_type;
			buf << guid;
			buf << character_id;
			buf << speed;
			buf << body_state;
			buf << health_state;
			buf << effect_state;
			buf << job_id;
			buf << hair_style_id;
			buf << weapon_id;
			buf << headgear_bottom_id;
			buf << headgear_top_id;
			buf << headgear_mid_id;
			buf << hair_color_id;
			buf << cloth_color_id;
			buf << (uint16_t) head_direction;
			buf << robe_id;
			buf << guild_id;
			buf << guild_emblem_version;
			buf << honor;
			buf << virtue;
			buf << in_pk_mode;
			buf << gender;
			PackPosition((int8_t *) packed_pos, current_x, current_y, current_dir);
			buf.append(packed_pos, sizeof(packed_pos));
			buf << x_size;
			buf << y_size;
			buf << (uint8_t) posture;
			buf << base_level;
			buf << font;
			buf << max_hp;
			buf << hp;
			buf << is_boss;
			buf << body_style_id;
			buf.append(name, sizeof(name));
			return buf;
		}

		int16_t packet_length{102 + 2};
	} entry;
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_PACKET_ZC_NOTIFY_STANDENTRY10_HPP */
