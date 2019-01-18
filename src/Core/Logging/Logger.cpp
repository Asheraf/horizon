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

#include "Logger.hpp"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"

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
