/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
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

#include <string>
#include <cstdint>

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

class Server;

namespace Horizon
{
namespace Models
{
namespace Character
{

class Status;
class Inventory;

class Character
{
public:
	Character(uint32_t char_id) : _character_id(char_id)
	{ }

	// Creation constructor without char_id.
	Character(uint32_t account_id, std::string const &name, uint8_t slot, character_gender_type gender)
	: _account_id(account_id), _slot(slot), _name(name), _online(false), _gender(gender), _deleted_at(0)
	{ }

	~Character() { }

	/**
	 * Load all fields from the database into this instance.
	 * @param server
	 * @param char_id
	 * @return
	 */
	bool load(Server *server, uint32_t char_id);

	bool load_all(Server *server, uint32_t char_id);

	/**
	 * @brief Save this model to the database in its current state.
	 * @param[in|out] server   instance of the server object used to borrow mysql connections.
	 */
	bool save(Server *server);

	bool create(Server *server);

	uint32_t save(Server *server, uint32_t type);

	/* Character ID */
	uint32_t get_id() const
	{
		return _character_id;
	}

	void set_id(uint32_t id)
	{
		_character_id = id;
	}

	/* Account ID */
	uint32_t get_account_id() const { return _account_id; }
	void set_account_id(uint32_t id) { _account_id = id; }
	/* Slot */
	uint16_t get_slot() const { return _slot; }
	void set_slot(uint16_t slot) { _slot = slot; }
	/* Name */
	std::string const &get_name() const { return _name; }
	void set_name(std::string const &name) { _name = name; }
	/* Online */
	bool is_online() const { return _online; }
	void set_online() { _online = true; }
	void set_offline() { _online = false; }
	/* Gender */
	character_gender_type get_gender() const { return _gender; }
	void set_gender(character_gender_type gender) { _gender = gender; }
	/* Deleted */
	uint32_t get_deleted_at() { return _deleted_at; }
	void set_deleted_at(uint32_t time) { _deleted_at = time; }
	/* Unban Time */
	uint32_t get_unban_time() const { return _unban_time; }
	void set_unban_time(uint32_t unban_time) { _unban_time = unban_time; }
	/* Pet ID */
	uint32_t get_pet_id() const { return _pet_id; }
	void set_pet_id(uint32_t pet_id) { _pet_id = pet_id; }
	/* Homun ID */
	uint32_t get_homun_id() const { return _homun_id; }
	void set_homun_id(uint32_t homun_id) { _homun_id = homun_id; }
	/* Elemental ID */
	uint32_t get_elemental_id() const { return _elemental_id; }
	void set_elemental_id(uint32_t elemental_id) { _elemental_id = elemental_id; }
	/* Parter Account ID */
	uint32_t get_partner_aid() const { return _parter_aid; }
	void set_partner_aid(uint32_t parter_aid) { _parter_aid = parter_aid; }
	/* Father Account ID */
	uint32_t get_father_aid() const { return _father_aid; }
	void set_father_aid(uint32_t father_aid) { _father_aid = father_aid; }
	/* Mother Account ID */
	uint32_t get_mother_aid() const { return _mother_aid; }
	void set_mother_aid(uint32_t mother_aid) { _mother_aid = mother_aid; }
	/* Child Account ID */
	uint32_t get_child_aid() const { return _child_aid; }
	void set_child_aid(uint32_t child_aid) { _child_aid = child_aid; }
	/* Party ID */
	uint32_t get_party_id() const { return _party_id; }
	void set_party_id(uint32_t party_id) { _party_id = party_id; }
	/* Guild ID */
	uint32_t get_guild_id() const { return _guild_id; }
	void set_guild_id(uint32_t guild_id) { _guild_id = guild_id; }
	/* Character Rename Count */
	uint8_t get_rename_count() const { return _rename_count; }
	void set_rename_count(uint8_t rename_count) { _rename_count = rename_count; }
	/* Last Unique Id */
	uint64_t get_last_unique_id() const { return _last_unique_id; }
	void set_last_unique_id(uint64_t last_unique_id) { _last_unique_id = last_unique_id; }
	/* Hotkey Row Index */
	uint8_t get_hotkey_row_index() const { return _hotkey_row_index; }
	void set_hotkey_row_index(uint8_t hotkey_row_index) { _hotkey_row_index = hotkey_row_index; }
	/* Change Slot Count */
	uint8_t get_change_slot_count() const { return _change_slot_count; }
	void set_change_slot_count(uint8_t change_slot_count) { _change_slot_count = change_slot_count; }
	/* Current Map */
	const std::string &get_current_map() const { return _current_map; }
	void set_current_map(const std::string &map) { _current_map = map; }
	/* Current X */
	uint16_t get_current_x() const { return _current_x; }
	void set_current_x(uint16_t current_x) { _current_x = current_x; }
	/* Current Y */
	uint16_t get_current_y() const { return _current_y; }
	void set_current_y(uint16_t current_y) { _current_y = current_y; }
	/* Saved Map */
	const std::string &get_saved_map() const { return _saved_map; }
	void set_saved_map(const std::string &saved_map) { _saved_map = saved_map; }
	/* Saved X */
	uint16_t get_saved_x() const { return _saved_x; }
	void set_saved_x(uint16_t saved_x) { _saved_x = saved_x; }
	/* Saved Y */
	uint16_t get_saved_y() const { return _saved_y; }
	void set_saved_y(uint16_t saved_y) { _saved_y = saved_y; }
	/* Font */
	uint8_t get_font() const { return _font; }
	void set_font(uint8_t font) { _font = font; }
	/* Show Equip */
	uint8_t get_show_equip() const { return _show_equip; }
	void set_show_equip(uint8_t show_equip) { _show_equip = show_equip; }
	/* Allow Party */
	uint8_t get_allow_party() const { return _allow_party; }
	void set_allow_party(uint8_t allow_party) { _allow_party = allow_party; }

