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
#define BOOST_TEST_MODULE "TaskSchedulingTest"

#include "Core/Multithreading/TaskScheduler/TaskScheduler.hpp"

#include <boost/test/unit_test.hpp>
#include <cstring>
#include <thread>


#define MAX_COUNT 3
#define INTERVAL 5

BOOST_AUTO_TEST_CASE(TaskSchedulingTest)
{
	TaskScheduler task_scheduler;
	int count = 0;

	printf("Executing tasks every %d seconds...\n", INTERVAL);

	task_scheduler.Schedule(Seconds(INTERVAL), [this, &count] (TaskContext context) {
		printf("task executed %d times\n", ++count);
		if (count < MAX_COUNT)
			context.Repeat(Seconds(INTERVAL));
	});

	while (true && count < MAX_COUNT) {
		uint32_t diff = 500;
		task_scheduler.Update(diff);
		std::this_thread::sleep_for(std::chrono::milliseconds(diff));
	}
}
