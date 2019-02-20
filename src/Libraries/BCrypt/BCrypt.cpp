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
#ifndef HORIZON_BCRYPT_CPP
#define HORIZON_BCRYPT_CPP

#include "BCrypt.hpp"
#include <exception>
#include <stdexcept>
#include <string>

std::string BCrypt::generateHash(const std::string & password, int workload)
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

bool BCrypt::validate_password(const std::string & password, const std::string & hash)
{
	return (bcrypt_checkpw(password.c_str(), hash.c_str()) == 0);
}

#endif //HORIZON_BCRYPT_CPP
