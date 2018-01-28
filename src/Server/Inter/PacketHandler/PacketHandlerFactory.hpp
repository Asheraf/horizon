//
// Created by SagunKho on 27/01/2018.
//

#ifndef HORIZON_INTER_PACKETHANDLERFACTORY_HPP
#define HORIZON_INTER_PACKETHANDLERFACTORY_HPP

#include "PacketHandler.hpp"

namespace Horizon
{
namespace Inter
{
class PacketHandlerFactory
{
public:
	PacketHandlerFactory() { };
	~PacketHandlerFactory() { };

	static std::shared_ptr<PacketHandler> CreatePacketHandler(std::shared_ptr<InterSession> session)
	{
		return std::make_shared<PacketHandler>(session);
	}
};
}
}

#endif //HORIZON_INTER_PACKETHANDLERFACTORY_HPP
