/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 * Copyright (c) 2020- Horizon Dev Team.
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

#include "AuthClientInterface.hpp"

#include "Libraries/Argon2/Argon2.hpp"
#include "Server/Common/SQL/GameAccount.hpp"

#include "Server/Auth/Auth.hpp"
#include "Server/Auth/Packets/AC_ACCEPT_LOGIN.hpp"
#include "Server/Auth/Packets/AC_REFUSE_LOGIN.hpp"

#include <memory>

using namespace Horizon::Auth;

AuthClientInterface::AuthClientInterface(std::shared_ptr<AuthSocket> sock)
: ClientInterface(sock)
{
	
}

AuthClientInterface::~AuthClientInterface()
{
	
}


bool AuthClientInterface::process_login(std::string username, std::string password, uint16_t version, uint16_t client_type)
{
	Argon2 argon2;
	SQL::TableGameAccounts tga;
	AC_ACCEPT_LOGIN acal(get_socket());
	AC_REFUSE_LOGIN acrl(get_socket());
	int pos = 0;
	char block_date[20]{0};
	std::shared_ptr<sqlpp::mysql::connection> conn = sAuth->get_mysql_connection();
	
	if (((pos = username.find("_m")) || (pos = username.find("_f"))) && pos != std::string::npos) {
		enum game_account_gender_type gender = ACCOUNT_GENDER_NONE;
		
		if (username.find("_m")) {
			username = username.substr(0, pos);
			gender = ACCOUNT_GENDER_MALE;
		} else if (username.find("_f")) {
			username = username.substr(0, pos);
			gender = ACCOUNT_GENDER_FEMALE;
		}
		
		std::string salt = sAuth->get_auth_config()._password_salt_mix.c_str();
		std::string hash = argon2.gen_hash(password, salt);
		
		std::shared_ptr<sqlpp::mysql::connection> conn = sAuth->get_mysql_connection();
		
		auto res = (*conn)(select(all_of(tga)).from(tga).where(tga.username == username));
		
		if (res.empty()) {
			HLog(info) << "Recieved connection request for unknown account '" << username << "'.";

			enum game_account_gender_type gender;
			
			HLog(info) << "Creating a new account for user '" << username << "' with password '" << password << "'.";
			
			std::string salt = sAuth->get_auth_config()._password_salt_mix.c_str();
			std::string hash = argon2.gen_hash(password, salt);
			
			HLog(debug) << "Argon2 hash created:" << std::hex << hash;
			
			try {
				auto last_insert_id = (*conn)(insert_into(tga).set(tga.username = username, tga.hash = hash, tga.salt = salt, tga.gender = (gender == (int) ACCOUNT_GENDER_FEMALE ? "F" : "M"),
											 tga.group_id = 0, tga.state = (int) ACCOUNT_STATE_NONE, tga.login_count = 1, tga.last_login = std::chrono::system_clock::now(),
											 tga.last_ip = get_socket()->remote_ip_address(), tga.character_slots = 3));
				uint32_t aid = last_insert_id;
				acal.deliver(aid, aid, 0, gender);
				HLog(info) << "Request for authorization of account '" << username << "' has been granted.";
			} catch (std::exception &error) {
				HLog(error) << error.what();
				acrl.deliver(login_error_codes::ERR_SESSION_CONNECTED, block_date, 0);
				return false;
			}
			
			return true;
		}
		
		HLog(info) << "Account '" << username << "' already exists. Please login without specifying '_m' or '_f' at the end.";
		acrl.deliver(login_error_codes::ERR_SESSION_CONNECTED, block_date, 0);
		return false;
	}
	
	auto res = (*conn)(select(all_of(tga)).from(tga).where(tga.username == username));
	
	if (res.empty()) {
		HLog(info) << "Recieved connection request for unknown account '" << username << "'.";
		acrl.deliver(login_error_codes::ERR_UNREGISTERED_ID, block_date, 0);
		return false;
	}
	
	std::string hash = res.front().hash;
	std::string salt = res.front().salt;
	
	uint32_t aid = res.front().id;
	uint32_t group_id = res.front().group_id;
	uint32_t gender = res.front().gender == "M" ? 0 : 1;
	
	if (argon2.verify(hash, password, salt) == false) {
		HLog(info) << "Incorrect password for account '" << username << "' with password '" << password << "'.";
		acrl.deliver(login_error_codes::ERR_INCORRECT_PASSWORD, block_date, 0);
		return false;
	}
	
	acal.deliver(aid, aid, group_id, gender);
	
	HLog(info) << "Request for authorization of account '" << username << "' has been granted.";
	return true;
}
