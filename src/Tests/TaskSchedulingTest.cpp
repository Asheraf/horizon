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