	/**
	 * Owned models
	 */
	/* Status */
	std::shared_ptr<Status> get_status_model() const { return _status_data; }
	void set_status_model(std::shared_ptr<Status> const &status) { _status_data = status; }
	/* Inventory */
	std::shared_ptr<Inventory> get_inventory_model() const { return _inventory; }
	void set_inventory_model(std::shared_ptr<Inventory> const &inv) { _inventory = inv; }

private:
	uint32_t _character_id{0};
	uint32_t _account_id{0};
	uint16_t _slot{0};
	std::string _name{""};
	bool _online{false};
	character_gender_type _gender{CHARACTER_GENDER_MALE};
	uint32_t _deleted_at{0};
	uint32_t _unban_time{0};          ///< Time until character is unbanned.
	uint32_t _pet_id{0};
	uint32_t _homun_id{0};
	uint32_t _elemental_id{0};
	uint32_t _parter_aid{0};
	uint32_t _father_aid{0};
	uint32_t _mother_aid{0};
	uint32_t _child_aid{0};
	uint32_t _party_id{0};
	uint32_t _guild_id{0};
	uint8_t _rename_count{0};
	uint64_t _last_unique_id{0};
	uint8_t _hotkey_row_index{0};
	uint8_t _change_slot_count{0};
	std::string _current_map{""};
	uint16_t _current_x{0}, _current_y{0};
	std::string _saved_map{""};
	uint16_t _saved_x{0}, _saved_y{0};
	uint8_t _font{0};
	uint8_t _show_equip{0};
	uint8_t _allow_party{0};

	std::shared_ptr<Status> _status_data{nullptr};
	std::shared_ptr<Inventory> _inventory{nullptr};
};
}
}
}

#endif // HORIZON_MODELS_CHARACTERS_CHARACTER_HPP
