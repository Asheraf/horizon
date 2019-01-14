#include "InterSession.hpp"
#include "Server/Zone/PacketHandler/InterPacketHandler.hpp"
#include "Server/Zone/PacketHandler/PacketHandlerFactory.hpp"
#include "Server/Zone/Socket/InterSocket.hpp"

using namespace Horizon::Zone;

InterSession::InterSession(std::shared_ptr<InterSocket> socket)
: Session(socket),
  _packet_handler(PacketHandlerFactory::create_inter_packet_handler(socket))
{
	PacketBuffer initial_buffer;
	_packet_handler->receive_and_handle(initial_buffer);
}

InterSession::~InterSession()
{
	//
}

std::shared_ptr<InterPacketHandler> InterSession::get_packet_handler() { return _packet_handler; }
void InterSession::set_packet_handler(std::shared_ptr<InterPacketHandler> handler) { _packet_handler.swap(handler); }

void InterSession::update(uint32_t diff)
{
	//
}
