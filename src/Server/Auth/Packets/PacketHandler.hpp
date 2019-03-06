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
 * Base Author - Sxyz (sagunxp@gmail.com)
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

#ifndef HORIZON_AUTH_PACKETHANDLER_HPP
#define HORIZON_AUTH_PACKETHANDLER_HPP

#include "Server/Common/Definitions/Horizon.hpp"
#include "Server/Common/PacketBuffer.hpp"
#include "Server/Common/Base/PacketHandler/PacketHandler.hpp"

#include <memory>
#include <unordered_map>
#include <boost/function.hpp>
#include <boost/system/error_code.hpp>

namespace Horizon
{
	namespace Models
	{
		class SessionData;
		class GameAccount;
	}
}

namespace Horizon
{
namespace Auth
{
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
class AuthSocket;
class PacketHandler : public Horizon::Base::PacketHandler<AuthSocket>
{
public:
	explicit PacketHandler(std::shared_ptr<AuthSocket> socket);
	virtual ~PacketHandler();
	/**
	 *
	 */
	bool validate_session_data(std::shared_ptr<Models::GameAccount> game_account, uint32_t client_version, uint8_t client_type);

	/**
	 * Client To Auth
	 */
	virtual bool Handle_CA_LOGIN(PacketBuffer &packet);
	virtual bool Handle_CA_REQ_HASH(PacketBuffer &packet);
	virtual bool Handle_CA_LOGIN2(PacketBuffer &packet);
	virtual bool Handle_CA_LOGIN3(PacketBuffer &packet);
	virtual bool Handle_CA_CONNECT_INFO_CHANGED(PacketBuffer &packet);
	virtual bool Handle_CA_EXE_HASHCHECK(PacketBuffer &packet);
	virtual bool Handle_CA_LOGIN_PCBANG(PacketBuffer &packet);
	virtual bool Handle_CA_LOGIN4(PacketBuffer &packet);
	virtual bool Handle_CA_LOGIN_HAN(PacketBuffer &packet);
	virtual bool Handle_CA_SSO_LOGIN_REQ(PacketBuffer &packet);
	virtual bool Handle_CA_LOGIN_OTP(PacketBuffer &packet);

	/**
	 * Auth To Client
	 */
	virtual void Send_AC_ACCEPT_LOGIN();
	virtual void Send_AC_REFUSE_LOGIN(login_error_codes error_code);
	virtual void Send_SC_NOTIFY_BAN();
	virtual void Send_AC_ACK_HASH();
	virtual void Send_AC_REFUSE_LOGIN_R2();
	virtual void Send_CA_CHARSERVERCONNECT();

	virtual bool process_login(std::string username, std::string password, uint32_t client_type, uint32_t client_version);

	virtual void initialize_handlers();
};
}
}

#endif //HORIZON_AUTH_PACKETHANDLER_HPP
