//
// Created by SagunKho on 16/01/2018.
//

#ifndef HORIZON_CHARHANDLE_H
#define HORIZON_CHARHANDLE_H

#include "CharPackets.h"
#include "Char.h"

#include <boost/asio.hpp>

class CharSession;

typedef void (CharHandle::*CharPacketHandler) (PacketBuffer &packet);

class CharHandle
{
public:
	CharHandle();
	~CharHandle();
	bool HandleIncomingPacket(CharSession *session, PacketBuffer &packet);
	void HandleLoginRequest(PacketBuffer &packet);
	void InitHandlers();

private:
	std::unordered_map<uint16_t, CharPacketHandler> handlers;
};

#endif //HORIZON_CHARHANDLE_H
