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
#ifndef HORIZON_BCRYPT_CPP
#define HORIZON_BCRYPT_CPP

#include "BCrypt.hpp"
#include <exception>
#include <stdexcept>
#include <string>

std::string BCrypt::generateHash(const std::string & password, int workload = 12)
{
	char salt[BCRYPT_HASHSIZE];
	char hash[BCRYPT_HASHSIZE];
	int ret;
	ret = bcrypt_gensalt(workload, salt);

	if (ret != 0)
		throw std::runtime_error{"bcrypt: can not generate salt"};

	 ret = bcrypt_hashpw(password.c_str(), salt, hash);

	 if (ret != 0)
		throw std::runtime_error{"bcrypt: can not generate hash"};

	 return hash;
}

bool BCrypt::validatePassword(const std::string & password, const std::string & hash)
{
	return (bcrypt_checkpw(password.c_str(), hash.c_str()) == 0);
}

#endif //HORIZON_BCRYPT_CPP
