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

#include "HC_ACK_CHARINFO_PER_PAGE.hpp"
#include "Server/Char/Session/CharSession.hpp"
#include "Server/Common/SQL/Character/Character.hpp"
#include "Server/Common/SQL/Character/Status.hpp"
#include "Server/Char/Char.hpp"

#include <sqlpp11/sqlpp11.h>
#include <sqlpp11/functions.h>

using namespace Horizon::Char;
using namespace Horizon::Base;

HC_ACK_CHARINFO_PER_PAGE::HC_ACK_CHARINFO_PER_PAGE(std::shared_ptr<CharSession> s)
 : NetworkPacket<CharSession>(ID_HC_ACK_CHARINFO_PER_PAGE, s) { }

HC_ACK_CHARINFO_PER_PAGE::~HC_ACK_CHARINFO_PER_PAGE() { }

void HC_ACK_CHARINFO_PER_PAGE::prepare_and_deliver()
{
	SQL::TableCharacters tch;
	SQL::TableCharacterStatus tcs;
	
	std::shared_ptr<sqlpp::mysql::connection> conn = sChar->get_db_connection();
	
	auto cres = (*conn)(select(all_of(tch).as(sqlpp::alias::left), all_of(tcs).as(sqlpp::alias::right)).from(tch.join(tcs).on(tch.id == tcs.id)).where(tch.account_id == get_session()->get_session_data()._account_id));
	
	_packet_length = 4;
	std::vector<s_hc_character_list_data> vc;
	for (auto i = cres.begin(); i != cres.end(); i++)
	{
		s_hc_character_list_data c;
		
		c._character_id = i->right.id;          ///< 0
		c._base_experience = i->right.base_experience;
		c._zeny = i->right.zeny;                    ///< 8
		c._job_experience = i->right.job_experience;
		c._job_level = i->right.job_level;               ///< 16
		c._sc_opt1 = 0;                 ///< 20 Probably OPT1 / 2
		c._sc_opt2 = 0;                 ///< 24
		c._body_state = i->right.body_state;              ///< 28
		c._virtue = i->right.virtue;                  ///< 32
		c._honor = i->right.honor;                   ///< 36
		c._status_points = i->right.status_points;           ///< 40
		c._hp = i->right.hp;                      ///< 42
		c._maximum_hp = i->right.maximum_hp;              ///< 46
		c._sp = i->right.sp;                      ///< 50
		c._maximum_sp = i->right.maximum_sp;              ///< 52
		c._walk_speed = DEFAULT_MOVEMENT_SPEED;              ///< 54
		c._job_id = i->right.job_id;                  ///< 56
		c._hair_view_id = i->right.hair_style_id;            ///< 58
#if PACKET_VERSION >= 20141022
		c._body_view_id = i->right.body_id;            ///< 60 p->body in hercules.
#endif
		c._weapon_view_id = i->right.weapon_id;          ///< 62 OPTION_* in hercules.
		c._base_level = i->right.base_level;              ///< 64
		c._skill_point = i->right.skill_points;             ///< 66
		c._head_bottom_view_id = i->right.head_bottom_view_id;     ///< 68
		c._shield_id = i->right.shield_id;               ///< 70
		c._head_top_view_id = i->right.head_top_view_id;        ///< 72
		c._head_mid_view_id = i->right.head_mid_view_id;        ///< 74
		c._hair_color_id = i->right.hair_color_id;           ///< 76
		c._clothes_color_id = i->right.cloth_color_id;        ///< 78
		
		std::string lname =i->left.name;
		strncpy(c._name,  lname.c_str(), MAX_UNIT_NAME_LENGTH);  ///< 80
		
		c._strength = i->right.strength;                 ///< 104
		c._agility = i->right.agility;
		c._vitality = i->right.vitality;
		c._intelligence = i->right.intelligence;
		c._dexterity = i->right.dexterity;
		c._luck = i->right.luck;
		c._char_slot = i->left.slot;               ///< 110
#if PACKET_VERSION >= 20061023
		c._rename_count = i->left.rename_count ? 0 : 1;            ///< 112
#endif
#if (PACKET_VERSION >= 20100720 && PACKET_VERSION <= 20100727) || PACKET_VERSION >= 20100803
		std::string current_map = i->left.current_map;
		strncpy(c._map_name,  current_map.c_str(), MAP_NAME_LENGTH_EXT);///< 114
#endif
#if PACKET_VERSION >= 20100803
		std::chrono::system_clock::time_point tp = i->left.deleted_at;             ///< 130
		std::chrono::system_clock::duration dn = tp.time_since_epoch();
		c._deleted_at = dn.count() * std::chrono::system_clock::period::num / std::chrono::system_clock::period::den;
#endif
#if PACKET_VERSION >= 20110111
		c._robe_view_id = i->right.robe_view_id;            ///< 134
#endif
#if PACKET_VERSION != 20111116 //2011-11-16 wants 136, ask gravity.
#if PACKET_VERSION >= 20110928
		c._change_slot_count = i->left.change_slot_count ? 1 : 0;       ///< 138
#endif
#if PACKET_VERSION >= 20111025
		c._addon_option = i->left.rename_count ? 1 : 0;            ///< 142 1: Displays "Addon" on side-bar.
#endif
#if PACKET_VERSION >= 20141016
		c._gender = i->left.gender == "M" ? 1 : i->left.gender == "F" ? 0 : 99;                   ///< 146 0: Female, 1: Male, 99: Account-based.
#endif
#endif
		_packet_length += sizeof(c);
		vc.push_back(c);
	}
	
	buf() << _packet_id;
	buf() << _packet_length;
	
	for (s_hc_character_list_data c : vc)
		buf().append((uint8_t *) &c, sizeof(s_hc_character_list_data));
	
	HLog(debug) << "Sending character list data size: " << sizeof(s_hc_character_list_data);
	
	deliver();
}

void HC_ACK_CHARINFO_PER_PAGE::deliver()
{
	transmit();
}

void HC_ACK_CHARINFO_PER_PAGE::handle(ByteBuffer &&buf)
{
}

void HC_ACK_CHARINFO_PER_PAGE::deserialize(ByteBuffer &buf)
{
}

