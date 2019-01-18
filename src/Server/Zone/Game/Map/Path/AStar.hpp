/*
 Copyright (c) 2015, Damian Barczynski <daan.net@wp.eu>
 Following tool is licensed under the terms and conditions of the ISC license.
 For more information visit https://opensource.org/licenses/ISC.
 */

#ifndef HORIZON_ZONE_GAME_MAP_PATH_ASTAR_HPP
#define HORIZON_ZONE_GAME_MAP_PATH_ASTAR_HPP

#include <vector>
#include <functional>
#include <set>
#include <cstdint>
#include <algorithm>
#include <math.h>
#include <boost/optional.hpp>

namespace Horizon
{
namespace Zone
{
namespace AStar
{
struct Vec2i
{
	int x{0}, y{0}, move_cost{0};

	bool operator == (const Vec2i& coordinates_) { return (x == coordinates_.x && y == coordinates_.y); }
	Vec2i operator + (const Vec2i& right_) { return{ x + right_.x, y + right_.y }; }
};

class Heuristic
{
	static Vec2i getDelta(Vec2i source_, Vec2i target_)
	{
		return { abs(source_.x - target_.x),  abs(source_.y - target_.y) };
	}

public:
	static uint32_t manhattan(Vec2i source_, Vec2i target_)
	{
		auto delta = getDelta(source_, target_);
		return static_cast<uint32_t>(10 * (delta.x + delta.y));
	}

	static uint32_t euclidean(Vec2i source_, Vec2i target_)
	{
		auto delta = getDelta(source_, target_);
		return static_cast<uint32_t>(10 * sqrt(pow(delta.x, 2) + pow(delta.y, 2)));
	}

	static uint32_t octagonal(Vec2i source_, Vec2i target_)
	{
		auto delta = getDelta(source_, target_);
		return 10 * (delta.x + delta.y) + (-6) * std::min(delta.x, delta.y);
	}
};

typedef std::function<uint32_t(Vec2i, Vec2i)> HeuristicFunction;
typedef std::vector<Vec2i> CoordinateList;
typedef std::function<bool(uint16_t x, uint16_t y)> CollisionDetectionFunction;

struct Node
{
	uint32_t G, H;
	Vec2i coordinates;
	Node *parent;

	Node(Vec2i coord_, Node *parent_ = nullptr)
	{
		parent = parent_;
		coordinates = coord_;
		G = H = 0;
	}

	uint32_t getScore() { return G + H; }
};

using NodeSet = std::vector<Node*>;

class Generator
{
	Node *findNodeOnList(NodeSet& nodes_, Vec2i coordinates_)
	{
		for (auto node : nodes_) {
			if (node->coordinates == coordinates_) {
				return node;
			}
		}
		return nullptr;
	}
	void releaseNodes(NodeSet& nodes_)
	{
		for (auto it = nodes_.begin(); it != nodes_.end();) {
			delete *it;
			it = nodes_.erase(it);
		}
	}

public:
	Generator()
	{
		setDiagonalMovement(false);
		setHeuristic(&Heuristic::manhattan);
	}

	Generator(Vec2i worldSize_, CollisionDetectionFunction c, bool diagonal_movement = true, HeuristicFunction h = &Heuristic::manhattan)
	{
		setWorldSize(worldSize_);
		setCollisionDetectionFunction(c);
		setDiagonalMovement(diagonal_movement);
		setHeuristic(h);
	}

	void setWorldSize(Vec2i worldSize_) { worldSize = worldSize_; }

	void setCollisionDetectionFunction(CollisionDetectionFunction c) { check_collision = c; };

	void setDiagonalMovement(bool enable_) { directions = (enable_ ? 8 : 4); }

	void setHeuristic(HeuristicFunction heuristic_) { heuristic = std::bind(heuristic_, std::placeholders::_1, std::placeholders::_2); }

	CoordinateList findPath(Vec2i source_, Vec2i target_)
	{
		CoordinateList path;
		Node *current = nullptr;
		NodeSet openSet, closedSet;

		openSet.reserve(100);
		closedSet.reserve(100);
		openSet.push_back(new Node(source_));

		if (check_collision(target_.x, target_.y))
			return path;

		while (!openSet.empty()) {
			auto current_it = openSet.begin();
			current = *current_it;
			for (auto it = openSet.begin(); it != openSet.end(); it++) {
				auto node = *it;
				if (node->getScore() <= current->getScore()) {
					current = node;
					current_it = it;
				}
			}

			if (current->coordinates == target_) {
				break;
			}

			closedSet.push_back(current);
			openSet.erase(current_it);

			for (uint32_t i = 0; i < directions; ++i) {
				Vec2i newCoordinates(current->coordinates + direction[i]);
				if (check_collision(newCoordinates.x, newCoordinates.y) ||
					findNodeOnList(closedSet, newCoordinates)) {
					continue;
				}

				newCoordinates.move_cost = ((i < 4) ? 10 : 14);
				uint32_t totalCost = current->G + newCoordinates.move_cost;

				Node *successor = findNodeOnList(openSet, newCoordinates);
				if (successor == nullptr) {
					successor = new Node(newCoordinates, current);
					successor->G = totalCost;
					successor->H = heuristic(successor->coordinates, target_);
					openSet.push_back(successor);
				}
				else if (totalCost < successor->G) {
					successor->parent = current;
					successor->G = totalCost;
				}
			}
		}

		while (current != nullptr) {
			path.push_back(current->coordinates);
			current = current->parent;
		}

		releaseNodes(openSet);
		releaseNodes(closedSet);

		return path;
	}

private:
	HeuristicFunction heuristic;
	CollisionDetectionFunction check_collision;
	CoordinateList direction = {
		{ 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 },
		{ -1, -1 }, { 1, 1 }, { -1, 1 }, { 1, -1 }
	};
	Vec2i worldSize;
	uint32_t directions;
};
}
}
}

#endif /* HORIZON_ZONE_GAME_MAP_PATH_ASTAR_HPP */
