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

#ifndef HORIZON_AUTHPACKETS_H
#define HORIZON_AUTHPACKETS_H

#include "Common/Horizon.hpp"
#include "Common/Packet.hpp"

enum auth_client_packets {
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
	CA_LOGIN_OTP            = 0x0acf,
	//PACKET_ID_CA_SSO_LOGIN_REQa       = 0x825a, /* unused */
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

enum auth_character_packets {
	CA_CHARSERVERCONNECT    = 0x2710, // Custom Packet
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

#pragma pack(push, 1)

/**
 * Client-Server Packets
 */
struct PACKET_CA_LOGIN : public Packet
{
	PACKET_CA_LOGIN() : Packet(CA_LOGIN) { }

	uint32 version;       ///< Client Version Information
	char username[24];    ///< Username
	char password[24];    ///< Password
	uint8 client_type;    ///< Client Type
};

/**
 * Packet structure for CA_LOGIN2.
 */
struct PACKET_CA_LOGIN2 : public Packet
{
	PACKET_CA_LOGIN2() : Packet(CA_LOGIN2) { }

	uint32 version;         ///< Client Version
	char id[24];            ///< Username
	uint8 password_md5[16]; ///< Password hash
	uint8 clienttype;       ///< Client Type
};

/**
 * Packet structure for CA_LOGIN3.
 */
struct PACKET_CA_LOGIN3 : public Packet
{
	PACKET_CA_LOGIN3() : Packet(CA_LOGIN3) { }

	uint32 version;         ///< Client Version
	char id[24];            ///< Username
	uint8 password_md5[16]; ///< Password hash
	uint8 clienttype;       ///< Client Type
	uint8 clientinfo;       ///< Index of the connection in the clientinfo file (+10 if the command-line contains "pc")
};

/**
 * Packet structure for CA_LOGIN4.
 */
struct PACKET_CA_LOGIN4 : public Packet
{
	PACKET_CA_LOGIN4() : Packet(CA_LOGIN4) { }

	uint32 version;         ///< Client Version
	char id[24];            ///< Username
	uint8 password_md5[16]; ///< Password hash
	uint8 clienttype;       ///< Client Type
	char mac_address[13];   ///< MAC Address
};

/**
 * Packet structure for CA_LOGIN_PCBANG.
 */
struct PACKET_CA_LOGIN_PCBANG : public Packet
{
	PACKET_CA_LOGIN_PCBANG() : Packet(CA_LOGIN_PCBANG) { }

	uint32 version;	      ///< Client Version
	char id[24];          ///< Username
	char password[24];    ///< Password
	uint8 clienttype;     ///< Client Type
	char ip[16];          ///< IP Address
	char mac_address[13]; ///< MAC Address
};

/**
 * Packet structure for CA_LOGIN_HAN.
 */
struct PACKET_CA_LOGIN_HAN : public Packet
{
	PACKET_CA_LOGIN_HAN() : Packet(CA_LOGIN_HAN) { }

	uint32 version;         ///< Client Version
	char id[24];            ///< Username
	char password[24];      ///< Password
	uint8 clienttype;       ///< Client Type
	char ip[16];            ///< IP Address
	char mac_address[13];   ///< MAC Address
	uint8 is_han_game_user; ///< 'isGravityID'
};

/**
 * Packet structure for CA_SSO_LOGIN_REQ.
 *
 * Variable-length packet.
 */
struct PACKET_CA_SSO_LOGIN_REQ : public Packet
{
	PACKET_CA_SSO_LOGIN_REQ() : Packet(CA_SSO_LOGIN_REQ) { }

	int16 packet_len;     ///< Length (variable length)
	uint32 version;       ///< Clientver
	uint8 clienttype;     ///< Clienttype
	char id[24];          ///< Username
	char password[27];    ///< Password
	int8 mac_address[17]; ///< MAC Address
	char ip[15];          ///< IP Address
	char t1[];            ///< SSO Login Token (variable length)
};

/**
 * Packet structure for CA_LOGIN_OTP.
 */
struct PACKET_CA_LOGIN_OTP : public Packet
{
	PACKET_CA_LOGIN_OTP() : Packet(CA_LOGIN_OTP) { }
#if PACKETVER >= 20171113
	uint32 devFlags;      ///< flags including dev flag
#endif
	char login[25];       ///< Username
	char password[32];    ///< Password encrypted by rijndael
	char flagsStr[5];     ///< Unknown flags. Normally string: G000
};

#if 0 // Unused
struct PACKET_CA_SSO_LOGIN_REQa {
	int16 PACKET_id;
	int16 packet_len;
	uint32 version;
	uint8 clienttype;
	char id[24];
	int8 mac_address[17];
	char ip[15];
	char t1[];
};
#endif // unused

/**
 * Packet structure for CA_CONNECT_INFO_CHANGED.
 *
 * New alive packet. Used to verify if client is always alive.
 */
struct PACKET_CA_CONNECT_INFO_CHANGED : public Packet
{
	PACKET_CA_CONNECT_INFO_CHANGED() : Packet(CA_CONNECT_INFO_CHANGED) { }

