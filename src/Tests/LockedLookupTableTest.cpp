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
#define BOOST_TEST_MODULE "LockedLookupTableTest"

#include "Core/Multithreading/LockedLookupTable.hpp"
#include <boost/test/unit_test.hpp>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <atomic>
#include <thread>

#define MAX_THREADS 2
#define MAX_TABLE_SIZE 1000
#define STRING_SIZE 32
#define MAX_BUCKETS MAX_TABLE_SIZE / 10

#define SPLIT_THREADS 1

std::atomic<bool> go{false}, done_read{false}, done_write{false}, fail{false};

/**
 * @brief This test checks read/writing between multiple threads simultaneously
 * for a table of int and string keys.
 * It is normal for the string/string table to take longer than its int/int counterpart.
 * The goal is to test for simlutaneous reading/writing only, not erasing.
 * For erasing we would need to stop  read/writing or pause before reloading.
 * The table size is limited to 1000 only due to memory limits in docker containers for CI.
 */
BOOST_AUTO_TEST_CASE(LockedLookupTableTest)
{
	clock_t int_begin = clock();
	LockedLookupTable<int, int> table(MAX_BUCKETS);
	std::thread *r[MAX_THREADS], *w[MAX_THREADS];

#if SPLIT_THREADS
	printf("Dividing work between %d reader + %d writer threads: %d per thread.\n", MAX_THREADS, MAX_THREADS, (MAX_TABLE_SIZE/MAX_THREADS));
#endif

	// Populate for reading
	for (int j = 0; j < MAX_TABLE_SIZE; j++)
		table.insert(j, j);

	// Readers
	for (int i = 0; i < MAX_THREADS; i++) {
		r[i] = new std::thread([&table, i] () {
#if SPLIT_THREADS
			int start = MAX_TABLE_SIZE / MAX_THREADS * i;
			int end = start + MAX_TABLE_SIZE / MAX_THREADS;
#else
			int start = 0;
			int end = MAX_TABLE_SIZE;
#endif
			while (!go);

			clock_t t_begin = clock();

			for (int j = start; j < end; j++) {
				int val = table.at(j);
				if (j != val) {
					char output[256];
					sprintf(output, "INT/INT not equal: %d != %d\n", j, val);
					done_read.exchange(true);
					fail.exchange(true);
					return;
				}
			}

			done_read.exchange(true);
			printf("INT/INT Thread #%d - Read Time %.5fs\n", i, double(clock() - t_begin) / CLOCKS_PER_SEC);
		});
	}

	// Writers
	for (int i = 0; i < MAX_THREADS; i++) {
		w[i] = new std::thread([&table, i] () {
#if SPLIT_THREADS
			int start = MAX_TABLE_SIZE / MAX_THREADS * i;
			int end = start + MAX_TABLE_SIZE / MAX_THREADS;
#else
			int start = 0;
			int end = MAX_TABLE_SIZE;
#endif
			while (!go);

			clock_t t_begin = clock();

			for (int j = start; j < end; j++)
				table.insert(j, j);

			done_write.exchange(true);
			printf("INT/INT Thread #%d - Write Time %.5fs\n", i, double(clock() - t_begin) / CLOCKS_PER_SEC);
		});
	}

	go.exchange(true);

	while (table.size() < MAX_TABLE_SIZE && !done_read && !done_write);

	if (fail)
		BOOST_FAIL("Failed read.");

	printf("INT/INT Read/Write Test Finished in %0.5fs\n", double(clock() - int_begin) / CLOCKS_PER_SEC);

	int_begin = clock();

	// Map Iteration
	std::map<int, int> map = table.get_map();
	int i = 0;
	for (auto c : map) {
		BOOST_CHECK_EQUAL(i, c.second);
		i++;
	}

	printf("INT/INT Map Iteration Test Finished in %0.5fs\n", double(clock() - int_begin) / CLOCKS_PER_SEC);

	// Final Integrity Check
	for (int j = 0; j < MAX_TABLE_SIZE; j++)
		BOOST_CHECK_EQUAL(j, table.at(j));

	printf("INT/INT Finished in %0.5fs\n", double(clock() - int_begin) / CLOCKS_PER_SEC);

	for (int i = 0; i < MAX_THREADS; i++) {
		if (r[i]->joinable()) r[i]->join();
		if (w[i]->joinable()) w[i]->join();
		delete r[i];
		delete w[i];
	}

	done_read.exchange(false);
	done_write.exchange(false);
	go.exchange(false);

	// Erase table contents.
	for (int i = 0; i < MAX_THREADS; i++) {
		w[i] = new std::thread([&table, i] () {
#if SPLIT_THREADS
			int start = MAX_TABLE_SIZE / MAX_THREADS * i;
			int end = start + MAX_TABLE_SIZE / MAX_THREADS;
#else
			int start = 0;
			int end = MAX_TABLE_SIZE;
#endif
			while (!go);

			clock_t t_begin = clock();

			for (int j = start; j < end; j++)
				table.erase(j);

			printf("INT/INT Thread #%d - Erase Time %.5fs\n", i, double(clock() - t_begin) / CLOCKS_PER_SEC);
		});
	}

	go.exchange(true);

	while (table.size() > 0);

	printf("INT/INT Collisions: %d\n", table.max_collisions());

	for (int i = 0; i < MAX_THREADS; i++) {
		if (w[i]->joinable()) w[i]->join();
		delete w[i];
	}

	done_read.exchange(false);
	done_write.exchange(false);
	go.exchange(false);

	/*==================================*
	 * String Key / Value Test
	 *==================================*/
	clock_t str_begin = clock();
	std::string chars("abcdefghijklmnopqrstuvwxyz"
					  "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
					  "1234567890"
					  "!@#$%^&*()"
					  "`~-_=+[{]}\\|;:'\",<.>/? ");
	LockedLookupTable<std::string, std::string> str_table(MAX_BUCKETS);
	std::vector<std::string> keylist, vallist;

	// Populate
	for (int j = 0; j < MAX_TABLE_SIZE; j++) {
		char key[STRING_SIZE + 1]{0}, val[STRING_SIZE + 1]{0};
		for (int i = 0; i < STRING_SIZE; ++i) {
			key[i] = chars[rand() % (chars.size() - 1)];
			val[i] = chars[rand() % (chars.size() - 1)];
		}

		keylist.push_back(key);
		vallist.push_back(val);
		str_table.insert(key, val);
	}

	// Readers
	for (int i = 0; i < MAX_THREADS; i++) {
		r[i] = new std::thread([&str_table, keylist, vallist, i] () {
#if SPLIT_THREADS
			int start = MAX_TABLE_SIZE / MAX_THREADS * i;
			int end = start + MAX_TABLE_SIZE / MAX_THREADS;
#else
			int start = 0;
			int end = MAX_TABLE_SIZE;
#endif
			while (!go);

			clock_t t_begin = clock();

			for (int j = start; j < end; j++) {
				std::string val = str_table.at(keylist.at(j));
				if (val.compare(vallist.at(j)) != 0) {
					printf("STR/STR not equal: %s != %s\n", vallist.at(j).c_str(), val.c_str());
					done_read.exchange(true);
					fail.exchange(true);
					return;
				}
			}

			done_read.exchange(true);
			printf("STR/STR Thread #%d - Read Time %.5fs\n", i, double(clock() - t_begin) / CLOCKS_PER_SEC);
		});
	}

	// Writers
	for (int i = 0; i < MAX_THREADS; i++) {
		w[i] = new std::thread([&str_table, keylist, vallist, i] () {
#if SPLIT_THREADS
			int start = MAX_TABLE_SIZE / MAX_THREADS * i;
			int end = start + MAX_TABLE_SIZE / MAX_THREADS;
#else
			int start = 0;
			int end = MAX_TABLE_SIZE;
#endif
			while (!go);
			clock_t t_begin = clock();

			for (int j = start; j < end;  j++)
				str_table.insert(keylist.at(j), vallist.at(j));

			done_write.exchange(true);
			printf("STR/STR Thread #%d - Write Time %.5fs\n", i, double(clock() - t_begin) / CLOCKS_PER_SEC);
		});
	}

	go.exchange(true);

	while (!done_read && !done_write);

	if (fail)
		BOOST_FAIL("Failed read.");

	for (int i = 0; i < MAX_THREADS; i++) {
		if (r[i]->joinable()) r[i]->join();
		if (w[i]->joinable()) w[i]->join();
		delete r[i];
		delete w[i];
	}

	printf("STR/STR Read/Write Test Finished in %0.6fs\n", double(clock() - str_begin) / CLOCKS_PER_SEC);

	str_begin = clock();

	// Map Iteration
	std::map<std::string, std::string> strmap = str_table.get_map();
	i = 0;
	for (auto str : keylist) {
		BOOST_CHECK_EQUAL(strmap.at(str).compare(vallist.at(i)), 0);
		i++;
	}

	printf("STR/STR Map Iteration Test Finished in %0.6fs\n", double(clock() - str_begin) / CLOCKS_PER_SEC);

	// Final Integrity Check
	i = 0;
	for (auto str : keylist) {
		BOOST_CHECK_EQUAL(vallist.at(i).compare(str_table.at(str)), 0);
		i++;
	}

	go.exchange(false);

	// Erase table contents.
	for (int i = 0; i < MAX_THREADS; i++) {
		w[i] = new std::thread([&str_table, keylist, i] () {
#if SPLIT_THREADS
			int start = MAX_TABLE_SIZE / MAX_THREADS * i;
			int end = start + MAX_TABLE_SIZE / MAX_THREADS;
#else
			int start = 0;
			int end = MAX_TABLE_SIZE;
#endif
			while (!go);

			clock_t t_begin = clock();

			for (int j = start; j < end;  j++)
				str_table.erase(keylist.at(j));
			
			printf("STR/STR Thread #%d - Erase Time %.5fs\n", i, double(clock() - t_begin) / CLOCKS_PER_SEC);
		});
	}

	go.exchange(true);

	while (str_table.size() > 0);

	printf("STR/STR Collisions: %d\n", str_table.max_collisions());

	for (int i = 0; i < MAX_THREADS; i++) {
		if (w[i]->joinable()) w[i]->join();
		delete w[i];
	}
}
