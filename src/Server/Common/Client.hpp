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

#ifndef HORIZON_CLIENT_HPP
#define HORIZON_CLIENT_HPP

#ifndef MAX_CHAR_NAME_LENGTH
	#define MAX_CHAR_NAME_LENGTH 24
#endif

#ifndef MAX_USERNAME_LENGTH
	#define MAX_USERNAME_LENGTH 24
#endif

#ifndef MAX_BIRTHDATE_STRING_LENGTH
#define CLIENT_BIRTHDATE_STRING_LENGTH 6
	#define MAX_BIRTHDATE_STRING_LENGTH CLIENT_BIRTHDATE_STRING_LENGTH + 5 // YYYY-MM-DD
#endif

#ifndef MAX_PINCODE_STRING_LENGTH
	#define MAX_PINCODE_STRING_LENGTH 5
#endif

#ifndef MAX_EMAIL_LENGTH
	#define MAX_EMAIL_LENGTH 40
#endif

#ifndef MAX_IP_ADDRESS_STR_LENGTH
	#define MAX_IP_ADDRESS_STR_LENGTH 16
#endif

#ifndef MAP_NAME_LENGTH
	// For Map Names, which the client considers to be 16 in length including the .gat extension.
	#define MAP_NAME_LENGTH (11 + 1)
	#define MAP_NAME_LENGTH_EXT (MAP_NAME_LENGTH + 4)
#endif

#endif //HORIZON_CLIENT_HPP
