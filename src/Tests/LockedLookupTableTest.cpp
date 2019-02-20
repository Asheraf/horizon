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
 * Under a proprietary license this file is not for use
 * or viewing without permission.
 **************************************************/

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "LockedLookupTableTest"

#include "Core/Multithreading/LockedLookupTable.hpp"
#include <boost/test/unit_test.hpp>
#include <cstring>
#include <cstdlib>
#include <cstdio>

#define MAX_THREADS 2
#define MAX_TABLE_SIZE 10000000
#define STRING_SIZE 32
#define MAX_BUCKETS MAX_TABLE_SIZE / 10

#define SPLIT_THREADS 1

BOOST_AUTO_TEST_CASE(LockedLookupTableTest)
{
	clock_t int_begin = clock();
	LockedLookupTable<int, int> table(MAX_BUCKETS);
	std::atomic<bool> go{false};
	std::thread *r[MAX_THREADS], *w[MAX_THREADS];

#if SPLIT_THREADS
	printf("Dividing work between %d reader + %d writer threads: %d per thread.\n", MAX_THREADS, MAX_THREADS, (MAX_TABLE_SIZE/MAX_THREADS));
#endif

	// Populate
	for (int j = 0; j < MAX_TABLE_SIZE; j++)
		table.insert(j, j);

	// Readers
	for (int i = 0; i < MAX_THREADS; i++) {
		r[i] = new std::thread([&go, &table, i] () {
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
				BOOST_CHECK_EQUAL(j, val);
				if (j != val) {
					char output[256];
					sprintf(output, "INT/INT not equal: %d != %d\n", j, val);
					BOOST_FAIL(output);
				}
			}
			printf("INT/INT Thread #%d - Read Time %.5fs\n", i, double(clock() - t_begin) / CLOCKS_PER_SEC);
		});
	}

	// Writers
	for (int i = 0; i < MAX_THREADS; i++) {
		w[i] = new std::thread([&go, &table, i] () {
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

			printf("INT/INT Thread #%d - Write Time %.5fs\n", i, double(clock() - t_begin) / CLOCKS_PER_SEC);
		});
	}

	go.exchange(true);

	for (int i = 0; i < MAX_THREADS; i++) {
		r[i]->join();
		w[i]->join();
		delete r[i];
		delete w[i];
	}

	std::cout << "INT/INT Read/Write Test Finished in " << double(clock() - int_begin) / CLOCKS_PER_SEC << "s" << std::endl;

	int_begin = clock();

	// Map Iteration
	int i = 0;
	for (auto c : table.get_map()) {
		BOOST_CHECK_EQUAL(i, c.second);
		i++;
	}
	std::cout << "INT/INT Map Iteration Test Finished in " << double(clock() - int_begin) / CLOCKS_PER_SEC << "s" << std::endl;

	// Final Integrity Check
	for (int j = 0; j < MAX_TABLE_SIZE; j++)
		BOOST_CHECK_EQUAL(j, table.at(j));

	std::cout << "INT/INT Finished in " << double(clock() - int_begin) / CLOCKS_PER_SEC << "s" << std::endl;
	std::cout << "INT/INT Collisions: " << table.max_collisions() << std::endl;

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

	go.exchange(false);

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
		r[i] = new std::thread([&go, &str_table, &keylist, &vallist, i] () {
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
				}
			}
			printf("STR/STR Thread #%d - Read Time %.5fs\n", i, double(clock() - t_begin) / CLOCKS_PER_SEC);
		});
	}

	// Writers
	for (int i = 0; i < MAX_THREADS; i++) {
		w[i] = new std::thread([&go, &str_table, &keylist, &vallist, i] () {
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

			printf("STR/STR Thread #%d - Write Time %.5fs\n", i, double(clock() - t_begin) / CLOCKS_PER_SEC);
		});
	}

	go.exchange(true);

	for (int i = 0; i < MAX_THREADS; i++) {
		r[i]->join();
		w[i]->join();
		delete r[i];
		delete w[i];
	}

	std::cout << "STR/STR Read/Write Test Finished in " << double(clock() - str_begin) / CLOCKS_PER_SEC << "s" << std::endl;

	str_begin = clock();

	// Map Iteration
	std::map<std::string, std::string> strmap = str_table.get_map();
	i = 0;
	for (auto str : keylist) {
		BOOST_CHECK_EQUAL(strmap.at(str).compare(vallist.at(i)), 0);
		i++;
	}

	std::cout << "STR/STR Map Iteration Test Finished in " << double(clock() - str_begin) / CLOCKS_PER_SEC << "s" << std::endl;;

	// Final Integrity Check
	i = 0;
	for (auto str : keylist) {
		BOOST_CHECK_EQUAL(vallist.at(i).compare(str_table.at(str)), 0);
		i++;
	}

	std::cout << "STR/STR Collisions: " << str_table.max_collisions() << std::endl;
}
