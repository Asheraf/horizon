/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 * Copyright (c) 2018 Horizon Dev Team.
 *
 * Base Author - Sagun Khosla. (sagunxp@gmail.com)
 *
 * Under a proprietary license this file is not for use
 * or viewing without permission.
 **************************************************/

#ifndef HORIZON_PACKETS_HPP
#define HORIZON_PACKETS_HPP

#include "Server/Common/PacketBuffer.hpp"
#include "Server/Common/Horizon.hpp"
#include "Server/Common/Models/Characters/Character.hpp"
#include "Server/Common/Models/Characters/Status.hpp"
#include "Server/Common/Models/Characters/View.hpp"
#include "Server/Common/Models/Characters/Group.hpp"
#include "Server/Common/Models/Characters/Misc.hpp"
#include "Server/Common/Models/Characters/Position.hpp"
#include "Server/Common/Models/Characters/Access.hpp"

namespace Horizon
{
namespace Char
{
enum packets : short
{
	CHAR_CONNECT            = 0x65,
	CHAR_SELECT             = 0x66,
	CHAR_CREATE             = 0x67,
	CHAR_DELETE             = 0x68,
	CHAR_LIST_ACK           = 0x6b,
	CHAR_CONNECT_ERROR      = 0x6c,
	CHAR_CREATE_SUCCESS_ACK = 0x6d,
	CHAR_CREATE_ERROR_ACK   = 0x6e,
	CHAR_SEND_ZONE_INFO     = 0x71,
	CHAR_KEEP_ALIVE         = 0x187,
	CHAR_BAN_LIST_ACK       = 0x20d,
	CHAR_SLOT_INFO_ACK      = 0x82d,
	CHAR_CREATE_2015        = 0xa39,
	CHAR_RENAME_1           = 0x8fc,
	CHAR_RENAME_2           = 0x28d,
	CHAR_RENAME_CONFIRM     = 0x28f,
	CHAR_RENAME_ACK         = 0x290,
	CHAR_DELETE_2           = 0x1fb,
	CHAR_DELETE_START       = 0x827,
	CHAR_DELETE_START_ACK   = 0x828,
	CHAR_DELETE_ACCEPT      = 0x829,
	CHAR_DELETE_ACCEPT_ACK  = 0x82a,
	CHAR_DELETE_CANCEL      = 0x82b,
	CHAR_DELETE_CANCEL_ACK  = 0x82c,
	CHAR_PINCODE_INIT       = 0x8c5,
	CHAR_PINCODE_CHANGE     = 0x8be,
	CHAR_PINCODE_CHECK      = 0x8b8,
	CHAR_PINCODE_ACTIVATE   = 0x8ba,
	CHAR_REQUEST_CHARACTERS = 0x9a1,
	CHAR_PINCODE_STATE_ACK  = 0x8b9,
	CHAR_RESEND_CHAR_LIST   = 0x99d,
};
}
}

#pragma pack(push, 1)

/**
 * List assumes that the packetver is >= 20141022
 */
struct character_list_data
{
	character_list_data() { };

