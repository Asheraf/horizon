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

#ifndef HORIZON_GAME_ACOUNT_HPP
#define HORIZON_GAME_ACOUNT_HPP

#include "Server/Common/Server.hpp"

#include <cstdint>

#include <sqlpp11/table.h>
#include <sqlpp11/data_types.h>
#include <sqlpp11/char_sequence.h>

enum game_account_gender_type
{
	ACCOUNT_GENDER_MALE,
	ACCOUNT_GENDER_FEMALE,
	ACCOUNT_GENDER_NONE
};

enum game_account_state_type
{
	ACCOUNT_STATE_NONE,
	ACCOUNT_STATE_BANNED
};

//#define SCRYPT_DERIVED_HASH_SIZE 64
//#define SCRYPT_SALT_SIZE 8
//#define SCRYPT_COMPUTATION_COST 2048
//#define SCRYPT_BLOCK_SIZE 8
//#define SCRYPT_PARALLELIZATION 16
//
//typedef std::map<uint32_t, std::shared_ptr<Horizon::Models::Character::Character>> AccountCharacterMapType;

namespace Horizon
{
namespace SQL
{
// CREATE TABLE `game_accounts` (
// `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
// `username` varchar(23) NOT NULL DEFAULT '',
// `hash` varchar(128) NOT NULL DEFAULT '',
// `salt` varchar(16) NOT NULL DEFAULT '',
// `gender` enum('M','F','NA') NOT NULL DEFAULT 'M',
// `email` varchar(39) NOT NULL DEFAULT '',
// `group_id` tinyint(3) NOT NULL DEFAULT '0',
// `state` int(11) unsigned NOT NULL DEFAULT '0',
// `unban_time` int(11) unsigned NOT NULL DEFAULT '0',
// `expiration_time` int(11) unsigned NOT NULL DEFAULT '0',
// `login_count` mediumint(9) unsigned NOT NULL DEFAULT '0',
// `last_login` datetime DEFAULT NULL,
// `last_ip` varchar(100) NOT NULL DEFAULT '',
// `birth_date` date DEFAULT NULL,
// `character_slots` tinyint(3) unsigned NOT NULL DEFAULT '0',
// `pincode` varchar(4) NOT NULL DEFAULT '',
// `pincode_expiry` int(11) unsigned NOT NULL DEFAULT '0',
// PRIMARY KEY (`id`),
// KEY `name` (`username`),
// KEY `id` (`id`),
// KEY `email` (`email`),
// KEY `last_ip` (`last_ip`)
// ) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
namespace TableGameAccounts_
{

struct id
{
	struct _alias_t
	{
		static constexpr const char _literal[] = "id";
		using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
		template <typename T>
		struct _member_t
		{
			T id;
			T& operator()()
			{
				return id;
			}
			const T& operator()() const
			{
				return id;
			}
		};
	};
	using _traits = sqlpp::make_traits<sqlpp::bigint, sqlpp::tag::must_not_insert, sqlpp::tag::must_not_update>;
};

struct username
{
	struct _alias_t
	{
		static constexpr const char _literal[] = "username";
		using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
		template <typename T>
		struct _member_t
		{
			T username;
			T& operator()()
			{
				return username;
			}
			const T& operator()() const
			{
				return username;
			}
		};
	};
	using _traits = sqlpp::make_traits<sqlpp::varchar, sqlpp::tag::require_insert>;
};

struct hash
{
	struct _alias_t
	{
		static constexpr const char _literal[] = "hash";
		using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
		template <typename T>
		struct _member_t
		{
			T hash;
			T& operator()()
			{
				return hash;
			}
			const T& operator()() const
			{
				return hash;
			}
		};
	};
	using _traits = sqlpp::make_traits<sqlpp::varchar, sqlpp::tag::require_insert>;
};

struct salt
{
	struct _alias_t
	{
		static constexpr const char _literal[] = "salt";
		using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
		template <typename T>
		struct _member_t
		{
			T salt;
			T& operator()()
			{
				return salt;
			}
			const T& operator()() const
			{
				return salt;
			}
		};
	};
	using _traits = sqlpp::make_traits<sqlpp::varchar, sqlpp::tag::require_insert>;
};

struct gender
{
	struct _alias_t
	{
		static constexpr const char _literal[] = "gender";
		using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
		template <typename T>
		struct _member_t
		{
			T gender;
			T& operator()()
			{
				return gender;
			}
			const T& operator()() const
			{
				return gender;
			}
		};
	};
	using _traits = sqlpp::make_traits<sqlpp::char_>;
};

struct email
{
	struct _alias_t
	{
		static constexpr const char _literal[] = "email";
		using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
		template <typename T>
		struct _member_t
		{
			T email;
			T& operator()()
			{
				return email;
			}
			const T& operator()() const
			{
				return email;
			}
		};
	};
	using _traits = sqlpp::make_traits<sqlpp::varchar>;
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
	using _traits = sqlpp::make_traits<sqlpp::tinyint>;
};

struct state
{
	struct _alias_t
	{
		static constexpr const char _literal[] = "state";
		using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
		template <typename T>
		struct _member_t
		{
			T state;
			T& operator()()
			{
				return state;
			}
			const T& operator()() const
			{
				return state;
			}
		};
	};
	using _traits = sqlpp::make_traits<sqlpp::integer>;
};

struct unban_time
{
	struct _alias_t
	{
		static constexpr const char _literal[] = "unban_time";
		using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
		template <typename T>
		struct _member_t
		{
			T unban_time;
			T& operator()()
			{
				return unban_time;
			}
			const T& operator()() const
			{
				return unban_time;
			}
		};
	};
	using _traits = sqlpp::make_traits<sqlpp::integer>;
};

struct expiration_time
{
	struct _alias_t
	{
		static constexpr const char _literal[] = "expiration_time";
		using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
		template <typename T>
		struct _member_t
		{
			T expiration_time;
			T& operator()()
			{
				return expiration_time;
			}
			const T& operator()() const
			{
				return expiration_time;
			}
		};
	};
	using _traits = sqlpp::make_traits<sqlpp::integer>;
};

struct login_count
{
	struct _alias_t
	{
		static constexpr const char _literal[] = "login_count";
		using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
		template <typename T>
		struct _member_t
		{
			T login_count;
			T& operator()()
			{
				return login_count;
			}
			const T& operator()() const
			{
				return login_count;
			}
		};
	};
	using _traits = sqlpp::make_traits<sqlpp::integer>;
};

struct last_login
{
	struct _alias_t
	{
		static constexpr const char _literal[] = "last_login";
		using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
		template <typename T>
		struct _member_t
		{
			T last_login;
			T& operator()()
			{
				return last_login;
			}
			const T& operator()() const
			{
				return last_login;
			}
		};
	};
	using _traits = sqlpp::make_traits<sqlpp::time_point>;
};

struct last_ip
{
	struct _alias_t
	{
		static constexpr const char _literal[] = "last_ip";
		using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
		template <typename T>
		struct _member_t
		{
			T last_ip;
			T& operator()()
			{
				return last_ip;
			}
			const T& operator()() const
			{
				return last_ip;
			}
		};
	};
	using _traits = sqlpp::make_traits<sqlpp::varchar>;
};

struct birth_date
{
	struct _alias_t
	{
		static constexpr const char _literal[] = "birth_date";
		using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
		template <typename T>
		struct _member_t
		{
			T birth_date;
			T& operator()()
			{
				return birth_date;
			}
			const T& operator()() const
			{
				return birth_date;
			}
		};
	};
	using _traits = sqlpp::make_traits<sqlpp::day_point>;
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
	using _traits = sqlpp::make_traits<sqlpp::tinyint>;
};

struct pincode
{
	struct _alias_t
	{
		static constexpr const char _literal[] = "pincode";
		using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
		template <typename T>
		struct _member_t
		{
			T pincode;
			T& operator()()
			{
				return pincode;
			}
			const T& operator()() const
			{
				return pincode;
			}
		};
	};
	using _traits = sqlpp::make_traits<sqlpp::varchar>;
};

struct pincode_expiry
{
	struct _alias_t
	{
		static constexpr const char _literal[] = "pincode_expiry";
		using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
		template <typename T>
		struct _member_t
		{
			T pincode_expiry;
			T& operator()()
			{
				return pincode_expiry;
			}
			const T& operator()() const
			{
				return pincode_expiry;
			}
		};
	};
	using _traits = sqlpp::make_traits<sqlpp::integer>;
};
}

struct TableGameAccounts : sqlpp::table_t<TableGameAccounts,
	TableGameAccounts_::id, TableGameAccounts_::username, TableGameAccounts_::hash, TableGameAccounts_::salt,
	TableGameAccounts_::gender, TableGameAccounts_::email, TableGameAccounts_::group_id, TableGameAccounts_::state,
	TableGameAccounts_::unban_time, TableGameAccounts_::expiration_time, TableGameAccounts_::login_count, TableGameAccounts_::last_login,
	TableGameAccounts_::last_ip, TableGameAccounts_::birth_date, TableGameAccounts_::character_slots, TableGameAccounts_::pincode, TableGameAccounts_::pincode_expiry>
{
	struct _alias_t
	{
		static constexpr const char _literal[] = "game_accounts";
		using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
		template <typename T>
		struct _member_t
		{
			T game_accounts;
			T& operator()()
			{
				return game_accounts;
			}
			const T& operator()() const
			{
				return game_accounts;
			}
		};
	};
};
}
}

#endif // HORIZON_GAME_ACOUNT_HPP
