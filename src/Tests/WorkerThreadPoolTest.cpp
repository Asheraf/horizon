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
#define BOOST_TEST_MODULE "WorkerThreadPoolTest"

#include "Core/Multithreading/WorkerThreadPool.hpp"
#include <boost/test/unit_test.hpp>
#include <cstring>
#include <thread>
#include <cstdio>
#include <iostream>

int work_1(int num = 10)
{
	for (int i = 0; i < 100000000; i += num)
		;
	return num;
}

BOOST_AUTO_TEST_CASE(WorkerThreadPoolTest)
{
	WorkerThreadPool pool;

	for (int i = 0; i < 1000; i++) {
		std::future<typename std::result_of<std::function<void()>()>::type> fut = pool.submit([i]() { if (work_1(10)) std::cout << i << std::endl; });
		fut.wait();
	}
}
