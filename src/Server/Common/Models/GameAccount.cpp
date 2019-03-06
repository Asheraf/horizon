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

#include "GameAccount.hpp"
#include <cryptlib.h>
#include <secblock.h>
#include <scrypt.h>
#include <hex.h>
#include <files.h>

using namespace Horizon::Models;

bool GameAccount::verify_credentials(Server *server, std::string username, std::string password)
{
	std::string query = "SELECT `id`, `username`, `gender`, `email`, `group_id`, `state`, `unban_time`, `expiration_time`, UNIX_TIMESTAMP(`last_login`), `last_ip`, DATE_FORMAT(`birth_date`, '%Y-%m-%d'), `character_slots`, `pincode`, `pincode_expiry` FROM `game_accounts` WHERE `username` = ? AND `hash` = ?";

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

bool GameAccount::verify_credentials_scrypt(Server *server, std::string username, std::string password)
{
	using namespace CryptoPP;

	std::string query = "SELECT `id`, `username`, `hash`, `salt`, `gender`, `email`, `group_id`, `state`, `unban_time`, `expiration_time`, UNIX_TIMESTAMP(`last_login`), `last_ip`, DATE_FORMAT(`birth_date`, '%Y-%m-%d'), `character_slots`, `pincode`, `pincode_expiry` FROM `game_accounts` WHERE username = ?";

	try {
		SecByteBlock derived(SCRYPT_DERIVED_HASH_SIZE);
		Scrypt scrypt;
		byte *passb = nullptr;
		word64 cost = SCRYPT_COMPUTATION_COST, block_size = SCRYPT_BLOCK_SIZE, parallelization = SCRYPT_PARALLELIZATION;

		auto s = server->get_mysql_client()->getSession();
		auto record = s.sql(query).bind(username).execute().fetchOne();

		std::string hash, stored_password = record[2], salt = record[3];

		passb = new byte[password.size() + 1];
		passb[password.size()] = '\0';

		password.copy((char *) passb, password.size());

		AlgorithmParameters params = MakeParameters("Cost", cost)
		("BlockSize", block_size)("Parallelization", parallelization)
		("Salt", ConstByteArrayParameter(salt));

		scrypt.DeriveKey(derived, derived.size(), passb, password.size() + 1, params);
		StringSource(derived, derived.size(), true, new HexEncoder(new StringSink(hash)));

		delete[] passb;

		if (record && stored_password.compare(hash) == 0) {
			_id = record[0];
			set_username(record[1].get<std::string>());
			std::string account_gender = record[4].get<std::string>();

			if (account_gender == "M")
				_gender = ACCOUNT_GENDER_MALE;
			else if (account_gender == "F")
				_gender = ACCOUNT_GENDER_FEMALE;
			else if (account_gender == "NA")
				_gender = ACCOUNT_GENDER_NONE;

			_email = record[5].get<std::string>();
			_group_id = (uint16_t) record[6].get<int>();
			_state = (game_account_state_type) record[7].get<int>();
			_unban_time = record[8].get<int>();

			_expiration_time = record[9].get<int>();

			if (record[10].getType() > 0) // check null
				_last_login = record[10].get<int>();

			_last_ip = record[11].get<std::string>();

			if (record[12].getType() > 0)
				_birth_date = record[12].get<std::string>();

			_character_slots = record[13].get<int>();
			_pincode = record[14].get<std::string>();
			_pincode_expiry = record[15].get<int>();

			s.close();

			return true;
		}
		s.close();
	} catch (const mysqlx::Error &e) {
		CoreLog->warn("GameAccount::verify_credentials_scrypt: {}", e.what());
	}

	return false;
}

bool GameAccount::load(Server *server, uint32_t account_id)
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

void GameAccount::update(Server *server)
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
