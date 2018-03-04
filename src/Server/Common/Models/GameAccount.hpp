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
#include "Core/Database/MySqlConnection.hpp"
#include "Server/Common/Models/Character/Character.hpp"
#include "Server/Common/Base/PacketHandler/InterPackets.hpp"

#include <cstdint>
#include <boost/asio/ip/address.hpp>
#include <cppconn/resultset.h>

namespace Horizon
{
	namespace Models
	{
		namespace Characters
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

enum game_account_state_types
{
	ACCOUNT_STATE_NONE,
	ACCOUNT_STATE_BANNED
};

typedef std::map<uint32_t, std::shared_ptr<Horizon::Models::Characters::Character>> AccountCharacterMapType;

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
	bool VerifyCredentials(Server *server, std::string username, std::string password)
	{
		std::string query = "SELECT * FROM `game_account` WHERE username = ? AND password = ?";
		auto sql = server->MySQLBorrow();
		bool ret = false;

		try {
			sql::PreparedStatement *pstmt = sql->getConnection()->prepareStatement(query);
			pstmt->setString(1, username);
			pstmt->setString(2, password);
			sql::ResultSet *res = pstmt->executeQuery();

			if (res != nullptr && res->next()) {
				/**
				 * Create Game Account Data
				 */
				loadFromResultSet(res);
				ret = true;
			}

			delete res;
			delete pstmt;
		} catch (sql::SQLException &e) {
			DBLog->error("GameAccount::VerifyCredentials: {}", e.what());
		}

		server->MySQLUnborrow(sql);
		return ret;
	}

	/**
	 * @brief Verifies credentials using the bcrypt password hashing algorithm.
	 * @param[in|out]  server    instance to the server object calling this method.
	 * @param[in]      username  username for the account in question.
	 * @param[in]      password  password for the account in question.
	 * @return true on success, false on failure.
	 */
	bool VerifyCredentialsBCrypt(Server *server, std::string username, std::string password)
	{
		std::string query = "SELECT * FROM `game_account` WHERE username = ?";
		auto sql = server->MySQLBorrow();
		bool ret = false;

		try {
			sql::PreparedStatement *pstmt = sql->getConnection()->prepareStatement(query);
			pstmt->setString(1, username);
			sql::ResultSet *res = pstmt->executeQuery();

			if (res != nullptr && res->next()
			    && BCrypt::validatePassword(password, res->getString("password"))) {
				/**
				 * Create Game Account Data
				 */
				loadFromResultSet(res);
				ret = true;
			}

			delete res;
			delete pstmt;
		} catch (sql::SQLException &e) {
			DBLog->error("GameAccount::VerifyCredentialsBCrypt: {}", e.what());
		}

		server->MySQLUnborrow(sql);
		return ret;
	}

	/**
	 * @brief Load data into the model from a result set retrieved from the database.
	 * @param[in] res   instance of sql::ResultSet loaded from the database.
	 */
	void loadFromResultSet(sql::ResultSet *res)
	{
		id = res->getInt("id");
		username = res->getString("username");
		std::string account_gender = res->getString("gender");

		if (account_gender == "M")
			gender = ACCOUNT_GENDER_MALE;
		else if (account_gender == "F")
			gender = ACCOUNT_GENDER_FEMALE;
		else if (account_gender == "NA")
			gender = ACCOUNT_GENDER_NONE;

		email = res->getString("email");
		group_id = (uint16_t) res->getInt("group_id");
		state = (game_account_state_types) res->getInt("state");
		unban_time = res->getInt64("unban_time");

		expiration_time = res->getInt64("expiration_time");
		last_login = res->getInt64("last_login");
		last_ip = res->getString("last_ip");
		birth_date = res->getString("birth_date");
		character_slots = (uint8_t) res->getInt("character_slots");
		pincode = res->getInt("pincode");
		pincode_expiry = res->getInt64("pincode_expiry");
	}

	/**
	 * @brief Update this model to the database in its current state.
	 * @param[in|out] server   instance of the server object used to borrow mysql connections.
	 */
	void update(Server *server)
	{
		auto sql = server->MySQLBorrow();

		std::string query = "UPDATE `game_account` "
		"SET `gender` = ?, `email` = ?, `group_id` = ?, `state` = ?, `unban_time` = ?, "
		"`expiration_time` = ?, `last_login` = ?, `last_ip` = ?, `birth_date` = ?, `character_slots` = ?, `pincode` = ?, `pincode_expiry` = ?) WHERE `id` = ?";

		try {
			sql::PreparedStatement *pstmt = sql->getConnection()->prepareStatement(query);
			pstmt->setString(1, (getGender() == ACCOUNT_GENDER_MALE ? "M" : "F"));
			pstmt->setString(2, getEmail());
			pstmt->setInt(3, getState());
			pstmt->setInt(4, getUnbanTime());
			pstmt->setInt(5, getExpirationTime());
			pstmt->setInt(6, getLastLogin());
			pstmt->setString(7, getLastIP());
			pstmt->setString(8, getBirthDate());
			pstmt->setInt(9, getCharacterSlots());
			pstmt->setString(10, getPincode());
			pstmt->setInt(11, getPincodeExpiry());
			pstmt->setInt(12, getID());
			pstmt->executeUpdate();
			delete pstmt;
		} catch (sql::SQLException &e) {
			DBLog->error("SQLException: {}", e.what());
		}

		server->MySQLUnborrow(sql);
	}

