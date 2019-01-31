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

#ifndef HORIZON_AUTH_PACKETS_HPP
#define HORIZON_AUTH_PACKETS_HPP

#include "Server/Common/Horizon.hpp"

namespace Horizon
{
namespace Auth
{
enum packets {
	/**
	 * Receivable Packets.
	 */
	CA_LOGIN                = 0x0064,
	CA_REQ_HASH             = 0x01db,
	CA_LOGIN2               = 0x01dd,
	CA_LOGIN3               = 0x01fa,
	CA_CONNECT_INFO_CHANGED = 0x0200,
	CA_EXE_HASHCHECK        = 0x0204,
	CA_LOGIN_PCBANG         = 0x0277,
	CA_LOGIN4               = 0x027c,
	CA_LOGIN_HAN            = 0x02b0,
	CA_SSO_LOGIN_REQ        = 0x0825,
	//CA_SSO_LOGIN_REQa       = 0x825a, /* unused */
	CA_LOGIN_OTP            = 0x0acf,
	CA_MIN                  = CA_LOGIN,
	CA_MAX                  = CA_LOGIN_OTP,
	/**
	 * Response Packets
	 */
	AC_ACCEPT_LOGIN         = 0x0069,
	AC_REFUSE_LOGIN         = 0x006a,
	SC_NOTIFY_BAN           = 0x0081,
	AC_ACK_HASH             = 0x01dc,
	AC_REFUSE_LOGIN_R2      = 0x083e,
	MAX_AUTH_PACKETS,
};

enum class login_error_codes {
	ERR_NONE                            = -1,  // All ok!
	ERR_UNREGISTERED_ID                 =  0,  // Unregistered ID
	ERR_INCORRECT_PASSWORD              =  1,  // Incorrect Password
	ERR_EXPIRED_ID                      =  2,  // This ID is expired
	ERR_REJECTED_FROM_SERVER            =  3,  // Rejected from Server
	ERR_GM_BLOCK                        =  4,  // You have been blocked by the GM Team
	ERR_INCORRECT_CLIENT_VERSION        =  5,  // Your Game's EXE file is not the latest version
	ERR_BAN_TIMESTAMP                   =  6,  // Your are Prohibited to log in until %s
	ERR_SERVER_OVERPOPULATED            =  7,  // Server is jammed due to over populated
	ERR_COMPANY_LIMIT                   =  8,  // No more accounts may be connected from this company
	ERR_MSI_REFUSE_BAN_BY_DBA           =  9,  // MSI_REFUSE_BAN_BY_DBA
	ERR_MSI_REFUSE_EMAIL_NOT_CONFIRMED  = 10,  // MSI_REFUSE_EMAIL_NOT_CONFIRMED
	ERR_MSI_REFUSE_BAN_BY_GM            = 11,  // MSI_REFUSE_BAN_BY_GM
	ERR_MSI_REFUSE_TEMP_BAN_FOR_DBWORK  = 12,  // MSI_REFUSE_TEMP_BAN_FOR_DBWORK
	ERR_MSI_REFUSE_SELF_LOCK            = 13,  // MSI_REFUSE_SELF_LOCK
	ERR_MSI_REFUSE_NOT_PERMITTED_GROUP  = 14,  // MSI_REFUSE_NOT_PERMITTED_GROUP
	ERR_MSI_REFUSE_NOT_PERMITTED_GROUP2 = 15,  // MSI_REFUSE_NOT_PERMITTED_GROUP
	ERR_DELETED_ACCOUNT                 = 99,  // This ID has been totally erased
	ERR_SESSION_CONNECTED               = 100, // Login information remains at %s
	ERR_HACKING_INVESTIGATION           = 101, // Account has been locked for a hacking investigation. Please contact the GM Team for more information
	ERR_BUG_INVESTIGATION               = 102, // This account has been temporarily prohibited from login due to a bug-related investigation
	ERR_DELETING_CHAR                   = 103, // This character is being deleted. Login is temporarily unavailable for the time being
	ERR_DELETING_SPOUSE                 = 104, // This character is being deleted. Login is temporarily unavailable for the time being
};
}
}

#pragma pack(push, 1)
/**
 * Client-Server Packets
 */
struct PACKET_CA_LOGIN : public Packet
{
	PACKET_CA_LOGIN() : Packet(Horizon::Auth::CA_LOGIN) { }

	uint32 version{};       ///< Client Version Information
	char username[24]{};    ///< Username
	char password[24]{};    ///< Password
	uint8 client_type{};    ///< Client Type
};

struct PACKET_CA_LOGIN2 : public Packet
{
	PACKET_CA_LOGIN2() : Packet(Horizon::Auth::CA_LOGIN2) { }

	uint32 version{};         ///< Client Version
	char id[24]{};            ///< Username
	uint8 password_md5[16]{}; ///< Password hash
	uint8 clienttype{};       ///< Client Type
};

struct PACKET_CA_LOGIN3 : public Packet
{
	PACKET_CA_LOGIN3() : Packet(Horizon::Auth::CA_LOGIN3) { }

	uint32 version{};         ///< Client Version
	char id[24]{};            ///< Username
	uint8 password_md5[16]{}; ///< Password hash
	uint8 clienttype{};       ///< Client Type
	uint8 clientinfo{};       ///< Index of the connection in the clientinfo file (+10 if the command-line contains "pc")
};

