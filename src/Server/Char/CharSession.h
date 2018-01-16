//
// Created by SagunKho on 16/01/2018.
//

#ifndef HORIZON_CHARSESSION_H
#define HORIZON_CHARSESSION_H


#include "Core/Networking/Socket.hpp"
#include "Core/Networking/Buffer/MessageBuffer.hpp"

#include "../Packet.hpp"

#include <cstdio>
#include <boost/asio/ip/tcp.hpp>

class CharHandle;

using boost::asio::ip::tcp;

class CharSession : public Socket<CharSession>
{
	friend class CharMain;
	typedef Socket<CharSession> CharSocket;
public:
	CharSession(tcp::socket &&socket);
	~CharSession() { }

	void Start() override;
	bool Update() override;

	void SendPacket(ByteBuffer& packet);

	CharHandle *HandleRequest() { return _handle; }

protected:
	void ReadHandler() override;
	void OnClose() override;
	CharHandle *_handle;
};

#endif //HORIZON_CHARSESSION_H
