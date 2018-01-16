//
// Created by SagunKho on 16/01/2018.
//

#ifndef HORIZON_CHAR_H
#define HORIZON_CHAR_H

#include "CharSession.h"
#include "CharHandle.h"

#include "Logging/Logger.hpp"
#include "Server/Server.hpp"

#include <string>

class CharMain : public Server
{
public:
	CharMain();
	~CharMain();

	static CharMain *getInstance()
	{
		static CharMain instance;
		return &instance;
	}

	void PrintHeader();

	bool ReadConfig();

	struct network_configuration &getNetConf() { return netconf; }

	/* Configuration Retrieval Methods */
	std::string getConfigFileName() { return config_file_name; }
	bool isLoggingEnabled() { return log.enabled; }

	// Test Run
	void setTestRun() { minimal = true; }
	bool isTestRun() { return minimal; }


protected:
	/* Configuration */
	struct network_configuration netconf;                            ///< Network Configuration information.
	std::string config_file_name;                                    ///< Configuration File name.
	uint32_t client_version = 0;                                     ///< Client version to check. (0 = disabled)
	struct {
		bool enabled = true;                                         ///< Login logging is enabled.
	} log;
	bool minimal;
};

#define CharServer CharMain::getInstance()

#endif //HORIZON_CHAR_H
