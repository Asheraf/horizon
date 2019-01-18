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