	void create(std::shared_ptr<Horizon::Models::Characters::Character> c)
	{
		std::shared_ptr<Horizon::Models::Characters::Status> status = c->getStatusData();
		std::shared_ptr<Horizon::Models::Characters::View> view = c->getViewData();
		std::shared_ptr<Horizon::Models::Characters::Misc> misc = c->getMiscData();
		std::shared_ptr<Horizon::Models::Characters::Position> position = c->getPositionData();
		std::shared_ptr<Horizon::Models::Characters::Access> access = c->getAccessData();

		character_id = c->getCharacterID();
		base_experience = status->getBaseExperience();
		zeny = status->getZeny();
		job_experience = status->getJobExperience();
		job_level = status->getJobLevel();
		body_state1 = status->getBodyState();
		virtue = status->getVirtue();
		honor = status->getHonor();
		status_points = status->getStatusPoints();
		hp = status->getHP();
		maximum_hp = status->getMaximumHP();
		sp = status->getSP();
		maximum_sp = status->getMaximumSP();
		job_class = status->getJobClass();
		walk_speed = DEFAULT_WALK_SPEED;
		hair_view_id = view->getHairStyleID();
		body_view_id = view->getBodyID();
		weapon_view_id = view->getWeaponID();
		base_level = status->getBaseLevel();
		skill_point = status->getSkillPoints();
		head_bottom_view_id = view->getHeadBottomViewID();
		shield_id = view->getShieldID();
		head_top_view_id = view->getHeadTopViewID();
		head_mid_view_id = view->getHeadMidViewID();
		hair_color_id = view->getHairColorID();
		clothes_color_id = view->getClothColorID();
		strncpy(name, c->getName().c_str(), MAX_CHAR_NAME_LENGTH);
		strength = status->getStrength();
		agility = status->getAgility();
		vitality = status->getVitality();
		intelligence = status->getIntelligence();
		dexterity = status->getDexterity();
		luck = status->getLuck();
		char_slot = c->getSlot();
		rename_count = misc->getRenameCount();
		strncpy(map_name, position->getCurrentMap().c_str(), MAP_NAME_LENGTH_EXT);
		delete_date = access->getDeleteDate();
		robe_view_id = view->getRobeViewID();
		change_slot_count = misc->getChangeSlotCount();
	}

	uint32_t character_id{};      ///< 0
	uint32_t base_experience{};   ///< 4
	uint32_t zeny{};              ///< 8
	uint32_t job_experience{};    ///< 12
	uint32_t job_level{};         ///< 16
	uint32_t opt1{};              ///< 20 Probably OPT1 / 2
	uint32_t opt2{};              ///< 24
	uint32_t body_state1{};       ///< 28
	uint32_t virtue{};            ///< 32
	uint32_t honor{};             ///< 36
	uint16_t status_points{};     ///< 40
	uint32_t hp{};                ///< 42
	uint32_t maximum_hp{};        ///< 46
	uint16_t sp{};                ///< 50
	uint16_t maximum_sp{};        ///< 52
	uint16_t walk_speed{};        ///< 54
	uint16_t job_class{};         ///< 56
	uint16_t hair_view_id{};      ///< 58
	uint16_t body_view_id{};      ///< 60 p->body in hercules.
	uint16_t weapon_view_id{};    ///< 62 OPTION_* in hercules.
	uint16_t base_level{};        ///< 64
	uint16_t skill_point{};         ///< 66
	uint16_t head_bottom_view_id{};  ///< 68
	uint16_t shield_id{};            ///< 70
	uint16_t head_top_view_id{};     ///< 72
	uint16_t head_mid_view_id{};     ///< 74
	uint16_t hair_color_id{};        ///< 76
	uint16_t clothes_color_id{};     ///< 78
	char name[MAX_CHAR_NAME_LENGTH]{};     ///< 80
	uint8_t strength{};              ///< 104
	uint8_t agility{};
	uint8_t vitality{};
	uint8_t intelligence{};
	uint8_t dexterity{};
	uint8_t luck{};
	uint16_t char_slot{};            ///< 110
	uint16_t rename_count{};         ///< 112
	char map_name[MAP_NAME_LENGTH_EXT]{};          ///< 114
	uint32_t delete_date{};          ///< 130
	uint32_t robe_view_id{};         ///< 134
	uint32_t change_slot_count{};    ///< 138
	uint32_t addon_option{};         ///< 142 1: Displays "Addon" on side-bar.
	uint8_t gender{};                ///< 146 0: Female, 1: Male, 99: Account-based.
};

struct PACKET_CHAR_CONNECT : public Packet
{
	PACKET_CHAR_CONNECT()  : Packet(Horizon::Char::packets::CHAR_CONNECT) {}
	// 0065 <account id>.L <login id1>.L <login id2>.L <???>.W <sex>.B
	uint32_t account_id{};
	uint32_t auth_code{};
	uint32_t account_level{};
	uint16_t unknown{};
	uint8_t gender{};
};

