/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 * Copyright (c) 2019 Horizon Dev Team.
 *
 * Base Author - Sxyz (sagunxp@gmail.com)
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 **************************************************/

#ifndef HORIZON_INTERFACES_INTERSERVERAPI_HPP
#define HORIZON_INTERFACES_INTERSERVERAPI_HPP

#include "Server/Common/Base/PacketHandler/InterPackets.hpp"
#include "Server/Common/Models/GameAccount.hpp"
#include "Server/Common/Models/SessionData.hpp"

#include <stdio.h>
#include <memory>

namespace Horizon
{
namespace Interface
{
template <class SessionType>
class InterServerAPI
{
public:
	InterServerAPI()
	{
		//
	}

	virtual ~InterServerAPI()
	{
		//
	}

	/**
	 * @brief Obtain session data from the inter-server.
	 *        - Does not check if the inter-server is online
	 *          (but returns nullptr if the session happens to be null).
	 * @param[in] auth_code   session auth code to check against.
	 * @return shared_ptr to the session data or nullptr if none found.
	 */
	std::shared_ptr<Horizon::Models::SessionData> get_session_data(uint32_t auth_code)
	{
		std::shared_ptr<SessionData> session_data = std::make_shared<Horizon::Models::SessionData>();
		PACKET_CI_SESSION_REQ send_pkt;
		PACKET_IC_SESSION_REQ_ACK recv_pkt;

		send_pkt.auth_code = auth_code;

		if (_inter_socket != nullptr
			&& _inter_socket->get_session()->get_packet_handler()->send_and_receive_packet(send_pkt, &recv_pkt) == Horizon::Base::inter_packets::IC_SESSION_REQ_ACK) {
			*session_data << recv_pkt.s;
			return session_data;
		}

		return nullptr;
	}

	void request_authorisation()
	{
		if (_inter_socket != nullptr)
			_inter_socket->get_session()->get_packet_handler()->Send_CI_CONNECT_AUTH();
	}

	/**
	 * @brief Request inter to delete a session from the server's storage.
	 *        - Use carefully, deletions performed will affect all other services.
	 * @param[in] auth_code  session auth code to check against.
	 */
	void delete_session(uint32_t auth_code)
	{
		if (_inter_socket != nullptr)
			_inter_socket->get_session()->get_packet_handler()->Send_CI_SESSION_DEL(auth_code);
	}

	/**
	 * @brief Insert or Update session data into the inter server storage.
	 * @param[in|out] session_data   shared_ptr to the session data object.
	 */
	void store_session_data(std::shared_ptr<Horizon::Models::SessionData> const &session_data)
	{
		if (_inter_socket != nullptr)
			_inter_socket->get_session()->get_packet_handler()->Send_CI_SESSION_SET(*session_data);
	}

	/**
	 * @brief Obtain game account data from the inter-server.
	 *        - Does not check if the inter-server is online
	 *          (but returns nullptr if the session happens to be null).
	 * @param[in] account_id   game account ID to check against.
	 * @return shared_ptr to the game account data or nullptr if none found.
	 */
	std::shared_ptr<Horizon::Models::GameAccount> get_game_account(uint32_t account_id)
	{
		std::shared_ptr<Horizon::Models::GameAccount> game_account = std::make_shared<Horizon::Models::GameAccount>();
		PACKET_CI_GAME_ACCOUNT_REQ send_pkt;
		PACKET_IC_GAME_ACCOUNT_REQ_ACK recv_pkt;

		send_pkt.account_id = account_id;

		if (_inter_socket != nullptr
			&& _inter_socket->get_session()->get_packet_handler()->send_and_receive_packet(send_pkt, &recv_pkt) == Horizon::Base::inter_packets::IC_GAME_ACCOUNT_REQ_ACK) {
			*game_account << recv_pkt.s;
			return game_account;
		}

		return nullptr;
	}

	/**
	 * @brief Request inter to delete a game account from the server's storage.
	 *        - Use carefully, deletions performed will affect all other services.
	 * @param[in] account_id  game account ID to check against.
	 */
	void delete_game_account(uint32_t account_id)
	{
		if (_inter_socket != nullptr)
			_inter_socket->get_session()->get_packet_handler()->Send_CI_GAME_ACCOUNT_DEL(account_id);
	}

	/**
	 * @brief Insert or Update game account data into the inter server storage.
	 * @param[in|out] game_account   shared_ptr to the game account data object.
	 */
	void store_game_account(std::shared_ptr<Horizon::Models::GameAccount> game_account)
	{
		if (_inter_socket != nullptr)
			_inter_socket->get_session()->get_packet_handler()->Send_CI_GAME_ACCOUNT_SET(*game_account);
	}

	bool ping_inter_server()
	{
		PACKET_CI_PING send_pkt;
		PACKET_IC_PONG recv_pkt;

		if (_inter_socket != nullptr && _inter_socket->get_session() && _inter_socket->get_session()->get_packet_handler()
			&&_inter_socket->get_session()->get_packet_handler()->send_and_receive_packet(send_pkt, &recv_pkt) == Horizon::Base::inter_packets::IC_PONG)
			return true;

		return false;
	}

	std::shared_ptr<SessionType> get_inter_socket() { return std::atomic_load(&_inter_socket); }
	void set_inter_socket(std::shared_ptr<SessionType> socket) { std::atomic_store(&_inter_socket, socket); }

private:
	std::shared_ptr<SessionType> _inter_socket;
};
}
}

#endif /* HORIZON_INTERFACES_INTER_SERVER_HPP */
