//
// Created by SagunKho on 16/01/2018.
//

#include "CharHandle.h"
#include "CharSession.h"
#include "Core/Logging/Logger.hpp"
#include "Utilities/Tokenizer.h"

CharHandle::CharHandle()
{
	InitHandlers();
}

CharHandle::~CharHandle()
{

}

bool CharHandle::HandleIncomingPacket(CharSession *session, PacketBuffer &packet)
{
	uint16_t opCode = packet.getOpCode();
	CharPacketHandler func = nullptr;

	if (opCode < MIN_CHAR_PACKETS || opCode > MAX_CHAR_PACKETS) {
		CharLog->trace("Unknown packet with ID received: {0:x}", opCode);
		return false;
	}

	/* Call the function handling */
	if ((func = handlers[opCode]) != nullptr)
		(this->*func)(packet);

	return true;
}

void CharHandle::InitHandlers()
{
	// Insert Handlers.
}

