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

#ifndef HORIZON_LOGGER_H
#define HORIZON_LOGGER_H

#include <cstring>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/rotating_file_sink.h>

class Logger
{
public:
	Logger();

	~Logger();

	static Logger *getInstance()
	{
		static Logger instance;
		return &instance;
	}

	std::shared_ptr<spdlog::logger> registerLogger(std::string name, std::string /*path*/, uint8_t level, size_t /*file_size*/, uint32_t /*max_files*/);
};

#define InterLog Logger().getInstance()->registerLogger("Inter", "logs/inter-server.log", 0, 102400, 1)
#define AuthLog Logger().getInstance()->registerLogger("Auth", "logs/auth-server.log", 0, 102400, 1)
#define CharLog Logger().getInstance()->registerLogger("Char", "logs/char-server.log", 0, 102400, 1)
#define ZoneLog Logger().getInstance()->registerLogger("Zone", "logs/zone-server.log", 0, 102400, 1)
#define CoreLog Logger().getInstance()->registerLogger("Core", "logs/core.log", 0, 102400, 1)
#define DBLog Logger().getInstance()->registerLogger("Database", "logs/database.log", 0, 102400, 1)

#endif //HORIZON_LOGGER_H
