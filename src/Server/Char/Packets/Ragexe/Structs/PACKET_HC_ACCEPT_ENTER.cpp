/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
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

#include "PACKET_HC_ACCEPT_ENTER.hpp"
#include "Server/Common/Definitions/Horizon.hpp"
#include "Server/Common/Models/Character/Character.hpp"
#include "Server/Common/Models/Character/Status.hpp"

using namespace Horizon::Char::Ragexe;
using namespace Horizon::Models::Character;

void PACKET_HC_ACCEPT_ENTER::character_list_data::create_from_model(std::shared_ptr<Character> c)
{
	std::shared_ptr<Status> status = c->get_status_model();

	character_id = c->get_id();
	base_experience = status->get_base_exp();
	zeny = status->get_zeny();
	job_experience = status->get_job_exp();
	job_level = status->get_job_level();
	body_state = status->get_body_state();
	virtue = status->get_virtue();
	honor = status->get_honor();
	status_points = status->get_status_points();
	hp = status->get_hp();
	maximum_hp = status->get_max_hp();
	sp = status->get_sp();
	maximum_sp = status->get_max_sp();
	walk_speed = DEFAULT_MOVEMENT_SPEED;
	job_id = status->get_job_id();
	hair_view_id = status->get_hair_style_id();
	body_view_id = status->get_body_id();
	weapon_view_id = status->get_weapon_id();
	base_level = status->get_base_level();
	skill_point = status->get_skill_points();
	head_bottom_view_id = status->get_head_bottom_view_id();
	shield_id = status->get_shield_id();
	head_top_view_id = status->get_head_top_view_id();
	head_mid_view_id = status->get_head_mid_view_id();
	hair_color_id = status->get_hair_color_id();
	clothes_color_id = status->get_cloth_color_id();
	strncpy(name, c->get_name().c_str(), MAX_UNIT_NAME_LENGTH);
	strength = status->get_strength();
	agility = status->get_agility();
	vitality = status->get_vitality();
	intelligence = status->get_intelligence();
	dexterity = status->get_dexterity();
	luck = status->get_luck();
	char_slot = c->get_slot();
	rename_count = c->get_rename_count();
	strncpy(map_name, c->get_current_map().c_str(), MAP_NAME_LENGTH_EXT);
	strcat(map_name, ".gat");
	deleted_at = c->get_deleted_at();
	robe_view_id = status->get_robe_view_id();
	change_slot_count = c->get_change_slot_count();
	gender = c->get_gender();
}

PacketBuffer PACKET_HC_ACCEPT_ENTER::character_list_data::serialize(PacketBuffer &buf)
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
	buf << job_id;
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
	buf << deleted_at;
	buf << robe_view_id;
	buf << change_slot_count;
	buf << addon_option;
	buf << gender;

	return buf;
}
