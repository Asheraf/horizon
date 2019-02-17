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
 * Base Author - Sagun Khosla. (sagunxp@gmail.com)
 *
 * Under a proprietary license this file is not for use
 * or viewing without permission.
 **************************************************/

#ifndef HORIZON_COMMON_UTILITIES_STRUTILS_HPP
#define HORIZON_COMMON_UTILITIES_STRUTILS_HPP

#include <sstream>
#include <vector>

class StrUtils
{
public:
	static std::vector<std::string> explode(std::string const &s, char delim)
	{
		std::vector<std::string> result;
		std::istringstream iss(s);

		for (std::string token; std::getline(iss, token, delim); /* */)
			result.push_back(std::move(token));

		return result;
	}

};


#endif // HORIZON_COMMON_UTILITIES_STRUTILS_HPP
