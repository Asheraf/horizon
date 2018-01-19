//
//  main.h
//  Horizon
//
//  Created by Sagun Khosla on 11/6/17.
//  Copyright © 2017 Horizon. All rights reserved.
//

#ifndef HORIZON_AUTH_HPP
#define HORIZON_AUTH_HPP

#include "AuthSession.hpp"

#include "Core/Database/MySqlConnection.hpp"
#include "Server/Server.hpp"

#include <string>

enum HashingMethods
{
	PASS_HASH_NONE   = 0,
	PASS_HASH_MD5    = 1,
	PASS_HASH_BCRYPT = 2
};

typedef std::vector<uint64_t> OnlineListType;

class AuthMain : public Server
{
public:
	AuthMain();
	~AuthMain();

	static AuthMain *getInstance()
	{
		static AuthMain instance;
		return &instance;
	}

	void PrintHeader();

	bool ReadConfig();

	boost::shared_ptr<MySQLConnection> MySQLBorrow()
	{
		return mysql_pool->borrow();
	}

	void MySQLUnborrow(boost::shared_ptr<MySQLConnection> conn)
	{
		mysql_pool->unborrow(conn);
	}

	/**
	 * Account Online List Getter.
	 * @return
	 */
	std::shared_ptr<OnlineListType> getAccountOnlineList() const;

protected:
	struct {
		enum HashingMethods pass_hash_method = PASS_HASH_NONE;           ///< Password Hashing Method.
		std::string date_format = "%Y-%m-%d %H:%M:%S";                   ///< Date format sent to clients.
		uint32_t client_version = 0;                                     ///< Client version to check. (0 = disabled)

		/**
		 * Authentication Server Logging
		 */
		struct {
			bool enabled = true;                                         ///< Login logging is enabled.
			uint32_t login_max_tries = 3;                                ///< Max login tries.
			time_t login_fail_ban_time = 300;                            ///< 5 Minutes ban time
			time_t login_fail_check_time = 60;                           ///< Save fail information for 1 minute.
		} logs;
	} auth_config;

	/**
	 * List of accounts that are connected.
	 */
	std::shared_ptr<OnlineListType> account_online_list;
};

#define AuthServer AuthMain::getInstance()

#endif /* HORIZON_AUTH_HPP */
