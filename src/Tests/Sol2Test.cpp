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
#define BOOST_TEST_MODULE "Sol2Test"

#include <boost/test/unit_test.hpp>

#ifndef SOL_EXCEPTIONS_SAFE_PROPAGATION
#define SOL_EXCEPTIONS_SAFE_PROPAGATION
#endif
#include <sol.hpp>
#include <cstring>
#include <fstream>
#include <iostream>

BOOST_AUTO_TEST_CASE(Sol2Test)
{
	std::cout << "=== coroutine ===" << std::endl;

	sol::state lua;
	std::vector<sol::coroutine> tasks;

	lua.open_libraries(sol::lib::base, sol::lib::coroutine);

	sol::thread runner_thread = sol::thread::create(lua);

	lua.set_function("start_task",
					 [&runner_thread, &tasks](sol::function f, sol::variadic_args va) {
						 // You must ALWAYS get the current state
						 sol::state_view runner_thread_state = runner_thread.state();
						 // Put the task in our task list to keep it alive and track it
						 std::size_t task_index = tasks.size();
						 tasks.emplace_back(runner_thread_state, f);
						 sol::coroutine& f_on_runner_thread = tasks[task_index];
						 // call coroutine with arguments that came
						 // from main thread / other thread
						 // pusher for `variadic_args` and other sol types will transfer the
						 // arguments from the calling thread to
						 // the runner thread automatically for you
						 // using `lua_xmove` internally
						 int wait = f_on_runner_thread(va);
						 std::cout << "First return: " << wait << std::endl;
						 // When you call it again, you don't need new arguments
						 // (they remain the same from the first call)
						 f_on_runner_thread();
						 std::cout << "Second run complete: " << wait << std::endl;
					 });

	lua.script(
			   R"(
			   function main(x, y, z)
			   -- do something
			   coroutine.yield(20)
			   -- do something else
			   -- do ...
			   print(x, y, z)
			   end
			   function main2(x, y)
			   coroutine.yield(10)
			   print(x, y)
			   end
			   start_task(main, 10, 12, 8)
			   start_task(main2, 1, 2)
			   )"
	);

	std::cout << std::endl;
}

