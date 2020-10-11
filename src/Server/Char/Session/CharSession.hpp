#ifndef HORIZON_CHAR_SESSION_CHARSESSION_HPP
#define HORIZON_CHAR_SESSION_CHARSESSION_HPP

#include "Core/Networking/Session.hpp"
#include "Server/Common/Configuration/ServerConfiguration.hpp"

#include "Server/Common/Models/Character/Character.hpp"
#include "Server/Common/Models/GameAccount.hpp"
#include "Server/Common/Models/SessionData.hpp"

#include <memory>

class PacketBuffer;

namespace Horizon
{
	namespace Models
	{
		class GameAccount;
		class SessionData;
	}
}

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
	std::shared_ptr<Horizon::Models::Character::Character> get_char_model();
	void set_char_model(std::shared_ptr<Horizon::Models::Character::Character> character);
	/* Game Account */
	std::shared_ptr<Horizon::Models::GameAccount> get_game_account();
	void set_game_account(std::shared_ptr<Horizon::Models::GameAccount> account);
	/* Session Data */
	std::shared_ptr<Horizon::Models::SessionData> get_session_data();
	void set_session_data(std::shared_ptr<Horizon::Models::SessionData> session_data);

	void initialize();
	void handle_new_connection(PacketBuffer &buf);
	void update(uint32_t diff);

private:
	std::shared_ptr<PacketHandler> _packet_handler;
	std::shared_ptr<Horizon::Models::Character::Character> _character;
	std::shared_ptr<Horizon::Models::GameAccount> _game_account;
	std::shared_ptr<Horizon::Models::SessionData> _session_data;
	client_type _client_type;
	int32_t _packet_version;
};
}
}
#endif /* HORIZON_CHAR_SESSION_CHARSESSION_HPP */
