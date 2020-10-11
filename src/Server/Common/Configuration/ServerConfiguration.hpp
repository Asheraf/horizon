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

#ifndef HORIZON_SERVERCONFIGURATION_H
#define HORIZON_SERVERCONFIGURATION_H

#include <string>
#include <boost/filesystem.hpp>
#include <vector>

struct general_server_configuration
{
	/* Minimal Load for Test Run */
	bool is_test_run() const { return minimal; }
	void set_test_run() { this->minimal = true; }
	/* Configuration File Path */
	const boost::filesystem::path &get_config_file_path() const { return _config_file_path; }
	void set_config_file_path(const boost::filesystem::path &path) { _config_file_path = path; }
	/* Shut Down Signal */
	int get_shutdown_signal() const { return shutdown_signal; }
	void set_shutdown_signal(int shutdown_signal) { this->shutdown_signal = shutdown_signal; }
    /* Listen IP */
    const std::string &get_listen_ip() const { return _listen_ip; }
    void set_listen_ip(const std::string &listen_ip) { _listen_ip = listen_ip; }
    /* Listen Port */
    uint16_t get_listen_port() const { return _listen_port; }
    void set_listen_port(uint16_t listen_port) { _listen_port = listen_port; }

	bool minimal{false};
    
    const std::string &get_db_host() const { return _db_host; }
    void set_db_host(std::string &&host) { _db_host = host; }
    
    const std::string &get_db_user() const { return _db_user; }
    void set_db_user(std::string &&user) { _db_user = user; }
    
    const std::string &get_db_pass() const { return _db_pass; }
    void set_db_pass(std::string &&pass) { _db_pass = pass; }
    
    const std::string &get_db_database() const { return _db_database; }
    void set_db_database(std::string &&database) { _db_database = database; }
    
    const uint16_t &get_db_port() const { return _db_port; }
    void set_db_port(uint16_t port) { _db_port = port; }

    boost::filesystem::path _config_file_path{""};
	
    int shutdown_signal;    ///< Shutdown signal.

    std::string _listen_ip; ///< Listen IP
    uint16_t _listen_port;  ///< Listen Port Number
    
    std::string _db_host, _db_user, _db_pass, _db_database;
    uint16_t _db_port{3306};
};

#endif //HORIZON_SERVERCONFIGURATION_H
