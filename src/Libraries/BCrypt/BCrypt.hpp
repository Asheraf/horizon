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
#ifndef HORIZON_BCRYPT_HPP
#define HORIZON_BCRYPT_HPP

#include "bcrypt.h"
#include <string>

class BCrypt {
public:
	BCrypt() {}
	~BCrypt() {}

	static std::string generateHash(const std::string & password, int workload = 12);
	static bool validatePassword(const std::string & password, const std::string & hash);
};

#endif //HORIZON_BCRYPT_HPP
