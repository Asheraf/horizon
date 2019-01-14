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
class AStar
{
public:
	enum state
	{
		STATE_IDLE,
		STATE_COMPUTING
	};
	
	struct coords
	{
		int x{0}, y{0};
		uint8_t move_cost{0};

		bool operator== (const coords &c) { return (x == c.x && y == c.y); }
		coords operator+ (const coords &r)
		{
			return { x + r.x, y + r.y };
		}
		coords operator- (const coords &r)
		{
			return { abs(x - r.x),  abs(y - r.y) };
		}
	};

	struct node
	{
		uint32_t _g{0}, _h{0};
		coords _coords{0};
		node *_parent{nullptr};

		node(coords c, node *p = nullptr)
		: _coords(c), _parent(p)
		{
			//
		}

		uint32_t getScore() { return _g + _h; }
	};

	typedef std::function<uint32_t(coords, coords)> HeuristicFunction;
	typedef std::function<bool(uint16_t, uint16_t)> CollisionDetectionFunction;
	typedef std::vector<coords> CoordinateList;
	typedef std::set<node *> NodeSet;

	class Heuristic
	{
	public:
		static uint32_t manhattan(coords source, coords target)
		{
			coords delta = source - target;
			return (10 * (delta.x + delta.y));
		}

		static uint32_t euclidean(coords source, coords target)
		{
			coords delta = source - target;
			return static_cast<uint32_t>(10 * sqrt(pow(delta.x, 2) + pow(delta.y, 2)));
		}

		static uint32_t octagonal(coords source, coords target)
		{
			coords delta = source - target;
			return 10 * (delta.x + delta.y) + (-6) * std::min(delta.x, delta.y);
		}
	};

	AStar()
	{
		enableDiagonalMovement(false);
		setHeuristic(&Heuristic::manhattan);
	}

	AStar(coords map_size, bool diagonal, HeuristicFunction h,  CollisionDetectionFunction collision_func)
	: _heuristic(h), _collision(collision_func), _map_size(map_size), _diagonal_directions(diagonal)
	{
	}

	void setMapSize(coords size)
	{
		_map_size = size;
	}

	void enableDiagonalMovement(bool enable)
	{
		_diagonal_directions = enable;
	}

	void setHeuristic(HeuristicFunction h)
	{
		_heuristic = std::bind(h, std::placeholders::_1, std::placeholders::_2);
	}

	void cancel()
	{
		_cancel = true;
	}

	state get_state() const
	{
		return _state;
	}

	boost::optional<CoordinateList> navigate(coords source_coords, coords target_coords)
	{
		node *current = nullptr;
		NodeSet open_set, closed_set;
		CoordinateList path;

		_state = STATE_COMPUTING;

		open_set.insert(new node(source_coords));

		while (!open_set.empty()) {
			current = *open_set.begin();

			if (_cancel) {
				reset(open_set, closed_set);
				return boost::optional<CoordinateList>();
			}

			for (auto node : open_set)
				if (node->getScore() <= current->getScore())
					current = node;

			// Target Found.
			if (current->_coords == target_coords)
				break;
			else if (checkBounds(target_coords.x, target_coords.y)
				|| _collision(target_coords.x, target_coords.y))
				break;

			// Node evaluated, add to closed set.
			closed_set.insert(current);
			// Remove from open set.
			open_set.erase(std::find(open_set.begin(), open_set.end(), current));

			for (uint8_t i = 0; i < (_diagonal_directions ? 8 : 4); ++i) {
				coords new_coords(current->_coords + _directions[i]);

				if (_cancel) {
					reset(open_set, closed_set);
					return boost::optional<CoordinateList>();
				}

				new_coords.move_cost = (i < 4) ? 10 : 14;

				// Collision Detection or closed node.
				if (checkBounds(new_coords.x, new_coords.y)
					|| _collision(new_coords.x, new_coords.y)
					|| findNodeInList(closed_set, new_coords))
					continue;

				uint32_t cost = current->_g + new_coords.move_cost;

				node *child = findNodeInList(open_set, new_coords);

				if (child == nullptr) {
					child = new node(new_coords, current);
					child->_g = cost;
					child->_h = _heuristic(child->_coords, target_coords);
					open_set.insert(child);
				} else if (cost < child->_g) {
					child->_parent = current;
					child->_g = cost;
				}
			}
		}

		while (current != nullptr) {
			path.push_back(current->_coords);
			current = current->_parent;
		}

		reset(open_set, closed_set);

		return boost::optional<CoordinateList>(path);
	}

private:
	bool checkBounds(int x, int y)
	{
		if (x < 0 || y < 0
			|| x >= _map_size.x
			|| y >= _map_size.y)
			return true;

		return false;
	}

	node *findNodeInList(NodeSet &nodes, coords c)
	{
		for (auto node : nodes)
			if (node->_coords == c)
				return node;

		return nullptr;
	}

	void releaseNodes(NodeSet &nodes)
	{
		for (auto it = nodes.begin(); it != nodes.end();) {
			delete *it;
			it = nodes.erase(it);
		}
	}

	void reset(NodeSet &open_set, NodeSet &closed_set)
	{
		releaseNodes(open_set);
		releaseNodes(closed_set);

		_state = STATE_IDLE;
		_cancel = false;
	}

	HeuristicFunction _heuristic;
	CollisionDetectionFunction _collision;
	bool _cancel{false};
	coords _map_size;
	state _state{STATE_IDLE};
	bool _diagonal_directions{false};
	coords _directions[8] = {
		{0, 1},   {1, 0}, {0, -1}, {-1, 0},
		{-1, -1}, {1, 1}, {-1, 1}, {1, -1}
	};
};
}
}

#endif /* HORIZON_ZONE_GAME_MAP_PATH_ASTAR_HPP */
