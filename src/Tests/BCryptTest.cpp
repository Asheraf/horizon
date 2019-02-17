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
 * Base Author - Sagun Khosla <sagunxp@gmail.com>
 *
 * Under a proprietary license this file is not for use
 * or viewing without permission.
 **************************************************/

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "BCryptTest"

#include "Libraries/BCrypt/BCrypt.hpp"
#include <boost/test/unit_test.hpp>
#include <cstring>


BOOST_AUTO_TEST_CASE(BCryptTest)
{
	BCrypt bcrypt;
	std::string pass = "hi,mom";
	std::string hash;

	BOOST_CHECK(bcrypt.validate_password(pass, "$2a$10$VEVmGHy4F4XQMJ3eOZJAUeb.MedU0W10pTPCuf53eHdKJPiSE8sMK"));
	hash = bcrypt.generateHash(pass);
	BOOST_CHECK(bcrypt.validate_password(pass, hash));
}
