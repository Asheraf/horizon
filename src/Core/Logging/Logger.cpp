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

#include "Logger.hpp"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <iostream>

Logger::Logger()
{
	//
}

Logger::~Logger()
{
	//
}

std::shared_ptr<spdlog::logger> Logger::registerLogger(std::string name, std::string path, uint8_t level, size_t file_size, uint32_t max_files)
{
	std::shared_ptr<spdlog::logger> _logger = spdlog::get(name);

	if (_logger == nullptr) {
		std::vector<spdlog::sink_ptr> sinks;

		sinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
		sinks.push_back(std::make_shared<spdlog::sinks::rotating_file_sink_mt>(path, file_size, max_files));

		_logger = std::make_shared<spdlog::logger>(name, begin(sinks), end(sinks));
		spdlog::register_logger(_logger);

		_logger->set_level((spdlog::level::level_enum) level);
		_logger->set_pattern("[%T.%e] %n: %v");
	}

	return _logger;
}
