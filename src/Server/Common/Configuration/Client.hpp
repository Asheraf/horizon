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

#ifndef HORIZON_CLIENT_HPP
#define HORIZON_CLIENT_HPP

#include <stdint.h>

#define MAX_UNIT_NAME_LENGTH 24
#define MAX_PARTY_NAME_LENGTH 24
#define MAX_GUILD_NAME_LENGTH 24
#define MAX_GUILD_POSITION_NAME_LENGTH 24
#define MAX_USERNAME_LENGTH 24
#define CLIENT_BIRTHDATE_STRING_LENGTH 6
#define MAX_BIRTHDATE_STRING_LENGTH CLIENT_BIRTHDATE_STRING_LENGTH + 5 // YYYY-MM-DD
#define MAX_PINCODE_STRING_LENGTH 5
#define MAX_EMAIL_LENGTH 40
#define MAX_IP_ADDRESS_STR_LENGTH 16
#define MAX_CHAT_STR_LENGTH 255 + 1
// For Map Names, which the client considers to be 16 in length including the .gat extension.
#define MAP_NAME_LENGTH (11 + 1)
#define MAP_NAME_LENGTH_EXT (MAP_NAME_LENGTH + 4)

#pragma pack(push, 1)
struct s_hc_character_list_data {
	uint32_t _character_id{0};            ///< 4
#if PACKET_VERSION >= 20170830
	uint64_t _base_experience{0};         ///< 12
#else
	uint32_t _base_experience{0};
#endif
	uint32_t _zeny{0};                    ///< 16
#if PACKET_VERSION >= 20170830
	uint64_t _job_experience{0};          ///< 24
#else
	uint32_t _job_experience{0};
#endif
	uint32_t _job_level{1};               ///< 28
	uint32_t _sc_opt1{0};                 ///< 32 Probably OPT1 / 2
	uint32_t _sc_opt2{0};                 ///< 36
	uint32_t _body_state{0};              ///< 40
	uint32_t _virtue{0};                  ///< 44
	uint32_t _honor{0};                   ///< 48
	uint16_t _status_points{0};           ///< 50
#if PACKET_VERSION > 20081217
	uint32_t _hp{1};                      ///< 54
	uint32_t _maximum_hp{1};              ///< 58
#else
	uint16_t _hp{1};
	uint16_t _maximum_hp{1};
#endif
	uint16_t _sp{1};                      ///< 60
	uint16_t _maximum_sp{1};              ///< 62
	uint16_t _walk_speed{DEFAULT_MOVEMENT_SPEED}; ///< 64
	uint16_t _job_id{0};                  ///< 66
	uint16_t _hair_view_id{0};            ///< 68
#if PACKET_VERSION >= 20141022
	uint16_t _body_view_id{0};            ///< 70 p->body in hercules.
#endif
	uint16_t _weapon_view_id{0};          ///< 72 OPTION_* in hercules.
	uint16_t _base_level{1};              ///< 74
	uint16_t _skill_point{0};             ///<
	uint16_t _head_bottom_view_id{0};     ///<
	uint16_t _shield_id{0};               ///<
	uint16_t _head_top_view_id{0};        ///<
	uint16_t _head_mid_view_id{0};        ///<
	uint16_t _hair_color_id{0};           ///<
	uint16_t _clothes_color_id{0};        ///< 88
	char _name[MAX_UNIT_NAME_LENGTH]{0};  ///< 112
	uint8_t _strength{1};                 ///<
	uint8_t _agility{1};                  ///<
	uint8_t _vitality{1};                 ///<
	uint8_t _intelligence{1};             ///<
	uint8_t _dexterity{1};                ///<
	uint8_t _luck{1};                     ///<
	uint16_t _char_slot{0};               ///< 120
#if PACKET_VERSION >= 20061023
	uint16_t _rename_count{0};            ///< 122
#endif
#if (PACKET_VERSION >= 20100720 && PACKET_VERSION <= 20100727) || PACKET_VERSION >= 20100803
	char _map_name[MAP_NAME_LENGTH_EXT]{0}; ///< len: 16  138
#endif
#if PACKET_VERSION >= 20100803
	uint32_t _deleted_at{0};             ///<
#endif
#if PACKET_VERSION >= 20110111
	uint32_t _robe_view_id{0};            ///<
#endif
#if PACKET_VERSION != 20111116 //2011-11-16 wants 136, ask gravity.
#if PACKET_VERSION >= 20110928
	uint32_t _change_slot_count{0};       ///< 150
#endif
#if PACKET_VERSION >= 20111025
	uint32_t _addon_option{0};            ///< 154 1: Displays "Addon" on side-bar.
#endif
#if PACKET_VERSION >= 20141016
	uint8_t _gender{0};                   ///< 155 0: Female, 1: Male, 99: Account-based.
#endif
#endif
} __attribute__((packed));
#pragma pack(pop)

enum character_delete_accept_result : uint32_t
{
	CHAR_DEL_ACCEPT_RESULT_UNKNOWN        = 0, /// 0 (0x718): An unknown error has occurred.
	CHAR_DEL_ACCEPT_RESULT_SUCCESS        = 1, /// 1: none/success
	CHAR_DEL_ACCEPT_RESULT_SYSTEM_ERR     = 2, /// 2: Due to system settings can not be deleted.
	CHAR_DEL_ACCEPT_RESULT_DATABASE_ERR   = 3, /// 3: A database error occurred.
	CHAR_DEL_ACCEPT_RESULT_TIME_ERR       = 4, /// 4: Deleting is not yet possible.
	CHAR_DEL_ACCEPT_RESULT_BIRTHDAY_ERR   = 5, /// 5: Date of birth do not match.
};

enum character_delete_result : uint32_t
{
	CHAR_DEL_RESULT_UNKNOWN        = 0, /// 0 (0x718): An unknown error has occurred.
	CHAR_DEL_RESULT_SUCCESS        = 1, /// 1: none/success
	CHAR_DEL_RESULT_SYSTEM_ERR     = 2, /// 2: Due to system settings can not be deleted.
	CHAR_DEL_RESULT_DATABASE_ERR   = 3, /// 3: A database error occurred.
	CHAR_DEL_RESULT_GUILD_ERR      = 4, /// 4: To delete a character you must withdraw from the guild.
	CHAR_DEL_RESULT_PARTY_ERR      = 5, /// 5: To delete a character you must withdraw from the party.
};

#endif //HORIZON_CLIENT_HPP
