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

#ifndef HORIZON_CLIENT_HPP
#define HORIZON_CLIENT_HPP

#include <stdint.h>

#define MAX_UNIT_NAME_LENGTH 24
#define MAX_PARTY_NAME_LENGTH 24
#define MAX_GUILD_NAME_LENGTH 24
#define MAX_GUILD_POSITION_NAME_LENGTH 24
#define MAX_USERNAME_LENGTH 24
#define CLIENT_BIRTHDATE_STRING_LENGTH 6
#define MAX_BIRTHDATE_STRING_LENGTH CLIENT_BIRTHDATE_STRING_LENGTH + 5 // YYYY-MM-DD
#define MAX_PINCODE_STRING_LENGTH 5
#define MAX_EMAIL_LENGTH 40
#define MAX_IP_ADDRESS_STR_LENGTH 16
#define MAX_CHAT_STR_LENGTH 255 + 1
// For Map Names, which the client considers to be 16 in length including the .gat extension.
#define MAP_NAME_LENGTH (11 + 1)
#define MAP_NAME_LENGTH_EXT (MAP_NAME_LENGTH + 4)


enum character_connect_errors : uint8_t
{
	CHAR_ERR_REJECTED_FROM_SERVER = 0, // 0 = Rejected from server.
};
enum char_create_error_type : uint8_t
{
	HC_CREATE_ERROR_ALREADY_EXISTS = 0x00,
	HC_CREATE_ERROR_DENIED         = 0xFF,
	HC_CREATE_ERROR_UNDERAGE       = 0x01,
	HC_CREATE_ERROR_SYMBOLS        = 0x02,
	HC_CREATE_ERROR_CHAR_SLOT      = 0x03
};

enum pincode_state : uint16_t
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

enum character_delete_result : uint32_t
{
	CHAR_DEL_RESULT_UNKNOWN        = 0, /// 0 (0x718): An unknown error has occurred.
	CHAR_DEL_RESULT_SUCCESS        = 1, /// 1: none/success
	CHAR_DEL_RESULT_SYSTEM_ERR     = 2, /// 2: Due to system settings can not be deleted.
	CHAR_DEL_RESULT_DATABASE_ERR   = 3, /// 3: A database error occurred.
	CHAR_DEL_RESULT_GUILD_ERR      = 4, /// 4: To delete a character you must withdraw from the guild.
	CHAR_DEL_RESULT_PARTY_ERR      = 5, /// 5: To delete a character you must withdraw from the party.
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

#endif //HORIZON_CLIENT_HPP
