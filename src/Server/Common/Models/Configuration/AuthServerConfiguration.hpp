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

#ifndef HORIZON_AUTHSERVERCONFIGURATION_H
#define HORIZON_AUTHSERVERCONFIGURATION_H

#include "Common/Horizon.hpp"
#include "Logging.hpp"
#include <cstring>
#include <ctime>

enum HashingMethods
{
	PASS_HASH_NONE   = 0,
	PASS_HASH_MD5    = 1,
	PASS_HASH_BCRYPT = 2
};

struct auth_server_logging_config : public logging
{
	uint32_t getLoginMaxTries() const { return login_max_tries; }
	void setLoginMaxTries(uint32_t login_max_tries) { auth_server_logging_config::login_max_tries = login_max_tries; }

	time_t getLoginFailBanTime() const { return login_fail_ban_time; }
	void setLoginFailBanTime(time_t login_fail_ban_time) { auth_server_logging_config::login_fail_ban_time = login_fail_ban_time; }

	time_t getLoginFailCheckTime() const { return login_fail_check_time; }
	void setLoginFailCheckTime(time_t login_fail_check_time) { auth_server_logging_config::login_fail_check_time = login_fail_check_time; }

	/* Member Variables */
	uint32_t login_max_tries = 3;                                ///< Max login tries.
	time_t login_fail_ban_time = 300;                            ///< 5 Minutes ban time
	time_t login_fail_check_time = 60;                           ///< Save fail information for 1 minute.
};

struct auth_server_config
{
	/* Pass Hash Method */
	HashingMethods getPassHashMethod() const { return pass_hash_method; }
	void setPassHashMethod(HashingMethods pass_hash_method) { auth_server_config::pass_hash_method = pass_hash_method; }
	/* Client Date Format */
	const std::string &getClientDateFormat() const { return client_date_format; }
	void setClientDateFormat(const std::string &date_format) { auth_server_config::client_date_format = date_format; }
	/* Allowed Client Version */
	uint32_t getAllowedClientVersion() const { return allowed_client_version; }
	void setAllowedClientVersion(uint32_t client_version) { auth_server_config::allowed_client_version = client_version; }
	/* Logs Configuration */
	auth_server_logging_config &getLogConf() { return logs; }

	/* Member Variables */
	enum HashingMethods pass_hash_method = PASS_HASH_NONE;                   ///< Password Hashing Method.
	std::string client_date_format = "%Y-%m-%d %H:%M:%S";                   ///< Date format sent to clients.
	uint32_t allowed_client_version = 0;                                    ///< Client version to check. (0 = disabled)
	/* Authentication Server Logging Configuration */
	struct auth_server_logging_config logs;
};

#endif //HORIZON_AUTHSERVERCONFIGURATION_H
