//
//  Packets.h
//  Horizon
//
//  Created by SagunKho on 18/06/2017.
//  Copyright © 2017 Horizon. All rights reserved.
//

#ifndef Packets_h
#define Packets_h

#include <stdint.h>

#include "Core/Networking/Buffer/ByteBuffer.hpp"

enum AuthPackets {
	CA_LOGIN                = 0x0064,
	CA_LOGIN2               = 0x01dd,
	CA_LOGIN3               = 0x01fa,
	CA_CONNECT_INFO_CHANGED = 0x0200,
	CA_EXE_HASHCHECK        = 0x0204,
	CA_LOGIN_PCBANG         = 0x0277,
	CA_LOGIN4               = 0x027c,
	CA_LOGIN_HAN            = 0x02b0,
	CA_SSO_LOGIN_REQ        = 0x0825,
	CA_REQ_HASH             = 0x01db,
	CA_CHARSERVERCONNECT    = 0x2710, // Custom Hercules Packet
	//PACKET_ID_CA_SSO_LOGIN_REQa       = 0x825a, /* unused */
	// (Auth to Client)
	AC_ACCEPT_LOGIN         = 0x0069,
	AC_REFUSE_LOGIN         = 0x006a,
	AC_NOTIFY_BAN           = 0x0081,
	AC_ACK_HASH             = 0x01dc,
	AC_REFUSE_LOGIN_R2      = 0x083e,
};

struct Packet
{
	Packet(uint16_t id) : op_code(id) { }
	uint16_t op_code;
} __attribute__((packed));

class PacketBuffer : public ByteBuffer
{
public:
	PacketBuffer() : ByteBuffer(0), op_code(0x0000)
	{
	}

	PacketBuffer(uint16_t id, MessageBuffer&& buffer)
	: ByteBuffer(std::move(buffer)), op_code(id)
	{
	}

	PacketBuffer(uint16_t id, size_t reserve = 200)
	: ByteBuffer(reserve), op_code(id)
	{
	}

	PacketBuffer(PacketBuffer&& packet) : ByteBuffer(std::move(packet)), op_code(packet.op_code)
	{
	}

	PacketBuffer(PacketBuffer const &right) : ByteBuffer(right), op_code(right.op_code)
	{
	}

	PacketBuffer &operator=(PacketBuffer const &right)
	{
		if (this != &right) {
			op_code = right.op_code;
			ByteBuffer::operator=(right);
		}

		return *this;
	}

	PacketBuffer& operator=(PacketBuffer &&right)
	{
		if (this != &right) {
			op_code = right.op_code;
			ByteBuffer::operator=(std::move(right));
		}

		return *this;
	}

	void Initialize(uint16_t id, size_t newres = 200)
	{
		clear();
		_storage.reserve(newres);
		op_code = id;
	}

	uint16_t getOpCode() { return op_code; };
	void SetOpcode(uint16_t code) { op_code = code; }

protected:
	uint16_t op_code;
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

#endif /* Packets_h */
