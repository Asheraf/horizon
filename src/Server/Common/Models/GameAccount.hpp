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
#include "Server/Common/Base/PacketHandler/InterPackets.hpp"

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
		std::string query = "SELECT `id`, `username`, `gender`, `email`, `group_id`, `state`, `unban_time`, `expiration_time`, UNIX_TIMESTAMP(`last_login`), `last_ip`, DATE_FORMAT(`birth_date`, '%Y-%m-%d'), `character_slots`, `pincode`, `pincode_expiry` FROM `game_account` WHERE `username` = ? AND `password` = ?";

		try {
			auto s = server->get_mysql_client()->getSession();
			auto record = s.sql(query).bind(username, password).execute().fetchOne();

			if (record) {
				id = record[0];
				username = record[1].get<std::string>();
				std::string account_gender = record[2];

				if (account_gender == "M")
					gender = ACCOUNT_GENDER_MALE;
				else if (account_gender == "F")
					gender = ACCOUNT_GENDER_FEMALE;
				else if (account_gender == "NA")
					gender = ACCOUNT_GENDER_NONE;

				email = record[3].get<std::string>();
				group_id = (uint16_t) record[4].get<int>();
				state = (game_account_state_type) record[5].get<int>();
				unban_time = record[6].get<int>();

				expiration_time = record[7].get<int>();

				if (record[8].getType() > 0)
					last_login = record[8].get<int>();

				last_ip = record[9].get<std::string>();

				if (record[10].getType() > 0)
					birth_date = record[10].get<std::string>();

				character_slots = (uint8_t) record[11].get<int>();
				pincode = record[12].get<std::string>();
				pincode_expiry = record[13].get<int>();
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
		std::string query = "SELECT `id`, `username`, `password`, `gender`, `email`, `group_id`, `state`, `unban_time`, `expiration_time`, UNIX_TIMESTAMP(`last_login`), `last_ip`, DATE_FORMAT(`birth_date`, '%Y-%m-%d'), `character_slots`, `pincode`, `pincode_expiry` FROM `game_account` WHERE username = ?";

		try {
			auto s = server->get_mysql_client()->getSession();
			auto record = s.sql(query).bind(username).execute().fetchOne();
			std::string stored_password = record[2];

			if (record && BCrypt::validate_password(password, stored_password)) {
				id = record[0];
				username = record[1].get<std::string>();
				std::string account_gender = record[3].get<std::string>();

				if (account_gender == "M")
					gender = ACCOUNT_GENDER_MALE;
				else if (account_gender == "F")
					gender = ACCOUNT_GENDER_FEMALE;
				else if (account_gender == "NA")
					gender = ACCOUNT_GENDER_NONE;

				email = record[4].get<std::string>();
				group_id = (uint16_t) record[5].get<int>();
				state = (game_account_state_type) record[6].get<int>();
				unban_time = record[7].get<int>();

				expiration_time = record[8].get<int>();

				if (record[9].getType() > 0) // check null
					last_login = record[9].get<int>();

				last_ip = record[10].get<std::string>();

				if (record[11].getType() > 0)
					birth_date = record[11].get<std::string>();

				character_slots = record[12].get<int>();
				pincode = record[13].get<std::string>();
				pincode_expiry = record[14].get<int>();
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
	 * @brief Update this model to the database in its current state.
	 * @param[in|out] server   instance of the server object used to borrow mysql connections.
	 */
	void update(Server *server)
	{
		std::string query = "UPDATE `game_account` "
		"SET `gender` = ?, `email` = ?, `group_id` = ?, `state` = ?, `unban_time` = ?, "
		"`expiration_time` = ?, `last_login` = FROM_UNIXTIME(?), `last_ip` = ?, `birth_date` = FROM_UNIXTIME(?), `character_slots` = ?, `pincode` = ?, `pincode_expiry` = ?) WHERE `id` = ?";

		try {
			auto s = server->get_mysql_client()->getSession();
			s.sql(query)
				.bind(get_gender() == ACCOUNT_GENDER_MALE ? "M" : "F",
					  get_email(),
					  (uint8_t) get_state(),
					  get_unban_time(),
					  get_expiration_time(),
					  get_last_login(),
					  get_last_ip(),
					  get_birthdate(),
					  get_character_slots(),
					  get_pincode(),
					  get_pincode_expiry(),
					  get_id())
				.execute();
			s.close();
		} catch (const mysqlx::Error &e) {
			CoreLog->warn("GameAccount::update: {}", e.what());
		}
	}

	/**
	 * Serialize into struct.
	 */
	GameAccount &operator >> (PACKET_INTER_GAME_ACCOUNT &pkt)
	{
		pkt.id = get_id();
		strncpy(pkt.username, get_username().c_str(), MAX_USERNAME_LENGTH);
		pkt.gender = get_gender();
		strncpy(pkt.email, get_email().c_str(), MAX_EMAIL_LENGTH);
		pkt.group_id = get_group_id();
		pkt.state = get_state();
		pkt.unban_time = get_unban_time();
		pkt.expiration_time = get_expiration_time();
		pkt.last_login = get_last_login();
		strncpy(pkt.last_ip, get_last_ip().c_str(), MAX_IP_ADDRESS_STR_LENGTH);
		strncpy(pkt.birth_date, get_birthdate().c_str(), MAX_BIRTHDATE_STRING_LENGTH);
		pkt.character_slots = get_character_slots();
		strncpy(pkt.pincode, get_pincode().c_str(), MAX_PINCODE_STRING_LENGTH);
		pkt.pincode_expiry = get_pincode_expiry();
		return *this;
	}

	/**
	 * Serialize into struct.
	 */
	GameAccount &operator << (PACKET_INTER_GAME_ACCOUNT &pkt)
	{
		set_id(pkt.id);
		set_username(pkt.username);
		set_gender(static_cast<game_account_gender_types>(pkt.gender));
		set_email(pkt.email);
		set_group_id(pkt.group_id);
		set_state(static_cast<game_account_state_type>(pkt.state));
		set_unban_time(pkt.unban_time);
		set_expiration_time(pkt.expiration_time);
		set_last_login(pkt.last_login);
		set_last_ip(pkt.last_ip);
		set_birthdate(pkt.birth_date);
		set_character_slots(pkt.character_slots);
		set_pincode(pkt.pincode);
		set_pincode_expiry(pkt.pincode_expiry);
		return *this;
	}

	/* Account Id */
	uint32_t get_id() const { return id; }
	void set_id(uint32_t id) { GameAccount::id = id; }
	/* Username */
	const std::string &get_username() const { return username; }
	void set_username(const std::string &username) { GameAccount::username = username; }
	/* Gender */
	game_account_gender_types get_gender() const { return gender; }
	void set_gender(game_account_gender_types gender) { GameAccount::gender = gender; }
	/* Email */
	const std::string &get_email() const { return email; }
	void set_email(const std::string &email) { GameAccount::email = email; }
	/* Group ID */
	uint16_t get_group_id() const { return group_id; }
	void set_group_id(uint16_t group_id) { GameAccount::group_id = group_id; }
	/* State */
	game_account_state_type get_state() const { return state; }
	void set_state(game_account_state_type state) { GameAccount::state = state; }
	/* Unban Time */
	time_t get_unban_time() const { return unban_time; }
	void set_unban_time(time_t unban_time) { GameAccount::unban_time = unban_time; }
	/* Expiration Time */
	time_t get_expiration_time() const { return expiration_time; }
	void set_expiration_time(time_t expiration_time) { GameAccount::expiration_time = expiration_time; }
	/* Last Login */
	time_t get_last_login() const { return last_login; }
	void set_last_login(time_t last_login) { GameAccount::last_login = last_login; }
	/* Last IP */
	const std::string &get_last_ip() const { return last_ip; }
	void set_last_ip(const std::string &last_ip) { GameAccount::last_ip = last_ip; }
	/* Birth Date */
	const std::string &get_birthdate() const { return birth_date; }
	void set_birthdate(const std::string &birth_date) { GameAccount::birth_date = birth_date; }
	/* Character Slots */
	uint8_t get_character_slots() const { return character_slots; }
	void set_character_slots(uint8_t character_slots) { GameAccount::character_slots = character_slots; }
	/* Pincode */
	const std::string &get_pincode() const { return pincode; }
	void set_pincode(const std::string &pincode) { GameAccount::pincode = pincode; }
	/* Pincode Expiry */
	time_t get_pincode_expiry() const { return pincode_expiry; }
	void set_pincode_expiry(time_t pincode_expiry) { GameAccount::pincode_expiry = pincode_expiry; }

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
	const AccountCharacterMapType &get_all_characters() const { return _characters; }
	
private:
	uint32_t id{};                                   ///< Account Id
	std::string username{};                          ///< Username
	game_account_gender_types gender{ACCOUNT_GENDER_NONE};              ///< Gender
	std::string email{};                             ///< e-mail (by default: a@a.com)
	uint16_t group_id{};                             ///< player group id
	game_account_state_type state{};                ///< packet 0x006a value + 1 (0: complete OK)
	time_t unban_time{};                             ///< (timestamp): ban time limit of the account (0 = no ban)
	time_t expiration_time{};                        ///< (timestamp): validity limit of the account (0 = unlimited)
	time_t last_login{};                             ///< date+time of last successful login
	std::string last_ip{};                           ///< save of last IP of connection
	std::string birth_date{};                        ///< assigned birth date (format: YYYY-MM-DD, default: 0000-00-00)
	uint8_t character_slots{};                       ///< this accounts maximum character slots (maximum is limited to MAX_CHARS define in char server)
	std::string pincode{};                           ///< pincode value
	time_t pincode_expiry{};                         ///< (timestamp): last time of pincode change

	/* Account Characters */
	AccountCharacterMapType _characters;
};

#endif // HORIZON_GAME_ACOUNT_HPP
