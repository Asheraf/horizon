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
