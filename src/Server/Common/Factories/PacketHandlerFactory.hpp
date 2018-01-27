//
// Created by SagunKho on 27/01/2018.
//

#ifndef HORIZON_PACKETHANDLERFACTORY_HPP
#define HORIZON_PACKETHANDLERFACTORY_HPP

#include "AuthPacketHandler.hpp"
#include "Versions/AuthPacketHandler20170315.hpp"
#include "Versions/AuthPacketHandler20171113.hpp"

class PacketHandlerFactory
{
public:
	PacketHandlerFactory() { };
	~PacketHandlerFactory() { };

	static std::shared_ptr<AuthPacketHandler> CreateAuthPacketHandler(uint32_t packet_version, std::shared_ptr<AuthSession> session)
	{
		switch (packet_version)
		{
		case 20170315:
			return std::make_shared<AuthPacketHandler20170315>(session);
		case 20171113:
			return std::make_shared<AuthPacketHandler20171113>(session);
		default: // return common type.
			return std::make_shared<AuthPacketHandler>(session);
		}
	}
};

#endif //HORIZON_PACKETHANDLERFACTORY_HPP
