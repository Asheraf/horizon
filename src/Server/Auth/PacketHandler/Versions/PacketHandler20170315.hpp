//
// Created by SagunKho on 27/01/2018.
//

#ifndef HORIZON_AUTH_PACKETHANDLER20170315_HPP
#define HORIZON_AUTH_PACKETHANDLER20170315_HPP

#include "Server/Auth/PacketHandler/PacketHandler.hpp"

struct PACKET_AC_ACCEPT_LOGIN_20170315;

namespace Horizon
{
namespace Auth
{
class PacketHandler20170315 : public PacketHandler
{
public:
	explicit PacketHandler20170315(std::shared_ptr<AuthSession> &session);
	~PacketHandler20170315() override;

	void Respond_AC_ACCEPT_LOGIN() override;
	void InitializeHandlers() override;
};
}
}

/**
 * Overloaded Packet Definitions
 */
#pragma pack(push, 1)
struct PACKET_AC_ACCEPT_LOGIN_20170315 : public Packet
{
	PACKET_AC_ACCEPT_LOGIN_20170315() : Packet(Horizon::Auth::CA_LOGIN) { }

	int16 packet_len{};         ///< Packet length (variable length)
	int32 auth_code{};          ///< Authentication code
	uint32 aid{};               ///< Account ID
	uint32 user_level{};        ///< User level
	uint32 last_login_ip{};     ///< Last login IP
	char last_login_time[26]{}; ///< Last login timestamp
	uint8 sex{};                ///< Account sex
	char unknown1[17]{};
	struct character_server_list {
		uint32 ip;         ///< Server IP address
		int16 port;        ///< Server port
		char name[20];     ///< Server name
		uint16 usercount;  ///< Online users
		uint16 is_new;     ///< Server state
		uint16 type;       ///< Server type @ character_server_types
		char unknown2[128];
	} server_list[];
};
#pragma pack(pop)

#endif //HORIZON_AUTH_PACKETHANDLER20170315_HPP
