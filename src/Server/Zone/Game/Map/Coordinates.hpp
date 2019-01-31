#ifndef HORIZON_ZONE_GAME_MAP_COORDINATES_HPP
#define HORIZON_ZONE_GAME_MAP_COORDINATES_HPP

#include <cstdint>
#include <stdlib.h>
#include <algorithm>

template <uint16_t UPPER_BOUNDS>
class Coordinates
{
public:
	Coordinates(uint16_t x = 0, uint16_t y = 0)
	: _x(x), _y(y)
	{
		//
	}

	Coordinates(const Coordinates<UPPER_BOUNDS> &obj)
	: _x(obj._x), _y(obj._y)
	{
		//
	}

	Coordinates<UPPER_BOUNDS> &operator= (const Coordinates<UPPER_BOUNDS> &obj)
	{
		_x = obj._x;
		_y = obj._y;
		return *this;
	}

	bool operator == (const Coordinates<UPPER_BOUNDS> &right)
	{
		return (_x == right._x && _y == right._y);
	}

	bool operator != (const Coordinates<UPPER_BOUNDS> &right)
	{
		return !(*this == right);
	}

	template <uint16_t BOUNDS>
	bool within_range(Coordinates<BOUNDS> &bounds, int range)
	{
		int x_diff = _x - bounds.x();
		int y_diff = _y - bounds.y();

		return abs(x_diff) <= range && abs(y_diff) <= range;
	}

	template<uint16_t BOUNDS>
	Coordinates<BOUNDS> at_range(int range) const
	{
		int x = std::max(0, std::min((_x + range), (int) BOUNDS));
		int y = std::max(0, std::min((_y + range), (int) BOUNDS));

		return Coordinates<BOUNDS>(x, y);
	}

	template<uint16_t BOUNDS, uint16_t SCALED_BOUNDS>
	Coordinates<SCALED_BOUNDS> scale() const
	{
		int x = _x / BOUNDS;
		int y = _y / BOUNDS;

		return Coordinates<SCALED_BOUNDS>(x, y);
	}

	uint16_t x() const { return _x; }
	uint16_t y() const { return _y; }

	void inc_x(uint16_t val)
	{
		if (_x + val < UPPER_BOUNDS)
			_x += val;
		else
			_x = UPPER_BOUNDS - 1;
	}

	void dec_x(uint16_t val)
	{
		if (_x > val)
			_x -= val;
		else
			_x = 0;
	}

	void inc_y(uint16_t val)
	{
		if (_y + val < UPPER_BOUNDS)
			_y += val;
		else
			_y = UPPER_BOUNDS - 1;
	}

	void dec_y(uint16_t val)
	{
		if (_y > val)
			_y -= val;
		else
			_y = 0;
	}

	bool valid() const
	{
		return _x < UPPER_BOUNDS && _y < UPPER_BOUNDS;
	}

private:
	uint16_t _x;
	uint16_t _y;
};

#endif /* HORIZON_ZONE_GAME_MAP_COORDINATES_HPP */
