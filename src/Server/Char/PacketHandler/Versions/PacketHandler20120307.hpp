//
//  PacketHandler20120307.hpp
//  char
//
//  Created by SagunKho on 08/02/2018.
//

#ifndef PacketHandler20120307_hpp
#define PacketHandler20120307_hpp

#include <stdio.h>

#include "Server/Char/PacketHandler/PacketHandler.hpp"

class PacketBuffer;

namespace Horizon
{
namespace Char
{
namespace PacketVer20120307
{
enum packets
{
	CHAR_CREATE        = 0x970,
};
#pragma pack(push, 1)
struct PACKET_CHAR_CREATE : public Packet
{
	PACKET_CHAR_CREATE() : Packet(Horizon::Char::PacketVer20120307::CHAR_CREATE) {}
	// S 0970 <name>.24B <slot>.B <hair color>.W <hair style>.W
	char name[MAX_CHAR_NAME_LENGTH]{0};
	uint8_t slot{0};
	uint16_t hair_color{0};
	uint16_t hair_style{0};
};
#pragma pack(pop)
}
}
}

namespace Horizon
{
namespace Char
{
class Session;
class PacketHandler20120307 : public PacketHandler
{
public:
	explicit PacketHandler20120307(std::shared_ptr<Session> session);
	virtual ~PacketHandler20120307();

	void InitializeHandlers();
	void Handle_CHAR_CREATE(PacketBuffer &buf);
};
}
}
#endif /* PacketHandler20120307_hpp */
