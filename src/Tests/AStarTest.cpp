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
#define BOOST_TEST_MODULE "AStarTest"

#include "Server/Zone/Game/Map/Path/AStar.hpp"
#include "Server/Zone/Game/Map/Grid/Cell/Cell.hpp"

#include <boost/test/unit_test.hpp>
#include <cstring>
#include <fstream>

using namespace Horizon::Zone;
using namespace Horizon::Zone::Game;

#define MAP_WIDTH 312
#define MAP_HEIGHT 392

#include "prontera.cpp"

Cell ***cell = (Cell ***) std::malloc(sizeof(Cell *) * MAP_WIDTH);

bool check_collision(uint16_t x, uint16_t y)
{
	if (cell[x][y]->isWalkable())
		return false;

	return true;
}

BOOST_AUTO_TEST_CASE(AStarTest)
{
	Horizon::Zone::AStar::Generator astar({MAP_WIDTH, MAP_HEIGHT}, &check_collision, true, &Horizon::Zone::AStar::Heuristic::manhattan);
	Horizon::Zone::AStar::Vec2i start = { 50, 40 };
	Horizon::Zone::AStar::Vec2i end = { 250, 350 };
	int idx = 0;

	cell[0] = (Cell **) std::malloc(sizeof(Cell *) * MAP_WIDTH * MAP_HEIGHT);

	for (int i = 0; i < MAP_WIDTH; i++)
		cell[i] = *cell + MAP_HEIGHT * i;

	for (int y = MAP_HEIGHT - 1; y >= 0; --y) {
		for (int x = 0; x < MAP_WIDTH; ++x) {
			cell[x][y] = new Cell(prontera[idx++]);
		}
	}

//	auto start_time = std::chrono::high_resolution_clock::now();
//	astar.navigate(start, end);
//	auto finish_time = std::chrono::high_resolution_clock::now();
//	std::chrono::duration<double> elapsed = finish_time - start_time;
//	printf("Euclidean: %.2fs\n", elapsed.count());

	auto start_time = std::chrono::high_resolution_clock::now();
	astar.setHeuristic(&AStar::Heuristic::manhattan);
	auto path = astar.findPath(start, end);
	auto finish_time = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = finish_time - start_time;
	printf("Manhattan: %.2fs\n", elapsed.count());

//	start_time = std::chrono::high_resolution_clock::now();
//	astar.setHeuristic(&AStar::Heuristic::octagonal);
//	astar.navigate(start, end);
//	finish_time = std::chrono::high_resolution_clock::now();
//	elapsed = finish_time - start_time;
//	printf("Octogonal: %.2fs\n", elapsed.count());

	//BOOST_ASSERT(path->size() > 1);

	std::ofstream mapfile;
	mapfile.open("prontera.txt");
	for (int y = MAP_HEIGHT - 1; y >= 0; --y) {
		for (int x = 0; x < MAP_WIDTH; ++x) {
			Horizon::Zone::AStar::Vec2i coords{x, y};
			bool found = false;

			for (auto c : path) {
				if (coords == c) {
					if (c == start)
						mapfile << "@";
					else if (c == end)
						mapfile << "T";
					else
						mapfile << "^";
					found = true;
				}
			}

			if (!found) {
				if (cell[x][y]->isWalkable())
					mapfile << " ";
				else
					mapfile << "|";
			}
		}

		mapfile << "\n";
	}

	mapfile.close();

	for (int x = 0; x < MAP_WIDTH; ++x)
		for (int y = 0; y < MAP_HEIGHT; ++y)
			std::free(cell[x][y]);

	std::free(cell);
}
