/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 *
 * Copyright (c) 2019 Sagun K. (sagunxp@gmail.com).
 * Copyright (c) 2019 Horizon Dev Team.
 *
 * Base Author - Sagun Khosla <sagunxp@gmail.com>
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

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "Argon2Test"

#include "Libraries/Argon2/Argon2.hpp"

#include <cstring>
#include <fstream>
#include <iostream>
#include <boost/test/unit_test.hpp>

#define HASHLEN 32
#define SALTLEN 16
#define PWD "password"

BOOST_AUTO_TEST_CASE(Argon2Test)
{
    Argon2 argon2;
    std::string hash1 = argon2.gen_hash("password", "horizon-123");
    
	std::cout << hash1 << std::endl;
	
	BOOST_TEST(argon2.verify(hash1, "password", "horizon-123") == true);
    BOOST_TEST(argon2.verify(hash1, "password", "horizon-12") == false);
    BOOST_TEST(argon2.verify(hash1, "passwo", "horizon-123") == false);
    BOOST_TEST(argon2.verify(hash1, "passwo", "horizon-13") == false);

    return;
}

