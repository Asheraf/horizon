#include "AuthSession.hpp"

#include "Server/Auth/PacketHandler/PacketHandler.hpp"
#include "Server/Auth/PacketHandler/PacketHandlerFactory.hpp"
#include "Server/Auth/Socket/AuthSocket.hpp"
#include "Server/Common/Models/GameAccount.hpp"
#include "Server/Common/Models/SessionData.hpp"
#include "Server/Common/PacketBuffer.hpp"

using namespace Horizon::Auth;

AuthSession::AuthSession(std::shared_ptr<AuthSocket> socket)
: Horizon::Networking::Session<AuthSocket>(socket)
{
	//
}

AuthSession::~AuthSession()
{
	//
}

/* Packet Handler */
std::shared_ptr<PacketHandler> AuthSession::get_packet_handler() { return _packet_handler; }
void AuthSession::set_packet_handler(std::shared_ptr<PacketHandler> handler) { _packet_handler.swap(handler); }
/* Game Account */
std::shared_ptr<GameAccount> AuthSession::get_game_account() { return _game_account; }
void AuthSession::set_game_account(std::shared_ptr<GameAccount> account) { _game_account.swap(account); }
/* Session Data */
std::shared_ptr<SessionData> AuthSession::get_session_data() { return _session_data; }
void AuthSession::set_session_data(std::shared_ptr<SessionData> session_data) { _session_data.swap(session_data); }

int AuthSession::get_packet_version(uint16_t packet_id, PacketBuffer buf)
{
	switch (packet_id)
	{
	case CA_LOGIN:
	{
		PACKET_CA_LOGIN pkt;
		buf >> pkt;
		return pkt.version;
	}
	default:
		return 0;
	}
}

void AuthSession::update(uint32_t /*diff*/)
{
	std::shared_ptr<PacketBuffer> buf;

	while ((buf = get_socket()->get_packet_recv_queue().try_pop())) {
		/**
		 * Devise a suitable packet handler
		 * based on the client's packet version.
		 */
		if (buf->getOpCode() == CA_LOGIN)
			set_packet_handler(PacketHandlerFactory::create_auth_packet_handler(get_socket(), get_packet_version(buf->getOpCode(), *buf)));

		if (_packet_handler == nullptr) {
			AuthLog->error("Packet handler was null!");
			return;
		}

		_packet_handler->handle_received_packet(*buf);
	}
}
