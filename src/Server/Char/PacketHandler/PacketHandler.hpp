//
// Created by SagunKho on 31/01/2018.
//

#ifndef HORIZON_PACKETHANDLER_HPP
#define HORIZON_PACKETHANDLER_HPP

#include <memory>

class PacketBuffer;

namespace Horizon
{
namespace Char
{
class CharSession;
class PacketHandler
{
public:
	explicit PacketHandler(std::shared_ptr<CharSession> session);
	virtual ~PacketHandler();

	template <class T>
	void SendPacket(T pkt);
	void SendPacket(PacketBuffer &buf, std::size_t size);
	/**
	 *
	 */
	bool HandleIncomingPacket(PacketBuffer &packet);
private:
};
}
}

#endif //HORIZON_PACKETHANDLER_HPP
