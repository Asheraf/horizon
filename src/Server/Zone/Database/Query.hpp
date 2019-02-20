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

#ifndef HORIZON_ZONE_DATABASE_QUERY_HPP
#define HORIZON_ZONE_DATABASE_QUERY_HPP

#include "Server/Common/Database/Query.hpp"

#include <map>
#include <stdio.h>
#include <mysqlx/xdevapi.h>

class GameAccount;

namespace Horizon
{
	namespace Models
	{
		namespace Character
		{
			class Character;
		}
	}
}

namespace Horizon
{
	namespace Char
	{
		namespace Database
		{
			enum char_query_types
			{
				SELECT_ALL_CHARS_BY_AID,
				CHECK_EXISTING_CHAR_BY_NAME,
			};
			class Query : public Horizon::Common::Database::Query
			{
			public:
				Query();
				~Query();

				static Query *getInstance()
				{
					static Query query;
					return &query;
				}

				void InitializeQueryStrings();

				std::shared_ptr<Horizon::Models::Character::Character> CreateCharacterModelFromResult(uint32_t account_id, mysqlx::Row record);
			};
		}
	}
}

#define ZoneQuery Horizon::Zone::Database::Query::getInstance()

#endif /* HORIZON_ZONE_DATABASE_QUERY_HPP */

