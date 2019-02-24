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

#ifndef HORIZON_COMMON_DATABASE_QUERY_HPP
#define HORIZON_COMMON_DATABASE_QUERY_HPP

#include <map>
#include <stdio.h>
#include <string>
#include <utility>
#include <boost/optional.hpp>
#include <memory>

namespace Horizon
{
namespace Common
{
namespace Database
{
class Query
{
	typedef std::map<int, std::string> QueryStringMapType;
public:
	Query() { }
	~Query() { }

	virtual void InitializeQueryStrings() = 0;

	boost::optional<std::string> getQueryString(uint32_t qid)
	{
		auto it = _query_string_map.find(qid);

		if (it != _query_string_map.end())
			return boost::optional<std::string>(it->second);

		return boost::optional<std::string>();
	}

	void addQueryString(uint32_t qid, std::string const &str)
	{
		boost::optional<std::string> query = getQueryString(qid);

		if (query)
			_query_string_map.erase(qid);

		_query_string_map.insert(std::make_pair(qid, str));
	}

private:
	QueryStringMapType _query_string_map;
};
}
}
}

#endif /* HORIZON_COMMON_DATABASE_QUERY_HPP */
