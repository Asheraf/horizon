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
	AStar astar({MAP_WIDTH, MAP_HEIGHT}, true, &AStar::Heuristic::manhattan, &check_collision);
	AStar::coords start = { 39, 96 };
	AStar::coords end = { 103, 126 };
	int idx = 0;

	cell[0] = (Cell **) std::malloc(sizeof(Cell *) * MAP_WIDTH * MAP_HEIGHT);

	for (int i = 0; i < MAP_WIDTH; i++)
		cell[i] = *cell + MAP_HEIGHT * i;

	for (int y = MAP_HEIGHT - 1; y >= 0; --y)
		for (int x = 0; x < MAP_WIDTH; ++x)
			cell[x][y] = new Cell(prontera[idx++]);

	auto path = astar.navigate(start, end);

	for (int y = MAP_HEIGHT - 1; y >= 0; --y) {
		for (int x = 0; x < MAP_WIDTH; ++x) {
			AStar::coords coords{x, y};
			bool found = false;

			for (auto c : *path) {
				if (coords == c) {
					if (c == start)
						printf("@");
					else if (c == end)
						printf("T");
					else
						printf("^");
					found = true;
				}
			}

			if (!found) {
				if (cell[x][y]->isWalkable())
					printf(" ");
				else
					printf(".");
			}
		}

		printf ("\n");
	}

	for (int x = 0; x < MAP_WIDTH; ++x)
		for (int y = 0; y < MAP_HEIGHT; ++y)
			std::free(cell[x][y]);

	std::free(cell);
}
