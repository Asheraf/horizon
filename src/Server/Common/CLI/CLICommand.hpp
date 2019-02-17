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
 * Base Author - Sagun Khosla. (sagunxp@gmail.com)
 *
 * Under a proprietary license this file is not for use
 * or viewing without permission.
 **************************************************/

#ifndef HORIZON_CLICOMMAND_HPP
#define HORIZON_CLICOMMAND_HPP

class Server;

class CLICommand
{
public:
	typedef void (*FinishFunc) (std::shared_ptr<CLICommand> cmd, bool success);

	CLICommand(Server *server, char *command, FinishFunc finish_func)
	: m_Server(server), m_command(command), m_finish_func(finish_func)
	{
		//
	}

	~CLICommand()
	{
	}

	Server *m_Server;                 ///< Instance to the server
	std::string m_command;            ///< Command string.
	FinishFunc m_finish_func;         ///< Completion handler function.
	bool terminal_shutdown_signal;    ///< Terminal shutdown signal.
};
#endif //HORIZON_CLICOMMAND_HPP
