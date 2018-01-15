//
//  AuthSession.hpp
//  Horizon
//
//  Created by SagunKho on 18/06/2017.
//  Copyright © 2017 Horizon. All rights reserved.
//

#ifndef HORIZON_AUTHSESSION_HPP
#define HORIZON_AUTHSESSION_HPP

#include "Core/Networking/Socket.hpp"
#include "Core/Networking/Buffer/MessageBuffer.hpp"

#include "../Packet.hpp"

#include <stdio.h>
#include <boost/asio/ip/tcp.hpp>

class AuthHandle;

using boost::asio::ip::tcp;

class AuthSession : public Socket<AuthSession>
{
	friend class AuthMain;
	typedef Socket<AuthSession> AuthSocket;
public:
	AuthSession(tcp::socket &&socket);
	~AuthSession() { }

	void Start() override;
	bool Update() override;

	void SendPacket(ByteBuffer& packet);

	AuthHandle *HandleRequest() { return _handle; }

protected:
	void ReadHandler() override;
	void OnClose() override;
	AuthHandle *_handle;
};

#endif /* HORIZON_AUTHSESSION_HPP */
