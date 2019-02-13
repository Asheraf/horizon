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
 * Under a proprietary license this file is not for use
 * or viewing without permission.
 **************************************************/

#ifndef HORIZON_CHAR_RAGEXE_20170906_PACKET_HC_ACCEPT_ENTER_HPP
#define HORIZON_CHAR_RAGEXE_20170906_PACKET_HC_ACCEPT_ENTER_HPP

#include "Server/Char/Packets/Ragexe/20170906/PacketsRagexe20170906.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_HC_ACCEPT_ENTER.hpp"
#include "Server/Char/Packets/Ragexe/Packets.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Char
{
namespace Ragexe20170906
{
struct PACKET_HC_ACCEPT_ENTER : public Ragexe::PACKET_HC_ACCEPT_ENTER
{
	PACKET_HC_ACCEPT_ENTER(uint16_t packet_id = Ragexe::HC_ACCEPT_ENTER) : Ragexe::PACKET_HC_ACCEPT_ENTER(packet_id) { }

	uint16_t get_length(uint8_t max_chars = 0) { return 27 + (155 * max_chars); }

	struct character_list_data : public Ragexe::PACKET_HC_ACCEPT_ENTER::character_list_data
	{
		virtual PacketBuffer serialize(PacketBuffer &buf)
		{
			buf << character_id;
			buf << base_experience;
			buf << zeny;
			buf << job_experience;
			buf << job_level;
			buf << sc_opt1;
			buf << sc_opt2;
			buf << body_state;
			buf << virtue;
			buf << honor;
			buf << status_points;
			buf << hp;
			buf << maximum_hp;
			buf << sp;
			buf << maximum_sp;
			buf << walk_speed;
			buf << job_class;
			buf << hair_view_id;
			buf << body_view_id;
			buf << weapon_view_id;
			buf << base_level;
			buf << skill_point;
			buf << head_bottom_view_id;
			buf << shield_id;
			buf << head_top_view_id;
			buf << head_mid_view_id;
			buf << hair_color_id;
			buf << clothes_color_id;
			buf.append(name, sizeof(name));
			buf << strength;
			buf << agility;
			buf << vitality;
			buf << intelligence;
			buf << dexterity;
			buf << luck;
			buf << char_slot;
			buf << rename_count;
			buf.append(map_name, sizeof(map_name));
			buf << delete_date;
			buf << robe_view_id;
			buf << change_slot_count;
			buf << addon_option;
			buf << gender;

			return buf;
		}
	};
};
}
}
}

#endif /* HORIZON_CHAR_RAGEXE_20170906_PACKET_HC_ACCEPT_ENTER_HPP */