struct PACKET_CHAR_SELECT : public Packet
{
	PACKET_CHAR_SELECT() : Packet(Horizon::Char::packets::CHAR_SELECT) {}
	uint8_t slot{};
};

struct PACKET_CHAR_CREATE : public Packet
{
	PACKET_CHAR_CREATE() : Packet(Horizon::Char::packets::CHAR_CREATE) {}
	//S 0067 <name>.24B <str>.B <agi>.B <vit>.B <int>.B <dex>.B <luk>.B <slot>.B <hair color>.W <hair style>.W
	char name[MAX_CHAR_NAME_LENGTH];
	uint8_t str{};
	uint8_t agi{};
	uint8_t vit{};
	uint8_t int_{};
	uint8_t dex{};
	uint8_t luk{};
	uint8_t slot{};
	uint16_t hair_color{};
	uint16_t hair_style{};
};

struct PACKET_CHAR_CREATE_SUCCESS_ACK : public Packet
{
	PACKET_CHAR_CREATE_SUCCESS_ACK() : Packet(Horizon::Char::packets::CHAR_CREATE_SUCCESS_ACK) { }
	character_list_data data;
};

enum char_create_error_types : uint8_t
{
	CHAR_CREATE_ERROR_ALREADY_EXISTS = 0x00,
	CHAR_CREATE_ERROR_DENIED         = 0xFF,
	CHAR_CREATE_ERROR_UNDERAGE       = 0x01,
	CHAR_CREATE_ERROR_SYMBOLS        = 0x02,
	CHAR_CREATE_ERROR_CHAR_SLOT      = 0x03
};

struct PACKET_CHAR_CREATE_ERROR_ACK : public Packet
{
	PACKET_CHAR_CREATE_ERROR_ACK() : Packet(Horizon::Char::packets::CHAR_CREATE_ERROR_ACK) { }
	uint8_t error_code;
};

struct PACKET_CHAR_SEND_ZONE_INFO : public Packet
{
	PACKET_CHAR_SEND_ZONE_INFO() : Packet(Horizon::Char::packets::CHAR_SEND_ZONE_INFO) { }
	uint32_t char_id;
	char mapname[MAP_NAME_LENGTH_EXT];
	uint32_t ip_address;
	uint16_t port;
};

enum class character_connect_errors : uint8_t
{
	CHAR_ERR_REJECTED_FROM_SERVER = 0, // 0 = Rejected from server.
};

struct PACKET_CHAR_CONNECT_ERROR : public Packet
{
	PACKET_CHAR_CONNECT_ERROR() : Packet(Horizon::Char::packets::CHAR_CONNECT_ERROR) {}
	character_connect_errors error;
};

struct PACKET_CHAR_SLOT_INFO_ACK : public Packet
{
	PACKET_CHAR_SLOT_INFO_ACK() : Packet(Horizon::Char::packets::CHAR_SLOT_INFO_ACK) { }

	uint16_t packet_len{sizeof(PACKET_CHAR_SLOT_INFO_ACK)};
	uint8_t total_slots{MAX_CHARACTER_SLOTS};
	uint8_t premium_slots{MAX_CHARACTER_SLOTS};
	uint8_t unknown_byte{0};
	uint8_t char_slots_1{MAX_CHARACTER_SLOTS};
	uint8_t char_slots_2{MAX_CHARACTER_SLOTS};
	uint8_t unknown_bytes[20]{0};
};

/* Sent without PacketID to the client on char connection. */
struct PACKET_CHAR_ACCOUNT_ID
{
	uint32_t account_id;
};

struct PACKET_CHAR_LIST_ACK : public Packet
{
	PACKET_CHAR_LIST_ACK() : Packet(Horizon::Char::packets::CHAR_LIST_ACK) { }

	uint16_t packet_len{sizeof(PACKET_CHAR_LIST_ACK)};
	uint8_t max_char_slots{MAX_CHARACTER_SLOTS};
	uint8_t permitted_slots{MAX_CHARACTER_SLOTS};
	uint8_t total_premium_slots{MAX_CHARACTER_SLOTS};         ///< Total out of the max_char_slots that are premium. (if not permitted will show red)
	uint8_t unknown_bytes[20]{0}; ///< 20 Unknown bytes.
	character_list_data character_list[];
};

