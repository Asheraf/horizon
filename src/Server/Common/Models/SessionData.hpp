//
// Created by SagunKho on 19/01/2018.
//

#ifndef HORIZON_SESSIONDATA_H
#define HORIZON_SESSIONDATA_H

#include <Server/Common/Horizon.hpp>
#include <ctime>

class SessionData
{
public:
	SessionData() { };
	~SessionData() { };

	int getAuthCode() const
	{
		return auth_code;
	}

	void setAuthCode(int auth_code)
	{
		SessionData::auth_code = auth_code;
	}

	int getClientVersion() const
	{
		return client_version;
	}

	void setClientVersion(int client_version)
	{
		SessionData::client_version = client_version;
	}

	uint8_t getClientType() const
	{
		return client_type;
	}

	void setClientType(uint8_t client_type)
	{
		SessionData::client_type = client_type;
	}

private:
	int auth_code;
	int client_version;
	uint8_t client_type;
};

#endif //HORIZON_SESSIONDATA_H
