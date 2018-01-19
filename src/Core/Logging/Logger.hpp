//
// Created by SagunKho on 19/06/2017.
//

#ifndef HORIZON_LOGGER_H
#define HORIZON_LOGGER_H

#include <spdlog/spdlog.h>

enum log_main_types
{
	LOG_MAIN_AUTH,
	LOG_MAIN_CHAR,
	LOG_MAIN_CORE,
	LOG_MAIN_DATABASE,
	LOG_MAIN_NETWORK
};

class Logger
{
public:
	Logger()
	{
	};

	~Logger()
	{
	}

	static Logger *getInstance()
	{
		static Logger instance;
		return &instance;
	}

	std::shared_ptr<spdlog::logger> registerLogger(log_main_types type, std::string name, std::string path, uint8_t level, size_t file_size, uint32_t max_files)
	{
		std::shared_ptr<spdlog::logger> _logger = spdlog::get(name);

		if (_logger == nullptr) {
			std::vector<spdlog::sink_ptr> sinks;
			auto stdout_sink = spdlog::sinks::stdout_sink_mt::instance();

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
			sinks.push_back(std::make_shared<spdlog::sinks::wincolor_stdout_sink_mt>());
#else
			sinks.push_back(std::make_shared<spdlog::sinks::stdout_sink_mt>());
#endif
			//sinks.push_back(std::make_shared<spdlog::sinks::rotating_file_sink_mt>(name, path, file_size, max_files, false));

			_logger = std::make_shared<spdlog::logger>(name, begin(sinks), end(sinks));
			spdlog::register_logger(_logger);

			_logger->set_level((spdlog::level::level_enum) level);
			_logger->set_pattern("[%T.%e] %n: %v");
		}

		return _logger;
	}
};

#define AuthLog Logger().getInstance()->registerLogger(LOG_MAIN_AUTH, "Auth", "logs/auth-server.log", 0, 102400, 1)
#define CharLog Logger().getInstance()->registerLogger(LOG_MAIN_CHAR, "Char", "logs/char-server.log", 0, 102400, 1)
#define CoreLog Logger().getInstance()->registerLogger(LOG_MAIN_CORE, "Core", "logs/core.log", 0, 102400, 1)
#define DBLog Logger().getInstance()->registerLogger(LOG_MAIN_DATABASE, "Database", "logs/database.log", 0, 102400, 1)

#endif //HORIZON_LOGGER_H
