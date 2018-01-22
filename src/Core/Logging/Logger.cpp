//
// Created by SagunKho on 23/01/2018.
//

#include "Logger.hpp"

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

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
		sinks.push_back(std::make_shared<spdlog::sinks::wincolor_stdout_sink_mt>());
#else
		sinks.push_back(std::make_shared<spdlog::sinks::ansicolor_stdout_sink_mt>());
#endif
		sinks.push_back(std::make_shared<spdlog::sinks::rotating_file_sink_mt>(path, file_size, max_files));

		_logger = std::make_shared<spdlog::logger>(name, begin(sinks), end(sinks));
		spdlog::register_logger(_logger);

		_logger->set_level((spdlog::level::level_enum) level);
		_logger->set_pattern("[%T.%e] %n: %v");
	}

	return _logger;
}