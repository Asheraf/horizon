#ifndef HORIZON_ZONE_GAME_MAP_COORDINATES_HPP
#define HORIZON_ZONE_GAME_MAP_COORDINATES_HPP

#include <cstdint>

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

	uint16_t x() { return _x; }
	uint16_t y() { return _y; }

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
