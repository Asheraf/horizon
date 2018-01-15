//
// Created by SagunKho on 19/06/2017.
//

#ifndef HORIZON_LOGGER_H
#define HORIZON_LOGGER_H

#include <spdlog/spdlog.h>
#include <iostream>

class Logger
{
public:
	Logger(std::string name, std::string path, uint8_t level, size_t file_size, uint32_t max_files)
	: path(path), _logger(spdlog::get(name))
	{
		//size_t q_size = 4096; //queue size must be power of 2

		//spdlog::set_async_mode(q_size);

		if (_logger == nullptr) {
			std::vector<spdlog::sink_ptr> sinks;
			auto stdout_sink = spdlog::sinks::stdout_sink_mt::instance();

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
			sinks.push_back(std::make_shared<spdlog::sinks::wincolor_sink>(stdout_sink));
#else
			sinks.push_back(std::make_shared<spdlog::sinks::ansicolor_sink>(stdout_sink));
#endif
			sinks.push_back(std::make_shared<spdlog::sinks::rotating_file_sink_mt>(path, file_size, max_files));

			_logger = std::make_shared<spdlog::logger>(name, begin(sinks), end(sinks));
			spdlog::register_logger(_logger);

			_logger->set_level((spdlog::level::level_enum) level);
			_logger->set_pattern("[%T.%e] %n: %v");
		}
	};
	~Logger() { };

	std::shared_ptr<spdlog::logger> get() { return _logger; }

private:
	std::shared_ptr<spdlog::logger> _logger;
	std::string path;
};

static Logger AuthLog("Auth", "logs/auth-server.log", 0, 1024, 1);
static Logger CoreLog("Core", "logs/core.log", 0, 1024, 1);
static Logger DatabaseLog("Database", "logs/database.log", 0, 1024, 1);

#define AuthLog (AuthLog.get())
#define CoreLog (CoreLog.get())
#define DBLog (DatabaseLog.get())

#endif //HORIZON_LOGGER_H
