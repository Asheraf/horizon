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

#ifndef HORIZON_USER_H
#define HORIZON_USER_H

#include "Server/Common/Server.hpp"
#include "Libraries/BCrypt/BCrypt.hpp"
#include "Core/Database/MySqlConnection.hpp"

#include <cstdint>
#include <boost/asio/ip/address.hpp>
#include <cppconn/resultset.h>

enum game_account_gender_types
{
	ACCOUNT_MALE,
	ACCOUNT_FEMALE,
	ACCOUNT_SERVER
};

enum game_account_state_types
{
	ACCOUNT_STATE_NONE,
	ACCOUNT_STATE_BANNED
};

class GameAccount
{
public:
	GameAccount()
	{
	}

	~GameAccount()
	{
	}

	bool VerifyCredentials(Server *server, std::string username, std::string password)
	{
		std::string query = "SELECT * FROM game_account WHERE username = ? AND password = ?";
		auto sql = server->MySQLBorrow();
		bool ret = false;

		try {
			sql::PreparedStatement *pstmt = sql->sql_connection->prepareStatement(query);
			pstmt->setString(1, username);
			pstmt->setString(2, password);
			sql::ResultSet *res = pstmt->executeQuery();

			if (res != nullptr && res->next()) {
				/**
				 * Create Game Account Data
				 */
				LoadFromDatabase(res);
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

	bool VerifyCredentialsBCrypt(Server *server, std::string username, std::string password)
	{
		std::string query = "SELECT * FROM game_account WHERE username = ?";
		auto sql = server->MySQLBorrow();
		bool ret = false;

		try {
			sql::PreparedStatement *pstmt = sql->sql_connection->prepareStatement(query);
			pstmt->setString(1, username);
			sql::ResultSet *res = pstmt->executeQuery();

			if (res != nullptr && res->next()
			    && BCrypt::validatePassword(password, res->getString("password"))) {
				/**
				 * Create Game Account Data
				 */
				LoadFromDatabase(res);
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

	void LoadFromDatabase(sql::ResultSet *res)
	{
		id = res->getInt("id");
		username = res->getString("username");
		gender = (game_account_gender_types) res->getInt("gender");
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

	uint32_t getId() const
	{
		return id;
	}

	void setId(uint32_t id)
	{
		GameAccount::id = id;
	}

	const std::string &getUsername() const
	{
		return username;
	}

	void setUsername(const std::string &username)
	{
		GameAccount::username = username;
	}

	game_account_gender_types getGender() const
	{
		return gender;
	}

	void setGender(game_account_gender_types gender)
	{
		GameAccount::gender = gender;
	}

	const std::string &getEmail() const
	{
		return email;
	}

	void setEmail(const std::string &email)
	{
		GameAccount::email = email;
	}

	uint16_t getGroupId() const
	{
		return group_id;
	}

	void setGroupId(uint16_t group_id)
	{
		GameAccount::group_id = group_id;
	}

	game_account_state_types getState() const
	{
		return state;
	}

	void setState(game_account_state_types state)
	{
		GameAccount::state = state;
	}

	time_t getUnbanTime() const
	{
		return unban_time;
	}

	void setUnbanTime(time_t unban_time)
	{
		GameAccount::unban_time = unban_time;
	}

	time_t getExpirationTime() const
	{
		return expiration_time;
	}

	void setExpirationTime(time_t expiration_time)
	{
		GameAccount::expiration_time = expiration_time;
	}

	time_t getLastLogin() const
	{
		return last_login;
	}

	void setLastLogin(time_t last_login)
	{
		GameAccount::last_login = last_login;
	}

	const std::string &getLastIp() const
	{
		return last_ip;
	}

	void setLastIp(const std::string &last_ip)
	{
		GameAccount::last_ip = last_ip;
	}

	const std::string &getBirthDate() const
	{
		return birth_date;
	}

	void setBirthDate(const std::string &birth_date)
	{
		GameAccount::birth_date = birth_date;
	}

	uint8_t getCharacterSlots() const
	{
		return character_slots;
	}

	void setCharacterSlots(uint8_t character_slots)
	{
		GameAccount::character_slots = character_slots;
	}

	const std::string &getPincode() const
	{
		return pincode;
	}

	void setPincode(const std::string &pincode)
	{
		GameAccount::pincode = pincode;
	}

	time_t getPincodeExpiry() const
	{
		return pincode_expiry;
	}

	void setPincodeExpiry(time_t pincode_expiry)
	{
		GameAccount::pincode_expiry = pincode_expiry;
	}

private:
	uint32_t id;                                   ///< Account Id
	std::string username;                          ///< Username
	game_account_gender_types gender;              ///< Gender
	std::string email;                             ///< e-mail (by default: a@a.com)
	uint16_t group_id;                             ///< player group id
	game_account_state_types state;                ///< packet 0x006a value + 1 (0: complete OK)
	time_t unban_time;                             ///< (timestamp): ban time limit of the account (0 = no ban)
	time_t expiration_time;                        ///< (timestamp): validity limit of the account (0 = unlimited)
	time_t last_login;                             ///< date+time of last successful login
	std::string last_ip;                           ///< save of last IP of connection
	std::string birth_date;                        ///< assigned birth date (format: YYYY-MM-DD, default: 0000-00-00)
	uint8_t character_slots;                       ///< this accounts maximum character slots (maximum is limited to MAX_CHARS define in char server)
	std::string pincode;                           ///< pincode value
	time_t pincode_expiry;                         ///< (timestamp): last time of pincode change
};

#endif //HORIZON_USER_H