struct PACKET_CHAR_RESEND_CHAR_LIST : public Packet
{
	PACKET_CHAR_RESEND_CHAR_LIST() : Packet(Horizon::Char::packets::CHAR_RESEND_CHAR_LIST) { }

	uint16_t packet_len{sizeof(PACKET_CHAR_RESEND_CHAR_LIST)};
	character_list_data character_list[];
};

struct char_ban_list_data
{
	uint32_t character_id;
	char timestamp[20];
};

struct PACKET_CHAR_BAN_LIST_ACK : public Packet
{
	PACKET_CHAR_BAN_LIST_ACK() : Packet(Horizon::Char::packets::CHAR_BAN_LIST_ACK) { }

	uint16_t packet_length{sizeof(PACKET_CHAR_BAN_LIST_ACK)};
};

struct PACKET_CHAR_CREATE_2015 : public Packet
{
	PACKET_CHAR_CREATE_2015() : Packet(Horizon::Char::packets::CHAR_CREATE_2015) {}
	// S 0a39 <name>.24B <slot>.B <hair color>.W <hair style>.W <starting job class ID>.W <Unknown>.(W or 2 B's)??? <sex>.B
	char name[MAX_CHAR_NAME_LENGTH];
	uint8_t slot{};
	uint16_t hair_color{};
	uint16_t hair_style{};
	uint16_t job_id{};
	uint8_t unknown_bytes[2];
	uint8_t gender{};
};

struct PACKET_CHAR_DELETE : public Packet
{
	PACKET_CHAR_DELETE() : Packet(Horizon::Char::packets::CHAR_DELETE) {}
	uint32_t character_id{};
	char email[MAX_EMAIL_LENGTH]{};
};

struct PACKET_CHAR_DELETE_2 : public Packet
{
	PACKET_CHAR_DELETE_2() : Packet(Horizon::Char::packets::CHAR_DELETE_2) {}
	uint32_t character_id{};
	char email[MAX_EMAIL_LENGTH]{};
};

struct PACKET_CHAR_DELETE_START : public Packet
{
	PACKET_CHAR_DELETE_START() : Packet(Horizon::Char::packets::CHAR_DELETE_START) {}
	uint32_t character_id{};
};

enum character_delete_result : int
{
	CHAR_DEL_RESULT_UNKNOWN        = 0, /// 0 (0x718): An unknown error has occurred.
	CHAR_DEL_RESULT_SUCCESS        = 1, /// 1: none/success
	CHAR_DEL_RESULT_SYSTEM_ERR     = 2, /// 2: Due to system settings can not be deleted.
	CHAR_DEL_RESULT_DATABASE_ERR   = 3, /// 3: A database error occurred.
	CHAR_DEL_RESULT_GUILD_ERR      = 4, /// 4: To delete a character you must withdraw from the guild.
	CHAR_DEL_RESULT_PARTY_ERR      = 5, /// 5: To delete a character you must withdraw from the party.
};

struct PACKET_CHAR_DELETE_START_ACK : public Packet
{
	PACKET_CHAR_DELETE_START_ACK() : Packet(Horizon::Char::packets::CHAR_DELETE_START_ACK) {}
	// HC: <0828>.W <char id>.L <Msg:0-5>.L <deleteDate>.L
	uint32_t character_id{};
	character_delete_result result{};
	uint32_t deletion_date{};
};

struct PACKET_CHAR_DELETE_ACCEPT : public Packet
{
	PACKET_CHAR_DELETE_ACCEPT() : Packet(Horizon::Char::packets::CHAR_DELETE_ACCEPT) {}
	uint32_t character_id{0};
	char birthdate[CLIENT_BIRTHDATE_STRING_LENGTH]{0};
};

