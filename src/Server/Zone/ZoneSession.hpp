/**           _   _            _
 *          | | | |          (_)
 *          | |_| | ___  _ __ _ _______  _ __
 *          |  _  |/ _ \| '__| |_  / _ \| '_ \
 *          | | | | (_) | |  | |/ / (_) | | | |
 *          \_| |_/\___/|_|  |_/___\___/|_| |_|
 *
 * This file is part of Horizon (c).
 * Copyright (c) 2018 Horizon Dev Team.
 *
 * Base Author - Sagun Khosla. (sagunxp@gmail.com)
 *
 * Under a proprietary license this file is not for use
 * or viewing without permission.
 ****************************************************/

#ifndef HORIZON_ZONE_ZONESESSION_H
#define HORIZON_ZONE_ZONESESSION_H

#include "Core/Networking/Socket.hpp"
#include "Core/Networking/Buffer/MessageBuffer.hpp"

#include "Common/PacketBuffer.hpp"

#include <cstdio>
#include <boost/asio/ip/tcp.hpp>

using boost::asio::ip::tcp;

namespace Horizon
{
namespace Zone
{
class ZoneSession : public Socket<ZoneSession>
{
	friend class ZoneMain;
	typedef Socket<ZoneSession> ZoneSocket;
	typedef void (ZoneSession::*ZonePacketHandler) (PacketBuffer &pkt);
public:
	ZoneSession(std::shared_ptr<tcp::socket> socket);
	~ZoneSession() { }

	void Start() override;
	bool Update() override;

protected:
	void ReadHandler() override;
	void OnClose() override;
};
}
}

#endif //HORIZON_ZONE_ZONESESSION_H
