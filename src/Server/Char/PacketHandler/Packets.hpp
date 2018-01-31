//
// Created by SagunKho on 31/01/2018.
//

#ifndef HORIZON_PACKETS_HPP
#define HORIZON_PACKETS_HPP

#include "Server/Common/Packet.hpp"
#include "Server/Common/Horizon.hpp"

namespace Horizon
{
namespace Char
{
enum packets
{
	CHAR_CONNECT            = 0x65,
	CHAR_SELECT             = 0x66,
	CHAR_CREATE             = 0x67,
	CHAR_CONNECT_ERROR      = 0x6c,
	CHAR_CREATE_2015        = 0xa39,
	CHAR_CREATE_2012        = 0x970,
	CHAR_RENAME_1           = 0x8fc,
	CHAR_RENAME_2           = 0x28d,
	CHAR_RENAME_CONFIRM     = 0x28f,
	CHAR_RENAME_ACK         = 0x290,
	CHAR_DELETE             = 0x68,
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
	CHAR_PINCODE_SENDSTATE  = 0x8b9,
	CHAR_KEEP_ALIVE         = 0x187,
};
}
}

struct PACKET_CHAR_CONNECT : public Packet
{
	PACKET_CHAR_CONNECT()  : Packet(Horizon::Char::packets::CHAR_CONNECT) {}
	// 0065 <account id>.L <login id1>.L <login id2>.L <???>.W <sex>.B
	uint32_t account_id;
	uint32_t auth_code;
	uint32_t account_level;
	uint16_t unknown;
	uint8_t gender;
};

struct PACKET_CHAR_SELECT : public Packet
{
	PACKET_CHAR_SELECT() : Packet(Horizon::Char::packets::CHAR_SELECT) {}
	uint8_t slot;
};

struct PACKET_CHAR_CREATE : public Packet
{
	PACKET_CHAR_CREATE() : Packet(Horizon::Char::packets::CHAR_CREATE) {}
	//S 0067 <name>.24B <str>.B <agi>.B <vit>.B <int>.B <dex>.B <luk>.B <slot>.B <hair color>.W <hair style>.W
	char name[CHAR_NAME_LENGTH];
	uint8_t str;
	uint8_t agi;
	uint8_t vit;
	uint8_t int;
	uint8_t dex;
	uint8_t luk;
	uint8_t slot;
	uint16_t hair_color;
	uint16_t hair_style;
};

enum character_connect_errors
{
	CHAR_CONN_REJECTED_FROM_SERVER = 0, // 0 = Rejected from server.
};

struct PACKET_CHAR_CONNECT_ERROR : public Packet
{
	PACKET_CHAR_CONNECT_ERROR() : Packet(Horizon::Char::packets::CHAR_CONNECT_ERROR) {}
	character_connect_errors error;
};

struct PACKET_CHAR_CREATE_2015 : public Packet
{
	PACKET_CHAR_CREATE_2015() : Packet(Horizon::Char::packets::CHAR_CREATE_2015) {}
	// S 0a39 <name>.24B <slot>.B <hair color>.W <hair style>.W <starting job class ID>.W <Unknown>.(W or 2 B's)??? <sex>.B
	char name[CHAR_NAME_LENGTH];
	uint8_t slot;
	uint16_t hair_color;
	uint16_t hair_style;
	uint16_t job_id;
	uint16_t unknown;
	uint8_t gender;
};

struct PACKET_CHAR_CREATE_2012 : public Packet
{
	PACKET_CHAR_CREATE_2012() : Packet(Horizon::Char::packets::CHAR_CREATE_2012) {}
	// S 0970 <name>.24B <slot>.B <hair color>.W <hair style>.W
	char name[CHAR_NAME_LENGTH];
	uint8_t slot;
	uint16_t hair_color;
	uint16_t hair_style;
};

struct PACKET_CHAR_DELETE : public Packet
{
	PACKET_CHAR_DELETE() : Packet(Horizon::Char::packets::CHAR_DELETE) {}
	uint32_t character_id;
	char email[CLIENT_EMAIL_LENGTH];
};

struct PACKET_CHAR_DELETE_2 : public Packet
{
	PACKET_CHAR_DELETE_2() : Packet(Horizon::Char::packets::CHAR_DELETE_2) {}
	uint32_t character_id;
	char email[CLIENT_EMAIL_LENGTH];
};

struct PACKET_CHAR_DELETE_START : public Packet
{
	PACKET_CHAR_DELETE_START() : Packet(Horizon::Char::packets::CHAR_DELETE_START) {}
	uint32_t character_id;
};

enum character_delete_result
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
	uint32_t character_id;
	character_delete_result result;
	uint32_t deletion_date;
};

struct PACKET_CHAR_DELETE_ACCEPT : public Packet
{
	PACKET_CHAR_DELETE_ACCEPT() : Packet(Horizon::Char::packets::CHAR_DELETE_ACCEPT) {}
	uint32_t character_id;
	char birthdate[6];
};

enum character_delete_accept_result
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
	uint32_t character_id;
	character_delete_accept_result result;
};

struct PACKET_CHAR_DELETE_CANCEL : public Packet
{
	PACKET_CHAR_DELETE_CANCEL() : Packet(Horizon::Char::packets::CHAR_DELETE_CANCEL) {}
	uint32_t character_id;
};

struct PACKET_CHAR_DELETE_CANCEL_ACK : public Packet
{
	PACKET_CHAR_DELETE_CANCEL_ACK() : Packet(Horizon::Char::packets::CHAR_DELETE_CANCEL_ACK) {}
	uint32_t character_id;
	character_delete_result result; // either 1 or 2.
};

struct PACKET_CHAR_KEEP_ALIVE : public Packet
{
	PACKET_CHAR_KEEP_ALIVE() : Packet(Horizon::Char::packets::CHAR_KEEP_ALIVE) {}
	uint32_t account_id;
};

struct PACKET_CHAR_RENAME_1 : public Packet
{
	PACKET_CHAR_RENAME_1() : Packet(Horizon::Char::packets::CHAR_RENAME_1) {}
	uint32_t character_id;
	char new_name[CHAR_NAME_LENGTH];
};

struct PACKET_CHAR_RENAME_2 : public Packet
{
	PACKET_CHAR_RENAME_2() : Packet(Horizon::Char::packets::CHAR_RENAME_2) {}
	uint32_t account_id;
	uint32_t character_id;
	char new_name[CHAR_NAME_LENGTH];
};

struct PACKET_CHAR_RENAME_CONFIRM : public Packet
{
	PACKET_CHAR_RENAME_CONFIRM() : Packet(Horizon::Char::packets::CHAR_RENAME_CONFIRM) {}
	uint32_t character_id;
};

struct PACKET_CHAR_RENAME_ACK : public Packet
{
	PACKET_CHAR_RENAME_ACK() : Packet(Horizon::Char::packets::CHAR_RENAME_ACK) {}
	uint16_t character_slot;
};

#endif //HORIZON_PACKETS_HPP
