/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
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
#define BOOST_TEST_MODULE "Sol2Test"

#include <boost/test/unit_test.hpp>

#include <sol.hpp>
#include <cstring>
#include <fstream>

BOOST_AUTO_TEST_CASE(Sol2Test)
{
	sol::state lua;
	lua.script(R"(
			   abc = 123;
			   function loop()
			       local counter = 0;
				   while counter < 30
				   do
					   coroutine.yield(counter);
					   counter = counter + 1;
				   end
				   return counter
			   end
			   )");

	sol::coroutine cr = lua["loop"];
	sol::object abc = lua["abc"];

	std::cout << "abc:" << abc.as<uint32_t>() << std::endl;

	for (int counter = 0; // start from 0
		 counter < 50 && cr; // we want 10 values, and we only want to run if the coroutine "cr" is valid
		 // Alternative: counter < 10 && cr.valid()
		 ++counter) {
		// Call the coroutine, does the computation and then suspends
		int value = cr();
		std::cout << value << std::endl;
	}
}

