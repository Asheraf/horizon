//
// Created by SagunKho on 27/01/2018.
//

#ifndef HORIZON_AUTHPACKETHANDLER20171113_HPP
#define HORIZON_AUTHPACKETHANDLER20171113_HPP

#include "Server/Common/Horizon.hpp"
#include "Server/Auth/PacketHandler/AuthPacketHandler.hpp"

struct PACKET_CA_LOGIN_OTP_20171113;

class AuthPacketHandler20171113 : public AuthPacketHandler
{
public:
	explicit AuthPacketHandler20171113(std::shared_ptr<AuthSession> session);
	~AuthPacketHandler20171113() override;

	void Handle_CA_LOGIN_OTP(PacketBuffer &packet) override;
	void InitializeHandlers() override;
};

/**
 * Overloaded Packet Definitions
 */
#pragma pack(push, 1)
/**
 * Packet structure for CA_LOGIN_OTP.
 */
struct PACKET_CA_LOGIN_OTP_20171113 : public PACKET_CA_LOGIN_OTP
{
	PACKET_CA_LOGIN_OTP_20171113() : PACKET_CA_LOGIN_OTP() { }

	uint32 devFlags{};      ///< flags including dev flag
	char login[25]{};       ///< Username
	char password[32]{};    ///< Password encrypted by rijndael
	char flagsStr[5]{};     ///< Unknown flags. Normally string: G000
};

#pragma pack(pop)

#endif //HORIZON_AUTHPACKETHANDLER20171113_HPP