enum character_delete_accept_result : uint32_t
{
	CHAR_DEL_ACCEPT_RESULT_UNKNOWN        = 0, /// 0 (0x718): An unknown error has occurred.
	CHAR_DEL_ACCEPT_RESULT_SUCCESS        = 1, /// 1: none/success
	CHAR_DEL_ACCEPT_RESULT_SYSTEM_ERR     = 2, /// 2: Due to system settings can not be deleted.
	CHAR_DEL_ACCEPT_RESULT_DATABASE_ERR   = 3, /// 3: A database error occurred.
	CHAR_DEL_ACCEPT_RESULT_TIME_ERR       = 4, /// 4: Deleting is not yet possible.
	CHAR_DEL_ACCEPT_RESULT_BIRTHDAY_ERR   = 5, /// 5: Date of birth do not match.
};

struct PACKET_CHAR_DELETE_ACCEPT_ACK : public Packet
{
	PACKET_CHAR_DELETE_ACCEPT_ACK() : Packet(Horizon::Char::packets::CHAR_DELETE_ACCEPT_ACK) {}
	uint32_t character_id{0};
	character_delete_accept_result result{CHAR_DEL_ACCEPT_RESULT_SUCCESS};
};

struct PACKET_CHAR_DELETE_CANCEL : public Packet
{
	PACKET_CHAR_DELETE_CANCEL() : Packet(Horizon::Char::packets::CHAR_DELETE_CANCEL) {}
	uint32_t character_id{};
};

struct PACKET_CHAR_DELETE_CANCEL_ACK : public Packet
{
	PACKET_CHAR_DELETE_CANCEL_ACK() : Packet(Horizon::Char::packets::CHAR_DELETE_CANCEL_ACK) {}
	uint32_t character_id{0};
	uint32_t result{0}; // either 1 or 2.
};

struct PACKET_CHAR_KEEP_ALIVE : public Packet
{
	PACKET_CHAR_KEEP_ALIVE() : Packet(Horizon::Char::packets::CHAR_KEEP_ALIVE) {}
	uint32_t account_id{};
};

struct PACKET_CHAR_RENAME_1 : public Packet
{
	PACKET_CHAR_RENAME_1() : Packet(Horizon::Char::packets::CHAR_RENAME_1) {}
	uint32_t character_id{};
	char new_name[MAX_CHAR_NAME_LENGTH];
};

struct PACKET_CHAR_RENAME_2 : public Packet
{
	PACKET_CHAR_RENAME_2() : Packet(Horizon::Char::packets::CHAR_RENAME_2) {}
	uint32_t account_id{};
	uint32_t character_id{};
	char new_name[MAX_CHAR_NAME_LENGTH];
};

struct PACKET_CHAR_RENAME_CONFIRM : public Packet
{
	PACKET_CHAR_RENAME_CONFIRM() : Packet(Horizon::Char::packets::CHAR_RENAME_CONFIRM) {}
	uint32_t character_id{};
};

struct PACKET_CHAR_RENAME_ACK : public Packet
{
	PACKET_CHAR_RENAME_ACK() : Packet(Horizon::Char::packets::CHAR_RENAME_ACK) {}
	uint16_t character_slot{};
};

enum pincode_state : short
{
	PINCODE_CORRECT        = 0,
	PINCODE_REQUEST_PIN    = 1,
	PINCODE_REQUEST_NEW    = 2,
	PINCODE_REQUEST_CHANGE = 3,
	PINCODE_REQUEST_NEW_2  = 4,
	PINCODE_SHOW_MESSAGE_1 = 5,
	PINCODE_SHOW_MESSAGE_2 = 6,
	PINCODE_SHOW_BUTTON    = 7,
	PINCODE_INCORRECT      = 8
};

struct PACKET_CHAR_PINCODE_STATE_ACK : public Packet
{
	PACKET_CHAR_PINCODE_STATE_ACK() : Packet(Horizon::Char::packets::CHAR_PINCODE_STATE_ACK) {}
	uint32_t pincode_seed;
	uint32_t account_id;
	pincode_state state;
};

#pragma pack(pop)

#endif //HORIZON_PACKETS_HPP
