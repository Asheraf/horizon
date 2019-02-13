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

#ifndef HORIZON_GAME_ACOUNT_HPP
#define HORIZON_GAME_ACOUNT_HPP

#include "Server/Common/Server.hpp"
#include "Libraries/BCrypt/BCrypt.hpp"
#include "Server/Common/Models/Character/Character.hpp"

#include <cstdint>
#include <boost/asio/ip/address.hpp>

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

enum game_account_gender_types
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

typedef std::map<uint32_t, std::shared_ptr<Horizon::Models::Character::Character>> AccountCharacterMapType;

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
	bool verify_credentials(Server *server, std::string username, std::string password)
	{
		std::string query = "SELECT `id`, `username`, `gender`, `email`, `group_id`, `state`, `unban_time`, `expiration_time`, UNIX_TIMESTAMP(`last_login`), `last_ip`, DATE_FORMAT(`birth_date`, '%Y-%m-%d'), `character_slots`, `pincode`, `pincode_expiry` FROM `game_accounts` WHERE `username` = ? AND `password` = ?";

		try {
			auto s = server->get_mysql_client()->getSession();
			auto record = s.sql(query).bind(username, password).execute().fetchOne();

			if (record) {
				_id = record[0];
				_username = record[1].get<std::string>();
				std::string account_gender = record[2];

				if (account_gender == "M")
					_gender = ACCOUNT_GENDER_MALE;
				else if (account_gender == "F")
					_gender = ACCOUNT_GENDER_FEMALE;
				else if (account_gender == "NA")
					_gender = ACCOUNT_GENDER_NONE;

				_email = record[3].get<std::string>();
				_group_id = (uint16_t) record[4].get<int>();
				_state = (game_account_state_type) record[5].get<int>();
				_unban_time = record[6].get<int>();

				_expiration_time = record[7].get<int>();

				if (record[8].getType() > 0)
					_last_login = record[8].get<int>();

				_last_ip = record[9].get<std::string>();

				if (record[10].getType() > 0)
					_birth_date = record[10].get<std::string>();

				_character_slots = (uint8_t) record[11].get<int>();
				_pincode = record[12].get<std::string>();
				_pincode_expiry = record[13].get<int>();

				s.close();

				return true;
			}
			s.close();
		} catch (const mysqlx::Error &e) {
			CoreLog->warn("GameAccount::verify_credentials: {}", e.what());
		}

		return false;
	}

	/**
	 * @brief Verifies credentials using the bcrypt password hashing algorithm.
	 * @param[in|out]  server    instance to the server object calling this method.
	 * @param[in]      username  username for the account in question.
	 * @param[in]      password  password for the account in question.
	 * @return true on success, false on failure.
	 */
	bool verify_credentials_bcrypt(Server *server, std::string username, std::string password)
	{
		std::string query = "SELECT `id`, `username`, `password`, `gender`, `email`, `group_id`, `state`, `unban_time`, `expiration_time`, UNIX_TIMESTAMP(`last_login`), `last_ip`, DATE_FORMAT(`birth_date`, '%Y-%m-%d'), `character_slots`, `pincode`, `pincode_expiry` FROM `game_accounts` WHERE username = ?";

		try {
			auto s = server->get_mysql_client()->getSession();
			auto record = s.sql(query).bind(username).execute().fetchOne();
			std::string stored_password = record[2];

			if (record && BCrypt::validate_password(password, stored_password)) {
				_id = record[0];
				set_username(record[1].get<std::string>());
				std::string account_gender = record[3].get<std::string>();

				if (account_gender == "M")
					_gender = ACCOUNT_GENDER_MALE;
				else if (account_gender == "F")
					_gender = ACCOUNT_GENDER_FEMALE;
				else if (account_gender == "NA")
					_gender = ACCOUNT_GENDER_NONE;

				_email = record[4].get<std::string>();
				_group_id = (uint16_t) record[5].get<int>();
				_state = (game_account_state_type) record[6].get<int>();
				_unban_time = record[7].get<int>();

				_expiration_time = record[8].get<int>();

				if (record[9].getType() > 0) // check null
					_last_login = record[9].get<int>();

				_last_ip = record[10].get<std::string>();

				if (record[11].getType() > 0)
					_birth_date = record[11].get<std::string>();

				_character_slots = record[12].get<int>();
				_pincode = record[13].get<std::string>();
				_pincode_expiry = record[14].get<int>();

				s.close();

				return true;
			}
			s.close();
		} catch (const mysqlx::Error &e) {
			CoreLog->warn("GameAccount::verify_credentials_bcrypt: {}", e.what());
		}

		return false;
	}


	/**
	 * @brief Loads the game account from database into memory.
	 * @param[in|out]  server    instance to the server object calling this method.
	 * @param[in]      account_id  id for the account in question.
	 * @return true on success, false on failure.
	 */
	bool load(Server *server, uint32_t account_id)
	{
		std::string query = "SELECT `username`, `gender`, `email`, `group_id`, `state`, `unban_time`, `expiration_time`, UNIX_TIMESTAMP(`last_login`), `last_ip`, DATE_FORMAT(`birth_date`, '%Y-%m-%d'), `character_slots`, `pincode`, `pincode_expiry` FROM `game_accounts` WHERE id = ?";

		try {
			auto s = server->get_mysql_client()->getSession();
			auto record = s.sql(query).bind(account_id).execute().fetchOne();

			if (record) {
				set_id(account_id);
				set_username(record[0].get<std::string>());
				std::string account_gender = record[1].get<std::string>();

				if (account_gender == "M")
					set_gender(ACCOUNT_GENDER_MALE);
				else if (account_gender == "F")
					set_gender(ACCOUNT_GENDER_FEMALE);
				else if (account_gender == "NA")
					set_gender(ACCOUNT_GENDER_NONE);

				set_email(record[2].get<std::string>());
				set_group_id((uint16_t) record[3].get<int>());
				set_state((game_account_state_type) record[4].get<int>());
				set_unban_time(record[5].get<int>());
				set_expiration_time(record[6].get<int>());

				if (record[7].getType() > 0) // check null
					set_last_login(record[7].get<int>());

				set_last_ip(record[8].get<std::string>());

				if (record[9].getType() > 0)
					set_birth_date(record[9].get<std::string>());

				set_character_slots(record[10].get<int>());
				set_pincode(record[11].get<std::string>());
				set_pincode_expiry(record[12].get<int>());

				s.close();
				return true;
			}
			s.close();
		} catch (const mysqlx::Error &e) {
			CoreLog->warn("GameAccount::load: {}", e.what());
		}

		return false;
	}

	/**
	 * @brief Update this model to the database in its current state.
	 * @param[in|out] server   instance of the server object used to borrow mysql connections.
	 */
	void update(Server *server)
	{
		try {
			auto s = server->get_mysql_client()->getSession();
			auto null = mysqlx::Value();
			auto t = s.getDefaultSchema().getTable("game_accounts");
			auto q = t.update()
			.set("gender", get_gender() == ACCOUNT_GENDER_MALE ? "M" : "F")
			.set("email", get_email())
			.set("group_id", get_group_id())
			.set("state", (uint8_t) get_state())
			.set("unban_time", get_unban_time())
			.set("expiration_time", get_expiration_time())
			.set("last_login", mysqlx::internal::expr("FROM_UNIXTIME(" + std::to_string(get_last_login()) + ", '%Y-%m-%d %H:%i:%s')"))
			.set("last_ip", get_last_ip());

			if (get_birth_date().empty())
				q.set("birth_date", null);
			else
				q.set("birth_date", get_birth_date());

			q.set("character_slots", get_character_slots())
				.set("pincode", get_pincode())
				.set("pincode_expiry", get_pincode_expiry());

			q.where("id = :id").bind("id", get_id()).execute();
			s.close();
		} catch (const mysqlx::Error &e) {
			CoreLog->warn("GameAccount::update: {}", e.what());
		}
	}

	/* Account Id */
	uint32_t get_id() const { return _id; }
	void set_id(uint32_t id) { _id = id; }
	/* Username */
	const std::string &get_username() const { return _username; }
	void set_username(const std::string &username) { _username = username; }
	/* Gender */
	game_account_gender_types get_gender() const { return _gender; }
	void set_gender(game_account_gender_types gender) { _gender = gender; }
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
		auto old_character = get_character(character->get_character_id());

		if (old_character != nullptr)
			old_character = character;
		else
			_characters.insert(std::make_pair(character->get_character_id(), character));
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
	game_account_gender_types _gender{ACCOUNT_GENDER_NONE};              ///< Gender
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

#endif // HORIZON_GAME_ACOUNT_HPP
