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
