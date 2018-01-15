//
// Created by SagunKho on 26/06/2017.
//

#ifndef HORIZON_AUTHPACKETS_H
#define HORIZON_AUTHPACKETS_H

#include "../Packet.hpp"

/**
 * Client-Server Packets
 */
#pragma
struct PACKET_CA_LOGIN : public Packet
{
	PACKET_CA_LOGIN() : Packet(CA_LOGIN) { }

	uint32_t version;     ///< Client Version Information
	char username[24];    ///< Username
	char password[24];    ///< Password
	uint8_t client_type;  ///< Client Type
} __attribute__((packed));

/**
 * Server-Client Packets
 */
class PACKET_AC_REFUSE_LOGIN : public Packet
{
public:
	PACKET_AC_REFUSE_LOGIN() : Packet(AC_REFUSE_LOGIN) { };

	uint8_t error_code;    ///< Error code
	char block_date[20];   ///< Ban expiration date

} __attribute__((packed));

struct PACKET_AC_REFUSE_LOGIN_R2 : public Packet
{
	PACKET_AC_REFUSE_LOGIN_R2() : Packet(AC_REFUSE_LOGIN_R2)
	{
		memset(block_date, 0x0, sizeof(block_date));
	};

	uint32_t error_code;    ///< Error code
	char block_date[20];    ///< Ban expiration date

	void operator>>(PacketBuffer &right)
	{
		right << op_code;
		right << error_code;
		right.append(block_date, sizeof(block_date));
	}

} __attribute__((packed));

#endif //HORIZON_AUTHPACKETS_H
