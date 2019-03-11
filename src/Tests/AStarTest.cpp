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
#define BOOST_TEST_MODULE "AStarTest"

#include "Server/Zone/Game/Map/Path/AStar.hpp"
#include "Server/Zone/Game/Map/Grid/Cell/Cell.hpp"

#include <boost/test/unit_test.hpp>
#include <cstring>
#include <fstream>

using namespace Horizon::Zone;
using namespace Horizon::Zone::Game;

#define MAP_WIDTH 268
#define MAP_HEIGHT 300

#include "prontera.cpp"

Cell cell[MAP_WIDTH][MAP_HEIGHT];

bool check_collision(uint16_t x, uint16_t y)
{
	if (cell[x][y].isWalkable())
		return false;

	return true;
}

BOOST_AUTO_TEST_CASE(AStarTest)
{

	Horizon::Zone::AStar::Generator astar({MAP_WIDTH, MAP_HEIGHT}, &check_collision, true, &Horizon::Zone::AStar::Heuristic::manhattan);
	Horizon::Zone::AStar::Vec2i start = { 204, 158 };
	Horizon::Zone::AStar::Vec2i end = { 200, 159 };
	int idx = 0;

	for (int y = MAP_HEIGHT - 1; y >= 0; --y) {
		for (int x = 0; x < MAP_WIDTH; ++x) {
			cell[x][y] = Cell(izlude[idx++]);
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
	mapfile.open("izlude.txt");
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
				if (cell[x][y].isWalkable())
					mapfile << " ";
				else
					mapfile << "|";
			}
		}

		mapfile << "\n";
	}

	mapfile.close();
}