struct PACKET_CA_LOGIN4 : public Packet
{
	PACKET_CA_LOGIN4() : Packet(Horizon::Auth::CA_LOGIN4) { }

	uint32 version{};         ///< Client Version
	char id[24]{};            ///< Username
	uint8 password_md5[16]{}; ///< Password hash
	uint8 clienttype{};       ///< Client Type
	char mac_address[13]{};   ///< MAC Address
};

struct PACKET_CA_LOGIN_PCBANG : public Packet
{
	PACKET_CA_LOGIN_PCBANG() : Packet(Horizon::Auth::CA_LOGIN_PCBANG) { }

	uint32 version{};	      ///< Client Version
	char id[24]{};            ///< Username
	char password[24]{};      ///< Password
	uint8 clienttype{};       ///< Client Type
	char ip[16]{};            ///< IP Address
	char mac_address[13]{};   ///< MAC Address
};

struct PACKET_CA_LOGIN_HAN : public Packet
{
	PACKET_CA_LOGIN_HAN() : Packet(Horizon::Auth::CA_LOGIN_HAN) { }

	uint32 version{};         ///< Client Version
	char id[24]{};            ///< Username
	char password[24]{};      ///< Password
	uint8 clienttype{};       ///< Client Type
	char ip[16]{};            ///< IP Address
	char mac_address[13]{};   ///< MAC Address
	uint8 is_han_game_user{}; ///< 'isGravityID'
};

struct PACKET_CA_SSO_LOGIN_REQ : public Packet
{
	PACKET_CA_SSO_LOGIN_REQ() : Packet(Horizon::Auth::CA_SSO_LOGIN_REQ) { }

	int16 packet_len{};       ///< Length (variable length)
	uint32 version{};         ///< Clientver
	uint8 clienttype{};       ///< Clienttype
	char id[24]{};            ///< Username
	char password[27]{};      ///< Password
	int8 mac_address[17]{};   ///< MAC Address
	char ip[15]{};            ///< IP Address
	/*char t1[];*/            ///< SSO Login Token (variable length)
};

struct PACKET_CA_LOGIN_OTP : public Packet
{
	PACKET_CA_LOGIN_OTP() : Packet(Horizon::Auth::CA_LOGIN_OTP) { }

	char login[25]{};         ///< Username
	char password[32]{};      ///< Password encrypted by rijndael
	char flagsStr[5]{};       ///< Unknown flags. Normally string: G000
};

struct PACKET_CA_CONNECT_INFO_CHANGED : public Packet
{
	PACKET_CA_CONNECT_INFO_CHANGED() : Packet(Horizon::Auth::CA_CONNECT_INFO_CHANGED) { }

	char id[24]{};            ///< account.userid
};

struct PACKET_CA_EXE_HASHCHECK : public Packet
{
	PACKET_CA_EXE_HASHCHECK() : Packet(Horizon::Auth::CA_EXE_HASHCHECK) { }

	uint8 hash_value[16];     ///< Client MD5 hash
};

struct PACKET_CA_REQ_HASH : public Packet
{
	PACKET_CA_REQ_HASH() : Packet(Horizon::Auth::CA_REQ_HASH) { }
};

struct PACKET_SC_NOTIFY_BAN : public Packet
{
	PACKET_SC_NOTIFY_BAN() : Packet(Horizon::Auth::SC_NOTIFY_BAN) { }

	uint8 error_code;        ///< Error code
};

/**
 * AC_*
 */
struct PACKET_AC_REFUSE_LOGIN : public Packet
{
	PACKET_AC_REFUSE_LOGIN() : Packet(Horizon::Auth::AC_REFUSE_LOGIN)
	{
		memset(block_date, '\0', 20);
	}

	uint8 error_code;       ///< Error code
	char block_date[20];    ///< Ban expiration date
};

struct PACKET_AC_REFUSE_LOGIN_R2 : public Packet
{
	PACKET_AC_REFUSE_LOGIN_R2() : Packet(Horizon::Auth::AC_REFUSE_LOGIN_R2) { }

	uint32 error_code;      ///< Error code
	char block_date[20];    ///< Ban expiration date
};

struct PACKET_AC_ACCEPT_LOGIN : public Packet
{
	PACKET_AC_ACCEPT_LOGIN() : Packet(Horizon::Auth::AC_ACCEPT_LOGIN) { }

	int16 packet_len;         ///< Packet length (variable length)
	int32 auth_code;          ///< Authentication code
	uint32 aid;               ///< Account ID
	uint32 user_level;        ///< User level
	uint32 last_login_ip;     ///< Last login IP
	char last_login_time[26]; ///< Last login timestamp
	uint8 sex;                ///< Account sex
	struct character_server_list {
		uint32 ip;            ///< Server IP address
		int16 port;           ///< Server port
		char name[20];        ///< Server name
		uint16 usercount;     ///< Online users
		uint16 is_new;        ///< Server state
		uint16 type;          ///< Server type @ character_server_types
	};
};

struct PACKET_AC_ACK_HASH : public Packet
{
	PACKET_AC_ACK_HASH() : Packet(Horizon::Auth::AC_ACK_HASH) { }

	/*uint8 secret[];*/       ///< Challenge string
};

#pragma pack(pop)

#endif //HORIZON_AUTH_PACKETS_HPP
