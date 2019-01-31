#ifndef HORIZON_AUTH_SESSION_AUTHSESSION_HPP
#define HORIZON_AUTH_SESSION_AUTHSESSION_HPP

#include "Core/Networking/Session.hpp"

#include <memory>

class PacketBuffer;
class GameAccount;
class SessionData;

namespace Horizon
{
namespace Auth
{
class PacketHandler;
class AuthSocket;
class AuthSession : public Horizon::Networking::Session<AuthSocket>
{
public:
	AuthSession(std::shared_ptr<AuthSocket> socket);
	~AuthSession();

	/* Packet Handler */
	std::shared_ptr<PacketHandler> get_packet_handler();
	void set_packet_handler(std::shared_ptr<PacketHandler> handler);
	/* Game Account */
	std::shared_ptr<GameAccount> get_game_account();
	void set_game_account(std::shared_ptr<GameAccount> account);
	/* Session Data */
	std::shared_ptr<SessionData> get_session_data();
	void set_session_data(std::shared_ptr<SessionData> session_data);
	/* */
	int get_packet_version(uint16_t packet_id, PacketBuffer buf);
	void update(uint32_t diff);

private:
	std::shared_ptr<PacketHandler> _packet_handler;
	std::shared_ptr<SessionData> _session_data;
	std::shared_ptr<GameAccount> _game_account;
};
}
}
#endif /* HORIZON_AUTH_SESSION_AUTHSESSION_HPP */
