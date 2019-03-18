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
#define BOOST_TEST_MODULE "ThreadSafeQueueTest"

#include "Core/Multithreading/ThreadSafeQueue.hpp"
#include <boost/test/unit_test.hpp>
#include <cstring>
#include <thread>
#include <atomic>

#define MAX_PUSHES 1000000

BOOST_AUTO_TEST_CASE(ThreadSafeQueueTest)
{
	ThreadSafeQueue<int> queue;
	std::thread *t[4];
	std::atomic<bool> go;

	for (int i = 0; i < MAX_PUSHES; i++)
		queue.push(std::move(i));

	BOOST_CHECK_EQUAL(queue.size(), MAX_PUSHES);

	t[0] = new std::thread([&queue, &go]() {
		while (!go);
		for (int i = 0; i < MAX_PUSHES; i++)
			queue.push(std::move(i));
	});

	t[1] = new std::thread([&queue, &go]() {
		while (!go);
		for (int i = 0; i < MAX_PUSHES; i++)
			queue.push(std::move(i));
	});

	t[2] = new std::thread([&queue, &go]() {
		while (!go);
		for (int i = 0; i < MAX_PUSHES; i++)
			queue.try_pop();
	});

	t[3] = new std::thread([&queue, &go]() {
		while (!go);
		for (int i = 0; i < MAX_PUSHES; i++)
			queue.try_pop();
	});

	go.exchange(true);

	t[0]->join();
	t[1]->join();
	t[2]->join();
	t[3]->join();

	delete t[0];
	delete t[1];
	delete t[2];
	delete t[3];

	BOOST_CHECK_EQUAL(queue.size(), MAX_PUSHES);
}
