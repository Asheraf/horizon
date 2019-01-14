#ifndef HORIZON_AUTH_SESSION_INTERSESSION_HPP
#define HORIZON_AUTH_SESSION_INTERSESSION_HPP

#include "Core/Networking/Session.hpp"

#include <memory>

namespace Horizon
{
namespace Auth
{
class InterPacketHandler;
class InterSocket;
class InterSession : public Horizon::Networking::Session<InterSocket>
{
public:
	InterSession(std::shared_ptr<InterSocket> socket);
	~InterSession();

	/* Packet Handler */
	std::shared_ptr<InterPacketHandler> get_packet_handler();
	void set_packet_handler(std::shared_ptr<InterPacketHandler> handler);

	void update(uint32_t diff);

private:
	std::shared_ptr<InterPacketHandler> _packet_handler;

};
}
}

#endif /* HORIZON_AUTH_SESSION_INTERSESSION_HPP */
