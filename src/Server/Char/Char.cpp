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

#include "Char.hpp"

#include "Core/Logging/Logger.hpp"
#include "Server/Char/Session/CharSession.hpp"
#include "Server/Char/SocketMgr/ClientSocketMgr.hpp"
#include "Server/Common/Models/Configuration/CharServerConfiguration.hpp"

#include <boost/asio.hpp>
#include <boost/make_shared.hpp>
#include <iostream>
#include <sol.hpp>

using namespace std;

using boost::asio::ip::udp;

/**
 * CharMain Constructor
 */
Horizon::Char::CharMain::CharMain() : Server("Char", "config/", "char-server.lua")
{
	//
}

/**
 * CharMain Destructor
 */
Horizon::Char::CharMain::~CharMain()
{
	//
}

#define char_config_error(setting_name, default) \
	CharLog->error("No setting for '{}' in configuration file, defaulting to '{}'.", setting_name, default);

/**
 * Read /config/char-server.yaml
 * @return true on success false on failure.
 */
bool Horizon::Char::CharMain::ReadConfig()
{
	sol::state lua;
	int t_val;
	std::string file_path = general_conf().get_config_file_path() + general_conf().get_config_file_name();

	// Read the file. If there is an error, report it and exit.
	try {
		lua.script_file(file_path);
	} catch(const std::exception &e) {
		CharLog->error("CharMain::ReadConfig: {}.", e.what());
		return false;
	}

	sol::table tbl = lua["server_config"];

	sol::table chtbl = tbl.get<sol::table>("new_character");
	get_char_config().set_start_map(chtbl.get_or("start_map", std::string("new_1-1")));
	get_char_config().set_start_x(chtbl.get_or("start_x", 53));
	get_char_config().set_start_y(chtbl.get_or("start_y", 111));
	get_char_config().set_start_zeny(chtbl.get_or("start_zeny", 0));

	sol::optional<sol::table> maybe_chitbl = chtbl.get<sol::optional<sol::table>>("start_items");

	if (maybe_chitbl) {
		sol::table chitbl = maybe_chitbl.value();
		chitbl.for_each([this](sol::object const &key, sol::object const &value) {
			get_char_config().add_start_item(std::make_pair(key.as<int>(), value.as<int>()));
		});
		if (chitbl.size() < 1) {
			get_char_config().add_start_item(std::make_pair(1201, 1));
			get_char_config().add_start_item(std::make_pair(2301, 1));
		}
	}

	get_char_config().set_character_deletion_time(tbl.get_or("character_deletion_time", 86400));

	sol::table zone_tbl = tbl.get<sol::table>("zone_server");
	get_char_config().set_zone_server_ip(zone_tbl.get_or("ip_address", std::string("127.0.0.1")));
	get_char_config().set_zone_server_port(zone_tbl.get_or("port", 5121));

	/**
	 * Process Configuration that is common between servers.
	 */
	if (!parse_common_configs(tbl))
		return false;

	CharLog->info("Done reading server configurations from '{}'.", file_path);

	return true;
}

#undef char_config_error

/* Initialize Char-Server CLI Commands */
void Horizon::Char::CharMain::initialize_cli_commands()
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
		CharServer->set_shutdown_stage(SHUTDOWN_INITIATED);
		CharServer->set_shutdown_signal(SIGINT);
	}
}

void Horizon::Char::CharMain::initialize_core()
{
	/* Core Signal Handler  */
	boost::asio::signal_set signals(get_io_service(), SIGINT, SIGTERM);
	signals.async_wait(SignalHandler);

	/* Start Character Network */
	ClientSocktMgr->start(get_io_service(),
						  network_conf().get_listen_ip(),
						  network_conf().get_listen_port(),
						  network_conf().get_network_thread_count());

	Server::initialize_core();

	uint32_t diff = general_conf().get_core_update_interval();

	while (get_shutdown_stage() == SHUTDOWN_NOT_STARTED && !general_conf().is_test_run()) {
		process_cli_commands();
		_task_scheduler.Update();
		ClientSocktMgr->update_socket_sessions(diff);
		std::this_thread::sleep_for(std::chrono::microseconds(diff));
	}

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
		CharServer->parse_exec_args(argv, argc);

	/* Read Char Configuration */
	if (!CharServer->ReadConfig())
		exit(SIGTERM); // Stop process if the file can't be read.

	/* Initialize the Common Core */
	CharServer->initialize_core();

	/* Core Cleanup */
	CharLog->info("Server shutting down...");

	return CharServer->general_conf().get_shutdown_signal();
}
