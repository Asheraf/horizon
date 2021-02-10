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

#include "Char.hpp"

#include "Server/Common/SQL/SessionData.hpp"
#include "Core/Logging/Logger.hpp"
#include "Server/Char/SocketMgr/ClientSocketMgr.hpp"

#include <boost/asio.hpp>
#include <boost/make_shared.hpp>
#include <iostream>

#include <sol.hpp>
#include <sqlpp11/sqlpp11.h>

using namespace Horizon::Char;

using namespace std;

/**
 * Char Constructor
 */
CharServer::CharServer()
: Server(), _update_timer(_io_service)
{
	//
}

/**
 * Char Destructor
 */
CharServer::~CharServer()
{
	//
}

#define char_config_error(s, d) \
	HLog(error) << "No setting for '" << s << "' in configuration file, defaulting to '" << d << "'.";

/**
 * Read /config/char-server.yaml
 * @return true on success false on failure.
 */
bool CharServer::read_config()
{
	sol::state lua;
	std::string file_path = general_conf().get_config_file_path().string();

	// Read the file. If there is an error, report it and exit.
	try {
		lua.script_file(file_path);
	} catch(const std::exception &e) {
		HLog(error) << "Char::ReadConfig: " << e.what();
		return false;
	}

	sol::table tbl = lua["horizon_config"];

	sol::table chtbl = tbl.get<sol::table>("new_character");
	config().set_start_map(chtbl.get_or("start_map", std::string("new_1-1")));
	config().set_start_x(chtbl.get_or("start_x", 53));
	config().set_start_y(chtbl.get_or("start_y", 111));
	config().set_start_zeny(chtbl.get_or("start_zeny", 0));

	sol::optional<sol::table> maybe_chitbl = chtbl.get<sol::optional<sol::table>>("start_items");

	if (maybe_chitbl) {
		sol::table chitbl = maybe_chitbl.value();
		chitbl.for_each([this](sol::object const &key, sol::object const &value) {
			config().add_start_item(std::make_pair(key.as<int>(), value.as<int>()));
		});
		if (chitbl.size() < 1) {
			config().add_start_item(std::make_pair(1201, 1));
			config().add_start_item(std::make_pair(2301, 1));
		}
	}

	config().set_character_deletion_time(tbl.get_or("character_deletion_time", 86400));
	config().set_char_hard_delete(tbl.get_or("character_hard_delete", false));

	sol::table zone_tbl = tbl.get<sol::table>("zone_server");
	config().set_zone_server_ip(zone_tbl.get_or("ip_address", std::string("127.0.0.1")));
	config().set_zone_server_port(zone_tbl.get_or("port", 5121));

	config().set_pincode_expiry(tbl.get<uint32_t>("pincode_expiry"));
	
	config().set_pincode_retry(tbl.get<uint8_t>("pincode_max_retry"));

	/**
	 * Process Configuration that is common between servers.
	 */
	if (!parse_common_configs(tbl))
		return false;

	HLog(info) << "Done reading server configurations from '" << file_path << "'.";

	return true;
}

#undef char_config_error

/* Initialize Char-Server CLI Commands */
void CharServer::initialize_cli_commands()
{
	Server::initialize_cli_commands();
}

/**
 * Signal handler for the Char-Server main thread.
 * @param[in|out] error   boost system error code.
 * @param[in]     signal  interrupt signal code
 */
void SignalHandler(const boost::system::error_code &error, int /*signal*/)
{
	if (!error) {
		sChar->set_shutdown_stage(SHUTDOWN_INITIATED);
		sChar->set_shutdown_signal(SIGINT);
	}
}

void CharServer::verify_connected_sessions()
{
	SQL::TableSessionData tsd;
	std::shared_ptr<sqlpp::mysql::connection> conn = sChar->get_db_connection();
	
	(*conn)(remove_from(tsd).where(tsd.current_server == "C" and
		tsd.last_update < std::time(nullptr) - general_conf().session_max_timeout()));

	auto sres = (*conn)(select(count(tsd.game_account_id)).from(tsd).where(tsd.current_server == "C"));

	int32_t count = sres.front().count;

	HLog(info) << count << " connected session(s).";
}

void CharServer::update(uint64_t diff)
{
	process_cli_commands();
	
	_task_scheduler.Update(diff);

	ClientSocktMgr->update_socket_sessions(MAX_CORE_UPDATE_INTERVAL);
	
	if (get_shutdown_stage() == SHUTDOWN_NOT_STARTED && !general_conf().is_test_run()) {
		_update_timer.expires_from_now(boost::posix_time::milliseconds(MAX_CORE_UPDATE_INTERVAL));
		_update_timer.async_wait(std::bind(&CharServer::update, this, MAX_CORE_UPDATE_INTERVAL));
	} else {
		get_io_service().stop();
	}
}

void CharServer::initialize_core()
{
	/* Core Signal Handler  */
	boost::asio::signal_set signals(get_io_service(), SIGINT, SIGTERM);
	signals.async_wait(SignalHandler);

	/* Start Character Network */
	ClientSocktMgr->start(get_io_service(),
						  general_conf().get_listen_ip(),
						  general_conf().get_listen_port(),
						  MAX_NETWORK_THREADS);

	Server::initialize_core();

	_task_scheduler.Schedule(Seconds(60), [this] (TaskContext context) {
		verify_connected_sessions();
		context.Repeat();
	});

	_update_timer.expires_from_now(boost::posix_time::milliseconds(MAX_CORE_UPDATE_INTERVAL));
	_update_timer.async_wait(std::bind(&CharServer::update, this, MAX_CORE_UPDATE_INTERVAL));
	
	get_io_service().run();

	HLog(info) << "Shutdown process initiated...";

	/**
	 * Cancel all pending tasks.
	 */
	_task_scheduler.CancelAll();

	/**
	 * Server shutdown routine begins here...
	 */
	Server::finalize_core();

	/**
	 * Stop all networks
	 */
	ClientSocktMgr->stop_network();

	/* Cancel signal handling. */
	signals.cancel();

	set_shutdown_stage(SHUTDOWN_CLEANUP_COMPLETE);
}

/**
 * Main entry point of the char-server application.
 * @param argc
 * @param argv
 * @return integer of shutdown signal.
 */
int main(int argc, const char * argv[])
{
	/* Parse Command Line Arguments */
	if (argc > 1)
		sChar->parse_exec_args(argv, argc);

	/* Read Char Configuration */
	if (!sChar->read_config())
		exit(SIGTERM); // Stop process if the file can't be read.

	/* Initialize the Common Core */
	sChar->initialize_core();

	/* Core Cleanup */
	HLog(info) << "Server shutting down...";

	return sChar->general_conf().get_shutdown_signal();
}
