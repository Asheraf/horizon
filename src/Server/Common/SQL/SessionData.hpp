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
 * Base Author - Sagun K. (sagunxp@gmail.com)
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

#ifndef HORIZON_SESSIONDATA_HPP
#define HORIZON_SESSIONDATA_HPP

#include <ctime>
#include <cstdint>

#include <sqlpp11/table.h>
#include <sqlpp11/data_types.h>
#include <sqlpp11/char_sequence.h>

class Server;

namespace Horizon
{
namespace SQL
{
namespace TableSessionData_
{

struct auth_code
{
	struct _alias_t
	{
		static constexpr const char _literal[] = "auth_code";
		using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
		template <typename T>
		struct _member_t
		{
			T auth_code;
			T& operator()()
			{
				return auth_code;
			}
			const T& operator()() const
			{
				return auth_code;
			}
		};
	};
	using _traits = sqlpp::make_traits<sqlpp::integer>;
};

struct game_account_id
{
	struct _alias_t
	{
		static constexpr const char _literal[] = "game_account_id";
		using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
		template <typename T>
		struct _member_t
		{
			T game_account_id;
			T& operator()()
			{
				return game_account_id;
			}
			const T& operator()() const
			{
				return game_account_id;
			}
		};
	};
	using _traits = sqlpp::make_traits<sqlpp::integer>;
};

struct client_version
{
	struct _alias_t
	{
		static constexpr const char _literal[] = "client_version";
		using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
		template <typename T>
		struct _member_t
		{
			T client_version;
			T& operator()()
			{
				return client_version;
			}
			const T& operator()() const
			{
				return client_version;
			}
		};
	};
	using _traits = sqlpp::make_traits<sqlpp::integer>;
};

struct client_type
{
	struct _alias_t
	{
		static constexpr const char _literal[] = "client_type";
		using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
		template <typename T>
		struct _member_t
		{
			T client_type;
			T& operator()()
			{
				return client_type;
			}
			const T& operator()() const
			{
				return client_type;
			}
		};
	};
	using _traits = sqlpp::make_traits<sqlpp::integer>;
};

struct character_slots
{
	struct _alias_t
	{
		static constexpr const char _literal[] = "character_slots";
		using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
		template <typename T>
		struct _member_t
		{
			T character_slots;
			T& operator()()
			{
				return character_slots;
			}
			const T& operator()() const
			{
				return character_slots;
			}
		};
	};
	using _traits = sqlpp::make_traits<sqlpp::integer>;
};

struct group_id
{
	struct _alias_t
	{
		static constexpr const char _literal[] = "group_id";
		using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
		template <typename T>
		struct _member_t
		{
			T group_id;
			T& operator()()
			{
				return group_id;
			}
			const T& operator()() const
			{
				return group_id;
			}
		};
	};
	using _traits = sqlpp::make_traits<sqlpp::integer>;
};

struct connect_time
{
	struct _alias_t
	{
		static constexpr const char _literal[] = "connect_time";
		using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
		template <typename T>
		struct _member_t
		{
			T connect_time;
			T& operator()()
			{
				return connect_time;
			}
			const T& operator()() const
			{
				return connect_time;
			}
		};
	};
	using _traits = sqlpp::make_traits<sqlpp::time_point>;
};

struct current_server
{
	struct _alias_t
	{
		static constexpr const char _literal[] = "current_server";
		using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
		template <typename T>
		struct _member_t
		{
			T current_server;
			T& operator()()
			{
				return current_server;
			}
			const T& operator()() const
			{
				return current_server;
			}
		};
	};
	using _traits = sqlpp::make_traits<sqlpp::char_>;
};

struct last_update
{
	struct _alias_t
	{
		static constexpr const char _literal[] = "last_update";
		using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
		template <typename T>
		struct _member_t
		{
			T last_update;
			T& operator()()
			{
				return last_update;
			}
			const T& operator()() const
			{
				return last_update;
			}
		};
	};
	using _traits = sqlpp::make_traits<sqlpp::integer>;
};
}

struct TableSessionData : sqlpp::table_t<TableSessionData,
TableSessionData_::auth_code, TableSessionData_::game_account_id, TableSessionData_::client_version, TableSessionData_::client_type, TableSessionData_::character_slots,
TableSessionData_::group_id, TableSessionData_::connect_time, TableSessionData_::current_server, TableSessionData_::last_update>
{
	struct _alias_t
	{
		static constexpr const char _literal[] = "session_data";
		using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
		template <typename T>
		struct _member_t
		{
			T session_data;
			T& operator()()
			{
				return session_data;
			}
			const T& operator()() const
			{
				return session_data;
			}
		};
	};
};

}
}

#endif //HORIZON_SESSIONDATA_HPP
