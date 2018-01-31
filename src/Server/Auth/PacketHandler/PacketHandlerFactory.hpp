//
// Created by SagunKho on 27/01/2018.
//

#ifndef HORIZON_AUTH_PACKETHANDLERFACTORY_HPP
#define HORIZON_AUTH_PACKETHANDLERFACTORY_HPP

#include "PacketHandler.hpp"
#include "InterPacketHandler.hpp"
#include "Versions/PacketHandler20170315.hpp"
#include "Versions/PacketHandler20171113.hpp"

namespace Horizon
{
namespace Auth
{
class PacketHandlerFactory
{
public:
	PacketHandlerFactory() { };
	~PacketHandlerFactory() { };

	static std::shared_ptr<PacketHandler> CreateAuthPacketHandler(int packet_version, std::shared_ptr<AuthSession> session)
	{
		switch (packet_version)
		{
		case 20170315:
			return std::make_shared<PacketHandler20170315>(session);
		case 20171113:
			return std::make_shared<PacketHandler20171113>(session);
		default: // return common type.
			return std::make_shared<PacketHandler>(session);
		}
	}

	static std::shared_ptr<InterPacketHandler> CreateInterPacketHandler(std::shared_ptr<AuthSession> session)
	{
		return std::make_shared<InterPacketHandler>(session);
	}
};
}
}

#endif //HORIZON_AUTH_PACKETHANDLERFACTORY_HPP
