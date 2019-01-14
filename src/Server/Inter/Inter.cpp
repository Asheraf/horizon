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

#include "Inter.hpp"
#include "Server/Inter/SocketMgr/ClientSocketMgr.hpp"

#include <boost/asio.hpp>
#include <iostream>
#include <boost/make_shared.hpp>
#include <libconfig.h++>

using namespace std;
using boost::asio::ip::udp;

/**
 * Inter Main server constructor.
 */
Horizon::Inter::InterMain::InterMain() : Server("Inter", "config/", "inter-server.conf")
{
}

/**
 * Inter Main server destructor.
 */
Horizon::Inter::InterMain::~InterMain()
{
}

/**
 * Read /config/inter-server.yaml
  * @return true on success, false on failure.
  */
bool Horizon::Inter::InterMain::ReadConfig()
{
	libconfig::Config cfg;
	std::string tmp_string;
	std::string file_path = general_conf().get_config_file_path() + general_conf().get_config_file_name();

	// Read the file. If there is an error, report it and exit.
	try {
		cfg.readFile(file_path.c_str());
	} catch(const libconfig::FileIOException &fioex) {
		InterLog->error("I/O error while reading file '{}'.", file_path);
		return false;
	} catch(const libconfig::ParseException &pex) {
		InterLog->error("Parse error at {}:{} - {}", pex.getFile(), pex.getLine(), pex.getError());
		return false;
	}

	if (cfg.lookupValue("password", tmp_string))
		network_conf().set_inter_server_password(tmp_string);

	/**
	 * Process Configuration that is common between servers.
	 */
	if (!parse_common_configs(cfg))
		return false;

	InterLog->info("Done reading {} configurations in '{}'.", cfg.getRoot().getLength(), file_path);

	return true;
}

bool Horizon::Inter::InterMain::CLICmd_SendAuthPacket()
{
	return true;
}
/**
 * Initialize Inter-Server CLI Commands.
 */
void Horizon::Inter::InterMain::initialize_cli_commands()
{
	Server::initialize_cli_commands();
}

/**
 * Signal Handler for the Inter-Server's main thread.
 * @param error
 */
void SignalHandler(const boost::system::error_code &error, int /*signalNumber*/)
{
	if (!error) {
		InterServer->shutdown(SIGINT);
	}
}

void Horizon::Inter::InterMain::initialize_core()
{

	/**
	 * Core Signal Handler
	 */
	boost::asio::signal_set signals(get_io_service(), SIGINT, SIGTERM);
	// Set signal handler for callbacks.
	// Set signal handlers (this must be done before starting io_service threads,
	// because otherwise they would unblock and exit)
	signals.async_wait(SignalHandler);

	// Start Interacter Network
	ClientSocktMgr->start(get_io_service(),
						  network_conf().get_listen_ip(),
						  network_conf().get_listen_port(),
						  network_conf().get_network_thread_count());
	
	Server::initialize_core();

	// Main Runtime Routine
	while (!is_shutting_down() && !general_conf().is_test_run()) {
		process_cli_commands();
		std::this_thread::sleep_for(std::chrono::milliseconds(general_conf().get_core_update_interval()));
	}

	/**
	 * Server shutdown routine begins here...
	 * Join various threads.
	 */
	if (!general_conf().is_test_run())
		m_CLIThread.join();

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
 * @return
 */
int main(int argc, const char * argv[])
{
	if (argc > 1)
		InterServer->parse_exec_args(argv, argc);

	/*
	 * Read Configuration Settings for
	 * the Interacter Server.
	 */
	if (!InterServer->ReadConfig())
		exit(SIGTERM); // Stop process if the file can't be read.

	/**
	 * Initialize the Common Core
	 */
	InterServer->initialize_core();

	/*
	 * Core Cleanup
	 */
	InterLog->info("Server shutting down...");

	return InterServer->general_conf().get_shutdown_signal();
}
