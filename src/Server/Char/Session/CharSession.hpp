#ifndef HORIZON_CHAR_SESSION_CHARSESSION_HPP
#define HORIZON_CHAR_SESSION_CHARSESSION_HPP

#include "Core/Networking/Session.hpp"

#include <memory>

namespace Horizon
{
	namespace Models
	{
		namespace Character
		{
			class Character;
		}
	}
}

using namespace Horizon::Models::Character;

class PacketBuffer;
class GameAccount;
class SessionData;

namespace Horizon
{
namespace Char
{
class CharSocket;
class PacketHandler;
class CharSession : public Horizon::Networking::Session<CharSocket>
{
public:
	CharSession(std::shared_ptr<CharSocket> socket);

	~CharSession();

	/* Packet Handler */
	std::shared_ptr<PacketHandler> get_packet_handler();
	void set_packet_handler(std::shared_ptr<PacketHandler> handler);
	/* Character */
	std::shared_ptr<Character> get_character();
	void set_character(std::shared_ptr<Character> character);
	/* Game Account */
	std::shared_ptr<GameAccount> get_game_account();
	void set_game_account(std::shared_ptr<GameAccount> account);
	/* Session Data */
	std::shared_ptr<SessionData> get_session_data();
	void set_session_data(std::shared_ptr<SessionData> session_data);

	void handle_new_connection(PacketBuffer &buf);
	void update(uint32_t diff);

private:
	std::shared_ptr<PacketHandler> _packet_handler;
	std::shared_ptr<Character> _character;
	std::shared_ptr<GameAccount> _game_account;
	std::shared_ptr<SessionData> _session_data;
};
}
}
#endif /* HORIZON_CHAR_SESSION_CHARSESSION_HPP */
