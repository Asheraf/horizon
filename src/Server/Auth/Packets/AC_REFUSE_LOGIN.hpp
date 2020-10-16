/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 * Copyright (c) 2020- Horizon Dev Team.
 *
 * Base Author - Sagun Khosla. (sagunxp@gmail.com)
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

#ifndef HORIZON_AC_REFUSE_LOGIN_HPP
#define HORIZON_AC_REFUSE_LOGIN_HPP

#include "Server/Common/Configuration/Horizon.hpp"
#include "Server/Common/Base/NetworkPacket.hpp"

namespace Horizon
{
namespace Auth
{

enum class login_error_codes
{
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

class AuthSession;
enum {
	ID_AC_REFUSE_LOGIN = 0x006a
};
/**
 * @brief Main object for the aegis packet: AC_REFUSE_LOGIN
 * Size : 23 @ 0
 *
 */ 
class AC_REFUSE_LOGIN : public Base::NetworkPacket<AuthSession>
{
public:
	AC_REFUSE_LOGIN(std::shared_ptr<AuthSession> s);
	virtual ~AC_REFUSE_LOGIN();

	void deliver(login_error_codes error_code, char *block_date, std::size_t bd_size);

	ByteBuffer &serialize();
	virtual void handle(ByteBuffer &&buf) override;
	void deserialize(ByteBuffer &buf);

protected:
	/* Structure Goes Here */
	uint32_t _error_code{0};      ///< Error code
	char _block_date[20]{0};      ///< Ban expiration date
};
}
}

#endif /* HORIZON_AC_REFUSE_LOGIN_HPP */
