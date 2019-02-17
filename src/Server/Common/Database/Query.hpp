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

#ifndef HORIZON_COMMON_DATABASE_QUERY_HPP
#define HORIZON_COMMON_DATABASE_QUERY_HPP

#include <map>
#include <stdio.h>
#include <string>
#include <utility>
#include <boost/optional.hpp>

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
