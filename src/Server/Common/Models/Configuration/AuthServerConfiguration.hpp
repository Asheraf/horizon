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

#ifndef HORIZON_AUTHSERVERCONFIGURATION_HPP
#define HORIZON_AUTHSERVERCONFIGURATION_HPP

#include "Server/Common/Definitions/Horizon.hpp"
#include "Logging.hpp"
#include <cstring>
#include <ctime>

enum login_hash_method
{
	PASS_HASH_NONE   = 0,
	PASS_HASH_MD5    = 1,
	PASS_HASH_SCRYPT = 2
};

struct auth_server_logging_config : public logging
{
	uint32_t get_login_max_tries() const { return login_max_tries; }
	void set_login_max_tries(uint32_t login_max_tries) { auth_server_logging_config::login_max_tries = login_max_tries; }

	time_t get_login_fail_ban_time() const { return login_fail_ban_time; }
	void set_login_fail_ban_time(time_t login_fail_ban_time) { auth_server_logging_config::login_fail_ban_time = login_fail_ban_time; }

	time_t get_login_fail_check_time() const { return login_fail_check_time; }
	void set_login_fail_check_time(time_t login_fail_check_time) { auth_server_logging_config::login_fail_check_time = login_fail_check_time; }

	/* Member Variables */
	uint32_t login_max_tries = 3;                                ///< Max login tries.
	time_t login_fail_ban_time = 300;                            ///< 5 Minutes ban time
	time_t login_fail_check_time = 60;                           ///< Save fail information for 1 minute.
};

struct auth_server_config
{
	/* Pass Hash Method */
	login_hash_method get_pass_hash_method() const { return pass_hash_method; }
	void set_pass_hash_method(login_hash_method pass_hash_method) { auth_server_config::pass_hash_method = pass_hash_method; }
	/* Client Date Format */
	const std::string &get_client_date_format() const { return client_date_format; }
	void set_client_date_format(const std::string &date_format) { auth_server_config::client_date_format = date_format; }
	/* Logs Configuration */
	auth_server_logging_config &get_log_conf() { return logs; }

	/* Member Variables */
	login_hash_method pass_hash_method = PASS_HASH_NONE;                   ///< Password Hashing Method.
	std::string client_date_format = "%Y-%m-%d %H:%M:%S";                    ///< Date format sent to clients.
	/* Authentication Server Logging Configuration */
	auth_server_logging_config logs;
};

#endif // HORIZON_AUTHSERVERCONFIGURATION_HPP
