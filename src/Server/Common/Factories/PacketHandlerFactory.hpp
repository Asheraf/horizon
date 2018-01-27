//
// Created by SagunKho on 27/01/2018.
//

#ifndef HORIZON_PACKETHANDLERFACTORY_HPP
#define HORIZON_PACKETHANDLERFACTORY_HPP

#include "PacketHandler.hpp"
#include "Versions/PacketHandler20170315.hpp"
#include "Versions/PacketHandler20171113.hpp"

class PacketHandlerFactory
{
public:
	PacketHandlerFactory() { };
	~PacketHandlerFactory() { };

	static std::shared_ptr<Horizon::Auth::PacketHandler> CreateAuthPacketHandler(int packet_version, std::shared_ptr<Horizon::Auth::AuthSession> session)
	{
		switch (packet_version)
		{
		case 20170315:
			return std::make_shared<Horizon::Auth::PacketHandler20170315>(session);
		case 20171113:
			return std::make_shared<Horizon::Auth::PacketHandler20171113>(session);
		default: // return common type.
			return std::make_shared<Horizon::Auth::PacketHandler>(session);
		}
	}
};

#endif //HORIZON_PACKETHANDLERFACTORY_HPP
