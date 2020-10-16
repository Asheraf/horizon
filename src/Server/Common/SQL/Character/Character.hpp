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

#ifndef HORIZON_MODELS_CHARACTERS_CHARACTER_HPP
#define HORIZON_MODELS_CHARACTERS_CHARACTER_HPP

#include <sqlpp11/table.h>
#include <sqlpp11/data_types.h>
#include <sqlpp11/char_sequence.h>

enum character_gender_type
{
	CHARACTER_GENDER_FEMALE = 0,
	CHARACTER_GENDER_MALE   = 1,
};

enum character_save_mask
{
	CHAR_SAVE_BASE_DATA         = 0x1,
	CHAR_SAVE_STATUS_DATA       = 0x2,
	CHAR_SAVE_INVENTORY_DATA    = 0x4,
	CHAR_SAVE_ALL               = 0xf,
};

namespace Horizon
{
namespace SQL
{
namespace TableCharacters_
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
	using _traits = sqlpp::make_traits<sqlpp::integer>;
};

struct account_id
{
	struct _alias_t
	{
		static constexpr const char _literal[] = "account_id";
		using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
		template <typename T>
		struct _member_t
		{
			T account_id;
			T& operator()()
			{
				return account_id;
			}
			const T& operator()() const
			{
				return account_id;
			}
		};
	};
	using _traits = sqlpp::make_traits<sqlpp::integer>;
};

struct slot
{
	struct _alias_t
	{
		static constexpr const char _literal[] = "slot";
		using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
		template <typename T>
		struct _member_t
		{
			T slot;
			T& operator()()
			{
				return slot;
			}
			const T& operator()() const
			{
				return slot;
			}
		};
	};
	using _traits = sqlpp::make_traits<sqlpp::tinyint>;
};

struct name
{
	struct _alias_t
	{
		static constexpr const char _literal[] = "name";
		using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
		template <typename T>
		struct _member_t
		{
			T name;
			T& operator()()
			{
				return name;
			}
			const T& operator()() const
			{
				return name;
			}
		};
	};
	using _traits = sqlpp::make_traits<sqlpp::varchar>;
};

struct online
{
	struct _alias_t
	{
		static constexpr const char _literal[] = "online";
		using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
		template <typename T>
		struct _member_t
		{
			T online;
			T& operator()()
			{
				return online;
			}
			const T& operator()() const
			{
				return online;
			}
		};
	};
	using _traits = sqlpp::make_traits<sqlpp::tinyint>;
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

struct deleted_at
{
	struct _alias_t
	{
		static constexpr const char _literal[] = "deleted_at";
		using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
		template <typename T>
		struct _member_t
		{
			T deleted_at;
			T& operator()()
			{
				return deleted_at;
			}
			const T& operator()() const
			{
				return deleted_at;
			}
		};
	};
	using _traits = sqlpp::make_traits<sqlpp::time_point, sqlpp::tag::can_be_null>;
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

struct rename_count
{
	struct _alias_t
	{
		static constexpr const char _literal[] = "rename_count";
		using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
		template <typename T>
		struct _member_t
		{
			T rename_count;
			T& operator()()
			{
				return rename_count;
			}
			const T& operator()() const
			{
				return rename_count;
			}
		};
	};
	using _traits = sqlpp::make_traits<sqlpp::tinyint>;
};

struct last_unique_id
{
	struct _alias_t
	{
		static constexpr const char _literal[] = "last_unique_id";
		using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
		template <typename T>
		struct _member_t
		{
			T last_unique_id;
			T& operator()()
			{
				return last_unique_id;
			}
			const T& operator()() const
			{
				return last_unique_id;
			}
		};
	};
	using _traits = sqlpp::make_traits<sqlpp::bigint>;
};

struct hotkey_row_index
{
	struct _alias_t
	{
		static constexpr const char _literal[] = "hotkey_row_index";
		using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
		template <typename T>
		struct _member_t
		{
			T hotkey_row_index;
			T& operator()()
			{
				return hotkey_row_index;
			}
			const T& operator()() const
			{
				return hotkey_row_index;
			}
		};
	};
	using _traits = sqlpp::make_traits<sqlpp::tinyint>;
};

struct change_slot_count
{
	struct _alias_t
	{
		static constexpr const char _literal[] = "change_slot_count";
		using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
		template <typename T>
		struct _member_t
		{
			T change_slot_count;
			T& operator()()
			{
				return change_slot_count;
			}
			const T& operator()() const
			{
				return change_slot_count;
			}
		};
	};
	using _traits = sqlpp::make_traits<sqlpp::tinyint>;
};

struct font
{
	struct _alias_t
	{
		static constexpr const char _literal[] = "font";
		using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
		template <typename T>
		struct _member_t
		{
			T font;
			T& operator()()
			{
				return font;
			}
			const T& operator()() const
			{
				return font;
			}
		};
	};
	using _traits = sqlpp::make_traits<sqlpp::tinyint>;
};

struct show_equip
{
	struct _alias_t
	{
		static constexpr const char _literal[] = "show_equip";
		using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
		template <typename T>
		struct _member_t
		{
			T show_equip;
			T& operator()()
			{
				return show_equip;
			}
			const T& operator()() const
			{
				return show_equip;
			}
		};
	};
	using _traits = sqlpp::make_traits<sqlpp::tinyint>;
};

struct allow_party
{
	struct _alias_t
	{
		static constexpr const char _literal[] = "allow_party";
		using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
		template <typename T>
		struct _member_t
		{
			T allow_party;
			T& operator()()
			{
				return allow_party;
			}
			const T& operator()() const
			{
				return allow_party;
			}
		};
	};
	using _traits = sqlpp::make_traits<sqlpp::tinyint>;
};

struct partner_aid
{
	struct _alias_t
	{
		static constexpr const char _literal[] = "partner_aid";
		using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
		template <typename T>
		struct _member_t
		{
			T partner_aid;
			T& operator()()
			{
				return partner_aid;
			}
			const T& operator()() const
			{
				return partner_aid;
			}
		};
	};
	using _traits = sqlpp::make_traits<sqlpp::integer>;
};

struct father_aid
{
	struct _alias_t
	{
		static constexpr const char _literal[] = "father_aid";
		using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
		template <typename T>
		struct _member_t
		{
			T father_aid;
			T& operator()()
			{
				return father_aid;
			}
			const T& operator()() const
			{
				return father_aid;
			}
		};
	};
	using _traits = sqlpp::make_traits<sqlpp::integer>;
};

struct mother_aid
{
	struct _alias_t
	{
		static constexpr const char _literal[] = "mother_aid";
		using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
		template <typename T>
		struct _member_t
		{
			T mother_aid;
			T& operator()()
			{
				return mother_aid;
			}
			const T& operator()() const
			{
				return mother_aid;
			}
		};
	};
	using _traits = sqlpp::make_traits<sqlpp::integer>;
};

struct child_aid
{
	struct _alias_t
	{
		static constexpr const char _literal[] = "child_aid";
		using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
		template <typename T>
		struct _member_t
		{
			T child_aid;
			T& operator()()
			{
				return child_aid;
			}
			const T& operator()() const
			{
				return child_aid;
			}
		};
	};
	using _traits = sqlpp::make_traits<sqlpp::integer>;
};

struct party_id
{
	struct _alias_t
	{
		static constexpr const char _literal[] = "party_id";
		using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
		template <typename T>
		struct _member_t
		{
			T party_id;
			T& operator()()
			{
				return party_id;
			}
			const T& operator()() const
			{
				return party_id;
			}
		};
	};
	using _traits = sqlpp::make_traits<sqlpp::integer>;
};

struct guild_id
{
	struct _alias_t
	{
		static constexpr const char _literal[] = "guild_id";
		using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
		template <typename T>
		struct _member_t
		{
			T guild_id;
			T& operator()()
			{
				return guild_id;
			}
			const T& operator()() const
			{
				return guild_id;
			}
		};
	};
	using _traits = sqlpp::make_traits<sqlpp::integer>;
};

struct pet_id
{
	struct _alias_t
	{
		static constexpr const char _literal[] = "pet_id";
		using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
		template <typename T>
		struct _member_t
		{
			T pet_id;
			T& operator()()
			{
				return pet_id;
			}
			const T& operator()() const
			{
				return pet_id;
			}
		};
	};
	using _traits = sqlpp::make_traits<sqlpp::integer>;
};

struct homun_id
{
	struct _alias_t
	{
		static constexpr const char _literal[] = "homun_id";
		using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
		template <typename T>
		struct _member_t
		{
			T homun_id;
			T& operator()()
			{
				return homun_id;
			}
			const T& operator()() const
			{
				return homun_id;
			}
		};
	};
	using _traits = sqlpp::make_traits<sqlpp::integer>;
};

struct elemental_id
{
	struct _alias_t
	{
		static constexpr const char _literal[] = "elemental_id";
		using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
		template <typename T>
		struct _member_t
		{
			T elemental_id;
			T& operator()()
			{
				return elemental_id;
			}
			const T& operator()() const
			{
				return elemental_id;
			}
		};
	};
	using _traits = sqlpp::make_traits<sqlpp::integer>;
};

struct current_map
{
	struct _alias_t
	{
		static constexpr const char _literal[] = "current_map";
		using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
		template <typename T>
		struct _member_t
		{
			T current_map;
			T& operator()()
			{
				return current_map;
			}
			const T& operator()() const
			{
				return current_map;
			}
		};
	};
	using _traits = sqlpp::make_traits<sqlpp::varchar>;
};

struct current_x
{
	struct _alias_t
	{
		static constexpr const char _literal[] = "current_x";
		using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
		template <typename T>
		struct _member_t
		{
			T current_x;
			T& operator()()
			{
				return current_x;
			}
			const T& operator()() const
			{
				return current_x;
			}
		};
	};
	using _traits = sqlpp::make_traits<sqlpp::smallint>;
};

struct current_y
{
	struct _alias_t
	{
		static constexpr const char _literal[] = "current_y";
		using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
		template <typename T>
		struct _member_t
		{
			T current_y;
			T& operator()()
			{
				return current_y;
			}
			const T& operator()() const
			{
				return current_y;
			}
		};
	};
	using _traits = sqlpp::make_traits<sqlpp::smallint>;
};

struct saved_map
{
	struct _alias_t
	{
		static constexpr const char _literal[] = "saved_map";
		using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
		template <typename T>
		struct _member_t
		{
			T saved_map;
			T& operator()()
			{
				return saved_map;
			}
			const T& operator()() const
			{
				return saved_map;
			}
		};
	};
	using _traits = sqlpp::make_traits<sqlpp::varchar>;
};

struct saved_x
{
	struct _alias_t
	{
		static constexpr const char _literal[] = "saved_x";
		using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
		template <typename T>
		struct _member_t
		{
			T saved_x;
			T& operator()()
			{
				return saved_x;
			}
			const T& operator()() const
			{
				return saved_x;
			}
		};
	};
	using _traits = sqlpp::make_traits<sqlpp::smallint>;
};

struct saved_y
{
	struct _alias_t
	{
		static constexpr const char _literal[] = "saved_y";
		using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
		template <typename T>
		struct _member_t
		{
			T saved_y;
			T& operator()()
			{
				return saved_y;
			}
			const T& operator()() const
			{
				return saved_y;
			}
		};
	};
	using _traits = sqlpp::make_traits<sqlpp::smallint>;
};
}

struct TableCharacters : sqlpp::table_t<TableCharacters,
TableCharacters_::id, TableCharacters_::account_id, TableCharacters_::slot, TableCharacters_::name, TableCharacters_::online, TableCharacters_::gender, TableCharacters_::deleted_at,
TableCharacters_::unban_time, TableCharacters_::rename_count, TableCharacters_::last_unique_id, TableCharacters_::hotkey_row_index, TableCharacters_::change_slot_count, TableCharacters_::font,
TableCharacters_::show_equip, TableCharacters_::allow_party, TableCharacters_::partner_aid, TableCharacters_::father_aid, TableCharacters_::mother_aid, TableCharacters_::child_aid, TableCharacters_::party_id,
TableCharacters_::guild_id, TableCharacters_::pet_id, TableCharacters_::homun_id, TableCharacters_::elemental_id, TableCharacters_::current_map, TableCharacters_::current_x, TableCharacters_::current_y,
TableCharacters_::saved_map, TableCharacters_::saved_x, TableCharacters_::saved_y>
{
	struct _alias_t
	{
		static constexpr const char _literal[] = "characters";
		using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
		template <typename T>
		struct _member_t
		{
			T characters;
			T& operator()()
			{
				return characters;
			}
			const T& operator()() const
			{
				return characters;
			}
		};
	};
};

}
}

#endif // HORIZON_MODELS_CHARACTERS_CHARACTER_HPP
