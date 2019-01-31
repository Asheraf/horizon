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
 * Base Author - Sagun Khosla <sagunxp@gmail.com>
 *
 * Under a proprietary license this file is not for use
 * or viewing without permission.
 **************************************************/

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "Sol2Test"

#include <boost/test/unit_test.hpp>

#include <sol.hpp>
#include <cstring>
#include <fstream>

struct something {
	int arr[4];

	void increment_0() { arr[0]++; }
	something() : arr{ 5, 6, 7, 8 } {}
};


BOOST_AUTO_TEST_CASE(Sol2Test)
{
	std::cout << "=== c arrays (works with Visual C++ too) ===" << std::endl;

	sol::state lua;
	lua.open_libraries(sol::lib::base);

	lua.new_usertype<something>("something",
								"arr", sol::property([](something& s) {
										return std::ref(s.arr);
									}),
								"increment_0", &something::increment_0
								);
	lua.set_function("something_increment_0", &something::increment_0);

	lua.script(R"(s = something.new()
			   print(s.arr[3])
			   s.arr[3] = 40
			   print(s.arr[3])
			   -- functions
			   something_increment_0(s)
			   s:increment_0()
			   print(s.arr[1])
			   -- coroutines
			   c = coroutine.create(function() something_increment_0(s) end)
			   coroutine.resume(c)
			   )");

	something& s = lua["s"];
	BOOST_CHECK_EQUAL(s.arr[0], 8);
	BOOST_CHECK_EQUAL(s.arr[1], 6);
	BOOST_CHECK_EQUAL(s.arr[2], 40);
	BOOST_CHECK_EQUAL(s.arr[3], 8);

	std::string string_array[] = {
		"first string",
		"second string",
		"third string",
	};
	lua["str_arr"] = std::ref(string_array);
	// or:
	// lua["str_array"] = &string_array;
	sol::load_result script = lua.load(R"(
			   print(str_arr[3])
			   str_arr[3] = str_arr[3] .. ': modified'
			   print(str_arr[3])
			   print(TEST_VAR)
			   print(TEST_VAR2["ABCDEF"])
									   print(TEST_VAR2["HIJKL"])
			   )");

	sol::environment env(lua, sol::create, lua.globals());
	env["TEST_VAR"] = 24;
	env["TEST_VAR2"] = lua.create_table();
	env["TEST_VAR2"]["ABCDEF"] = "HELLO";
	env["TEST_VAR2"]["HIJKL"] = "WORLD";

	sol::function f = script;
	env.set_on(f);
	f();

	BOOST_CHECK_EQUAL(string_array[2], "third string: modified");

	lua.script("c = coroutine.create(function() print('hi') end) print(c) coroutine.resume(c)");
}