	/**
	 * Serialize into struct.
	 */
	GameAccount &operator >> (PACKET_INTER_GAME_ACCOUNT &pkt)
	{
		pkt.id = getID();
		strncpy(pkt.username, getUsername().c_str(), MAX_USERNAME_LENGTH);
		pkt.gender = getGender();
		strncpy(pkt.email, getEmail().c_str(), MAX_EMAIL_LENGTH);
		pkt.group_id = getGroupID();
		pkt.state = getState();
		pkt.unban_time = getUnbanTime();
		pkt.expiration_time = getExpirationTime();
		pkt.last_login = getLastLogin();
		strncpy(pkt.last_ip, getLastIP().c_str(), MAX_IP_ADDRESS_STR_LENGTH);
		strncpy(pkt.birth_date, getBirthDate().c_str(), MAX_BIRTHDATE_STRING_LENGTH);
		pkt.character_slots = getCharacterSlots();
		strncpy(pkt.pincode, getPincode().c_str(), MAX_PINCODE_STRING_LENGTH);
		pkt.pincode_expiry = getPincodeExpiry();
		return *this;
	}

	/**
	 * Serialize into struct.
	 */
	GameAccount &operator << (PACKET_INTER_GAME_ACCOUNT &pkt)
	{
		setID(pkt.id);
		setUsername(pkt.username);
		setGender(static_cast<game_account_gender_types>(pkt.gender));
		setEmail(pkt.email);
		setGroupID(pkt.group_id);
		setState(static_cast<game_account_state_types>(pkt.state));
		setUnbanTime(pkt.unban_time);
		setExpirationTime(pkt.expiration_time);
		setLastLogin(pkt.last_login);
		setLastIP(pkt.last_ip);
		setBirthDate(pkt.birth_date);
		setCharacterSlots(pkt.character_slots);
		setPincode(pkt.pincode);
		setPincodeExpiry(pkt.pincode_expiry);
		return *this;
	}

	/* Account Id */
	uint32_t getID() const { return id; }
	void setID(uint32_t id) { GameAccount::id = id; }
	/* Username */
	const std::string &getUsername() const { return username; }
	void setUsername(const std::string &username) { GameAccount::username = username; }
	/* Gender */
	game_account_gender_types getGender() const { return gender; }
	void setGender(game_account_gender_types gender) { GameAccount::gender = gender; }
	/* Email */
	const std::string &getEmail() const { return email; }
	void setEmail(const std::string &email) { GameAccount::email = email; }
	/* Group ID */
	uint16_t getGroupID() const { return group_id; }
	void setGroupID(uint16_t group_id) { GameAccount::group_id = group_id; }
	/* State */
	game_account_state_types getState() const { return state; }
	void setState(game_account_state_types state) { GameAccount::state = state; }
	/* Unban Time */
	time_t getUnbanTime() const { return unban_time; }
	void setUnbanTime(time_t unban_time) { GameAccount::unban_time = unban_time; }
	/* Expiration Time */
	time_t getExpirationTime() const { return expiration_time; }
	void setExpirationTime(time_t expiration_time) { GameAccount::expiration_time = expiration_time; }
	/* Last Login */
	time_t getLastLogin() const { return last_login; }
	void setLastLogin(time_t last_login) { GameAccount::last_login = last_login; }
	/* Last IP */
	const std::string &getLastIP() const { return last_ip; }
	void setLastIP(const std::string &last_ip) { GameAccount::last_ip = last_ip; }
	/* Birth Date */
	const std::string &getBirthDate() const { return birth_date; }
	void setBirthDate(const std::string &birth_date) { GameAccount::birth_date = birth_date; }
	/* Character Slots */
	uint8_t getCharacterSlots() const { return character_slots; }
	void setCharacterSlots(uint8_t character_slots) { GameAccount::character_slots = character_slots; }
	/* Pincode */
	const std::string &getPincode() const { return pincode; }
	void setPincode(const std::string &pincode) { GameAccount::pincode = pincode; }
	/* Pincode Expiry */
	time_t getPincodeExpiry() const { return pincode_expiry; }
	void setPincodeExpiry(time_t pincode_expiry) { GameAccount::pincode_expiry = pincode_expiry; }

	/**
	 * @brief Retrieve a character from the account's character list.
	 * @param[in] id of the character to be retrieved.
	 */
	const std::shared_ptr<Horizon::Models::Characters::Character> getCharacter(uint32_t id)
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
	void addCharacter(std::shared_ptr<Horizon::Models::Characters::Character> character)
	{
		auto old_character = getCharacter(character->getCharacterID());

		if (old_character != nullptr)
			old_character = character;
		else
			_characters.insert(std::make_pair(character->getCharacterID(), character));
	}

	/**
	 * @brief Remove a character from the account's character list.
	 * @param[in] id of the character to remove.
	 */
	void removeCharacter(uint32_t id)
	{
		auto character = getCharacter(id);

		if (character != nullptr)
			_characters.erase(id);
	}

	/**
	 * @brief retrieve a std::map of all characters from the account.
	 */
	const AccountCharacterMapType &getAllCharacters() const { return _characters; }
	
private:
	uint32_t id{};                                   ///< Account Id
	std::string username{};                          ///< Username
	game_account_gender_types gender{ACCOUNT_GENDER_NONE};              ///< Gender
	std::string email{};                             ///< e-mail (by default: a@a.com)
	uint16_t group_id{};                             ///< player group id
	game_account_state_types state{};                ///< packet 0x006a value + 1 (0: complete OK)
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
