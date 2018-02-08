//
// Created by SagunKho on 31/01/2018.
//

#ifndef HORIZON_BASE_INTERPACKETHANDLER_HPP
#define HORIZON_BASE_INTERPACKETHANDLER_HPP

#include "Server/Common/PacketBuffer.hpp"
#include "Server/Common/Base/PacketHandler/PacketHandler.hpp"
#include "Server/Common/Base/PacketHandler/InterPackets.hpp"
#include "Server/Common/Models/SessionData.hpp"
#include "Server/Common/Models/GameAccount.hpp"

#include <memory>

class PacketBuffer;
class MessageBuffer;

namespace Horizon
{
namespace Base
{
template <class SocketType>
class InterPacketHandler : public PacketHandler<SocketType>
{
public:
	InterPacketHandler(std::shared_ptr<SocketType> session, std::string const &password)
	: PacketHandler<SocketType>(session), _inter_password(password)
	{
		InitializeHandlers();
	}

	~InterPacketHandler(){ }

	/* Initialize all handlers */
	virtual void InitializeHandlers() override
	{
#define HANDLER_FUNC(packet) this->addPacketHandler(packet, boost::bind(&InterPacketHandler::Handle_ ## packet, this, boost::placeholders::_1))
		HANDLER_FUNC(INTER_ACK_RECEIVED);
		HANDLER_FUNC(INTER_CONNECT_INIT);
		HANDLER_FUNC(INTER_SESSION_GET);
		HANDLER_FUNC(INTER_ACK_RECEIVED);
		HANDLER_FUNC(INTER_GAME_ACCOUNT_GET);
#undef HANDLER_FUNC
	}

	virtual bool SyncReceiveFromInter(PacketBuffer &pkt_buf)
	{
		std::size_t recv_size;
		MessageBuffer buf;
		int op_code = 0x0;

		recv_size = this->getSession()->SyncRead(buf);

		if (!recv_size)
			return false;

		memcpy(&op_code, buf.GetReadPointer(), sizeof(uint16_t));
		PacketBuffer recv_pkt(op_code, buf.GetReadPointer(), buf.GetActiveSize());
		pkt_buf = recv_pkt;

		return true;
	}

	virtual void ReceiveAndHandle(PacketBuffer &buf)
	{
		if (SyncReceiveFromInter(buf))
			this->HandleReceivedPacket(buf);
	}

	/************
	 * Handlers
	 ************/
	virtual void Handle_INTER_ACK_RECEIVED(PacketBuffer &buf)
	{
		PACKET_INTER_ACK_RECEIVED pkt;

		buf >> pkt;

		switch (pkt.ack_packet_id)
		{
		case INTER_CONNECT_AUTH:
			if (pkt.response == 1) {
				CoreLog->info("Connection to inter server authorized.");
			} else {
				CoreLog->info("Connection to inter server not authorized.");
				this->getSession()->CloseSocket();
			}
			break;
		default:
			CoreLog->info("Received unknown packet response from Inter {0:x}", pkt.op_code);
			break;
		}
	}

	virtual void Handle_INTER_CONNECT_INIT(PacketBuffer &/*buf*/)
	{
		// Start authentication with inter-server using passwords.
		Respond_INTER_CONNECT_AUTH();
	}

	virtual void Handle_INTER_SESSION_GET(PacketBuffer &buf)
	{
		const std::shared_ptr<SessionData> session_data = this->getSession()->getSessionData();
		PACKET_INTER_SESSION_GET pkt;

		// Deserialize Buffer.
		buf >> pkt;
		// Update Session Data.
		*session_data << pkt.s;

		CoreLog->info("Updated session data for account : '{}'", session_data->getGameAccountID());
	}

	virtual void Handle_INTER_GAME_ACCOUNT_GET(PacketBuffer &buf)
	{
		const std::shared_ptr<GameAccount> game_account = this->getSession()->getGameAccount();
		PACKET_INTER_GAME_ACCOUNT_GET pkt;

		// Deserialize Buffer.
		buf >> pkt;
		// Update Game Account Data.
		*game_account << pkt.s;

		CoreLog->info("Updated game account data for account : '{}'", game_account->getID());
	}

	/************
	 * Responders
	 ************/
	virtual void Respond_INTER_CONNECT_AUTH()
	{
		PacketBuffer send_buf, recv_buf;

		auto pass_len = (uint16_t) _inter_password.length();
		auto packet_len = (uint16_t) (pass_len + 5);

		send_buf.append((uint16_t) INTER_CONNECT_AUTH);
		send_buf.append(packet_len);
		send_buf.append((uint8_t) _client_type);
		send_buf.append(_inter_password.c_str(), pass_len);

		this->SendSyncPacket(send_buf, packet_len);
		ReceiveAndHandle(recv_buf);
	}

	// Session Data
	virtual void Respond_INTER_SESSION_SET(SessionData &session_data)
	{
		PACKET_INTER_SESSION_SET pkt;
		session_data >> pkt.s;
		this->SendSyncPacket(pkt);
	}

	virtual void Respond_INTER_SESSION_DEL(uint32_t auth_code)
	{
		PACKET_INTER_SESSION_DEL pkt;
		pkt.auth_code = auth_code;
		this->SendSyncPacket(pkt);
	}

	virtual void Respond_INTER_SESSION_REQ(uint32_t auth_code)
	{
		PACKET_INTER_SESSION_REQ pkt;
		pkt.auth_code = auth_code;
		this->SendSyncPacket(pkt);
	}

	// Game Account
	virtual void Respond_INTER_GAME_ACCOUNT_SET(GameAccount &game_account)
	{
		PACKET_INTER_GAME_ACCOUNT_SET pkt;
		game_account >> pkt.s;
		this->SendSyncPacket(pkt);
	}

	virtual void Respond_INTER_GAME_ACCOUNT_DEL(uint32_t account_id)
	{
		PACKET_INTER_GAME_ACCOUNT_DEL pkt;
		pkt.account_id = account_id;
		this->SendSyncPacket(pkt);
	}

	virtual void Respond_INTER_GAME_ACCOUNT_REQ(uint32_t account_id)
	{
		PACKET_INTER_GAME_ACCOUNT_REQ pkt;
		pkt.account_id = account_id;
		this->SendSyncPacket(pkt);
	}

	/**
	 * @brief Set the session client type for the handler.
	 * @param[in] type  type of the session.
	 */
	void setClientType(inter_connect_client_type type) { _client_type = type; }
	/**
	 * @brief Get the session client type.
	 * @return type of the client for inter-server identification. @see inter_connect_client_type
	 */
	inter_connect_client_type getClientType() { return _client_type; }

private:
	inter_connect_client_type _client_type;
	std::string _inter_password;
};
}
}

#endif // HORIZON_BASE_INTERPACKETHANDLER_HPP
