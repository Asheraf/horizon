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
 * Base Author - Sxyz (sagunxp@gmail.com)
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
#include "Server/Common/Models/Character/Character.hpp"

#include <cstdint>
#include <boost/asio/ip/address.hpp>

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

#define SCRYPT_DERIVED_HASH_SIZE 64
#define SCRYPT_SALT_SIZE 8
#define SCRYPT_COMPUTATION_COST 2048
#define SCRYPT_BLOCK_SIZE 8
#define SCRYPT_PARALLELIZATION 16

typedef std::map<uint32_t, std::shared_ptr<Horizon::Models::Character::Character>> AccountCharacterMapType;

namespace Horizon
{
namespace Models
{
class GameAccount
{
public:
	GameAccount()
	{
	}

	~GameAccount()
	{
	}

	/**
	 * @brief Verifies credentials the plain text password checking.
	 * @param[in|out]  server    instance to the server object calling this method.
	 * @param[in]      username  username for the account in question.
	 * @param[in]      password  password for the account in question.
	 * @return true on success, false on failure.
	 */
	bool verify_credentials(Server *server, std::string username, std::string password);

	/**
	 * @brief Verifies credentials using the scrypt password hashing algorithm.
	 * @param[in|out]  server    instance to the server object calling this method.
	 * @param[in]      username  username for the account in question.
	 * @param[in]      password  password for the account in question.
	 * @return true on success, false on failure.
	 */
	bool verify_credentials_scrypt(Server *server, std::string username, std::string password);


	/**
	 * @brief Loads the game account from database into memory.
	 * @param[in|out]  server    instance to the server object calling this method.
	 * @param[in]      account_id  id for the account in question.
	 * @return true on success, false on failure.
	 */
	bool load(Server *server, uint32_t account_id);

	/**
	 * @brief Update this model to the database in its current state.
	 * @param[in|out] server   instance of the server object used to borrow mysql connections.
	 */
	void update(Server *server);

	/* Account Id */
	uint32_t get_id() const { return _id; }
	void set_id(uint32_t id) { _id = id; }
	/* Username */
	const std::string &get_username() const { return _username; }
	void set_username(const std::string &username) { _username = username; }
	/* Gender */
	game_account_gender_type get_gender() const { return _gender; }
	void set_gender(game_account_gender_type gender) { _gender = gender; }
	/* Email */
	const std::string &get_email() const { return _email; }
	void set_email(const std::string &email) { _email = email; }
	/* Group ID */
	uint16_t get_group_id() const { return _group_id; }
	void set_group_id(uint16_t group_id) { _group_id = group_id; }
	/* State */
	game_account_state_type get_state() const { return _state; }
	void set_state(game_account_state_type state) { _state = state; }
	/* Unban Time */
	time_t get_unban_time() const { return _unban_time; }
	void set_unban_time(time_t unban_time) { _unban_time = unban_time; }
	/* Expiration Time */
	time_t get_expiration_time() const { return _expiration_time; }
	void set_expiration_time(time_t expiration_time) { _expiration_time = expiration_time; }
	/* Last Login */
	time_t get_last_login() const { return _last_login; }
	void set_last_login(time_t last_login) { _last_login = last_login; }
	/* Last IP */
	const std::string &get_last_ip() const { return _last_ip; }
	void set_last_ip(const std::string &last_ip) { _last_ip = last_ip; }
	/* Birth Date */
	const std::string &get_birth_date() const { return _birth_date; }
	void set_birth_date(const std::string &birth_date) { _birth_date = birth_date; }
	/* Character Slots */
	uint8_t get_character_slots() const { return _character_slots; }
	void set_character_slots(uint8_t character_slots) { _character_slots = character_slots; }
	/* Pincode */
	const std::string &get_pincode() const { return _pincode; }
	void set_pincode(const std::string &pincode) { _pincode = pincode; }
	/* Pincode Expiry */
	time_t get_pincode_expiry() const { return _pincode_expiry; }
	void set_pincode_expiry(time_t pincode_expiry) { _pincode_expiry = pincode_expiry; }

	/**
	 * @brief Retrieve a character from the account's character list.
	 * @param[in] id of the character to be retrieved.
	 */
	const std::shared_ptr<Horizon::Models::Character::Character> get_character(uint32_t id)
	{
		auto it = _characters.find(id);

		if (it != _characters.end())
			return it->second;

		return nullptr;
	}

	/**
	 * @brief Add a character to the account's character list.
	 * @param[in|out] character  shared_ptr to the character model to be added.
	 */
	void add_character(std::shared_ptr<Horizon::Models::Character::Character> character)
	{
		auto old_character = get_character(character->get_id());

		if (old_character != nullptr)
			old_character = character;
		else
			_characters.insert(std::make_pair(character->get_id(), character));
	}

	/**
	 * @brief Remove a character from the account's character list.
	 * @param[in] id of the character to remove.
	 */
	void remove_character(uint32_t id)
	{
		auto character = get_character(id);

		if (character != nullptr)
			_characters.erase(id);
	}

	/**
	 * @brief retrieve a std::map of all characters from the account.
	 */
	const AccountCharacterMapType &get_characters() const { return _characters; }

private:
	uint32_t _id{};                                   ///< Account Id
	std::string _username{};                          ///< Username
	game_account_gender_type _gender{ACCOUNT_GENDER_NONE};              ///< Gender
	std::string _email{};                             ///< e-mail (by default: a@a.com)
	uint16_t _group_id{};                             ///< player group id
	game_account_state_type _state{};                ///< packet 0x006a value + 1 (0: complete OK)
	time_t _unban_time{};                             ///< (timestamp): ban time limit of the account (0 = no ban)
	time_t _expiration_time{};                        ///< (timestamp): validity limit of the account (0 = unlimited)
	time_t _last_login{};                             ///< date+time of last successful login
	std::string _last_ip{};                           ///< save of last IP of connection
	std::string _birth_date{};                        ///< assigned birth date (format: YYYY-MM-DD, default: 0000-00-00)
	uint8_t _character_slots{};                       ///< this accounts maximum character slots (maximum is limited to MAX_CHARS define in char server)
	std::string _pincode{};                           ///< pincode value
	time_t _pincode_expiry{};                         ///< (timestamp): last time of pincode change

	/* Account Characters */
	AccountCharacterMapType _characters;
};
}
}

#endif // HORIZON_GAME_ACOUNT_HPP