	char id[24];    ///< account.userid
};

/**
 * Packet structure for CA_EXE_HASHCHECK.
 *
 * (kRO 2004-05-31aSakexe langtype 0 and 6)
 */
struct PACKET_CA_EXE_HASHCHECK : public Packet
{
	PACKET_CA_EXE_HASHCHECK() : Packet(CA_EXE_HASHCHECK) { }

	uint8 hash_value[16]; ///< Client MD5 hash
};

/**
 * Packet structure for CA_REQ_HASH.
 */
struct PACKET_CA_REQ_HASH : public Packet
{
	PACKET_CA_REQ_HASH() : Packet(CA_REQ_HASH) { }
};

//**
// * Packet structure for CA_CHARSERVERCONNECT.
// *
// * This packet is used internally, to signal a char-server connection.
// */
//struct PACKET_CA_CHARSERVERCONNECT {
//	int16 PACKET_id;   ///< Packet ID (#PACKET_ID_CA_CHARSERVERCONNECT)
//	char userid[24];   ///< Username
//	char password[24]; ///< Password
//	int32 unknown;
//	int32 ip;          ///< Charserver IP
//	int16 port;        ///< Charserver port
//	char name[20];     ///< Charserver name
//	int16 unknown2;
//	int16 type;        ///< Charserver type
//	int16 new;         ///< Whether charserver is to be marked as new
//};

/**
 * Packet structure for SC_NOTIFY_BAN.
 */
struct PACKET_SC_NOTIFY_BAN : public Packet
{
	PACKET_SC_NOTIFY_BAN() : Packet(SC_NOTIFY_BAN) { }

	uint8 error_code; ///< Error code
};

/**
 * Packet structure for AC_REFUSE_LOGIN.
 */
struct PACKET_AC_REFUSE_LOGIN : public Packet
{
	PACKET_AC_REFUSE_LOGIN() : Packet(AC_REFUSE_LOGIN)
	{
		memset(block_date, '\0', 20);
	}

	uint8 error_code;    ///< Error code
	char block_date[20]; ///< Ban expiration date
};

/**
 * Packet structure for AC_REFUSE_LOGIN_R2.
 */
struct PACKET_AC_REFUSE_LOGIN_R2 : public Packet
{
	PACKET_AC_REFUSE_LOGIN_R2() : Packet(AC_REFUSE_LOGIN_R2) { }

	uint32 error_code;   ///< Error code
	char block_date[20]; ///< Ban expiration date
};

/**
 * Packet structure for AC_ACCEPT_LOGIN.
 *
 * Variable-length packet.
 */
struct char_server_list {
	uint32 ip;        ///< Server IP address
	int16 port;       ///< Server port
	char name[20];    ///< Server name
	uint16 usercount; ///< Online users
	uint16 state;     ///< Server state
	uint16 property;  ///< Server property
#if PACKETVER >= 20170315
	char unknown2[128];
#endif
};
struct PACKET_AC_ACCEPT_LOGIN : public Packet
{
	PACKET_AC_ACCEPT_LOGIN() : Packet(AC_ACCEPT_LOGIN) { }

	int16 packet_len;         ///< Packet length (variable length)
	int32 auth_code;          ///< Authentication code
	uint32 aid;               ///< Account ID
	uint32 user_level;        ///< User level
	uint32 last_login_ip;     ///< Last login IP
	char last_login_time[26]; ///< Last login timestamp
	uint8 sex;                ///< Account sex
#if PACKETVER >= 20170315
	char unknown1[17];
#endif
	struct char_server_list *server_list; ///< List of charservers
};

/**
 * Packet structure for AC_ACK_HASH.
 *
 * Variable-length packet
 */
struct PACKET_AC_ACK_HASH : public Packet
{
	PACKET_AC_ACK_HASH() : Packet(AC_ACK_HASH) { }

	uint8 secret[];   ///< Challenge string
};
#pragma pack(pop)

#endif //HORIZON_AUTHPACKETS_H
