//
// Created by SagunKho on 16/01/2018.
//

#ifndef HORIZON_CHAR_H
#define HORIZON_CHAR_H

#include "CharSession.hpp"

#include "Logging/Logger.hpp"
#include "Server/Server.hpp"

#include <string>
#include <Core/Database/MySqlConnection.hpp>

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
private:
	struct {
		bool enabled;
	} logs;
};

#define CharServer CharMain::getInstance()

#endif //HORIZON_CHAR_H
