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
 * Base Author - Sagun Khosla. (sagunxp@gmail.com)
 *
 * Under a proprietary license this file is not for use
 * or viewing without permission.
 **************************************************/

#ifndef HORIZON_GAME_MAP_MAP_HPP
#define HORIZON_GAME_MAP_MAP_HPP

namespace Horizon
{
namespace Game
{
namespace Map
{
class Map
{
public:
	Map();
	~Map();

private:
	uint16_t _width, _height;    // Map Dimensions (X, Y).
	
}
}
}
}

#endif /* HORIZON_GAME_MAP_MAP_HPP */
