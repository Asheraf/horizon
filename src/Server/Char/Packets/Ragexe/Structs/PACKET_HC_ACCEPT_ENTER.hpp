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

#ifndef HORIZON_CHAR_RAGEXE_PACKET_HC_ACCEPT_ENTER_HPP
#define HORIZON_CHAR_RAGEXE_PACKET_HC_ACCEPT_ENTER_HPP


#include "Server/Char/Packets/Ragexe/Packets.hpp"
#include "Server/Common/Horizon.hpp"
#include "Server/Common/Client.hpp"
#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
	namespace Models
	{
		namespace Character
		{
			class Character;
		}
	}

namespace Char
{
namespace Ragexe
{
struct PACKET_HC_ACCEPT_ENTER : public Packet
{
	PACKET_HC_ACCEPT_ENTER(uint16_t packet_id = HC_ACCEPT_ENTER) : Packet(packet_id) { }

	virtual PacketBuffer serialize()
	{
		PacketBuffer buf(HC_ACCEPT_ENTER);

		buf << packet_length;
		buf << max_char_slots;
		buf << permitted_slots;
		buf << total_premium_slots;
		buf.append(unknown_bytes, sizeof(unknown_bytes));
		// Append character_list_data.
		return buf;
	}

	virtual void deserialize(PacketBuffer &/*buf*/) { }

	virtual PACKET_HC_ACCEPT_ENTER & operator << (PacketBuffer &right)
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right)
	{
		return right = serialize();
	}

	virtual uint16_t get_length(uint8_t max_chars = 0) { return 27 + (147 * max_chars); }

	/* Size: -1 bytes */
	uint16_t packet_length{27};
	uint8_t max_char_slots{MAX_CHARACTER_SLOTS};
	uint8_t permitted_slots{MAX_CHARACTER_SLOTS};
	// Total premium slots out of the max_char_slots which are premium. (if not permitted will show red)
	uint8_t total_premium_slots{MAX_CHARACTER_SLOTS};
	uint8_t unknown_bytes[20]{0}; ///< 20 Unknown bytes.

	struct character_list_data {
		void create_from_model(std::shared_ptr<Models::Character::Character> c);

		virtual PacketBuffer serialize(PacketBuffer &buf);

		uint32_t character_id{0};            ///< 0
		uint64_t base_experience{0};         ///< 4
		uint32_t zeny{0};                    ///< 8
		uint64_t job_experience{0};          ///< 12
		uint32_t job_level{0};               ///< 16
		uint32_t sc_opt1{0};                 ///< 20 Probably OPT1 / 2
		uint32_t sc_opt2{0};                 ///< 24
		uint32_t body_state{0};              ///< 28
		uint32_t virtue{0};                  ///< 32
		uint32_t honor{0};                   ///< 36
		uint16_t status_points{0};           ///< 40
		uint32_t hp{0};                      ///< 42
		uint32_t maximum_hp{0};              ///< 46
		uint16_t sp{0};                      ///< 50
		uint16_t maximum_sp{0};              ///< 52
		uint16_t walk_speed{0};              ///< 54
		uint16_t job_class{0};               ///< 56
		uint16_t hair_view_id{0};            ///< 58
		uint16_t body_view_id{0};            ///< 60 p->body in hercules.
		uint16_t weapon_view_id{0};          ///< 62 OPTION_* in hercules.
		uint16_t base_level{0};              ///< 64
		uint16_t skill_point{0};             ///< 66
		uint16_t head_bottom_view_id{0};     ///< 68
		uint16_t shield_id{0};               ///< 70
		uint16_t head_top_view_id{0};        ///< 72
		uint16_t head_mid_view_id{0};        ///< 74
		uint16_t hair_color_id{0};           ///< 76
		uint16_t clothes_color_id{0};        ///< 78
		char name[MAX_UNIT_NAME_LENGTH]{0};  ///< 80
		uint8_t strength{0};                 ///< 104
		uint8_t agility{0};
		uint8_t vitality{0};
		uint8_t intelligence{0};
		uint8_t dexterity{0};
		uint8_t luck{0};
		uint16_t char_slot{0};               ///< 110
		uint16_t rename_count{0};            ///< 112
		char map_name[MAP_NAME_LENGTH_EXT]{0};///< 114
		uint32_t delete_date{0};             ///< 130
		uint32_t robe_view_id{0};            ///< 134
		uint32_t change_slot_count{0};       ///< 138
		uint32_t addon_option{0};            ///< 142 1: Displays "Addon" on side-bar.
		uint8_t gender{0};                   ///< 146 0: Female, 1: Male, 99: Account-based.
	};
};
}
}
}

#endif /* HORIZON_CHAR_RAGEXE_PACKET_HC_ACCEPT_ENTER_HPP */
