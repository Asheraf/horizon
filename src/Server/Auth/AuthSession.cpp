/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 * Copyright (c) 2018 Horizon Dev Team.
 *
 * Base Author - Sagun Khosla. (sagunxp@gmail.com)
 *
 * Under a proprietary license this file is not for use
 * or viewing without permission.
 **************************************************/

#include "AuthSession.hpp"

#include "PacketHandler/Packets.hpp"
#include "Server/Auth/PacketHandler/PacketHandlerFactory.hpp"
#include "PacketHandler/PacketHandler.hpp"

#include <random>

Horizon::Auth::AuthSession::AuthSession(std::shared_ptr<tcp::socket> socket)
: Socket(socket)
{
	_session_data = std::make_shared<SessionData>();
}

void Horizon::Auth::AuthSession::Start()
{
	std::string ip_address = GetRemoteIPAddress().to_string();

	AuthLog->info("Established connection from {}.", ip_address);

	if (getSocketType() == SOCKET_ENDPOINT_TYPE_SERVER) {
		if (getInterPacketHandler() == nullptr) { // guessing that it was the inter-server.
			setInterPacketHandler(PacketHandlerFactory::CreateInterPacketHandler(shared_from_this()));
		}
	}

	AsyncRead();
}

void Horizon::Auth::AuthSession::OnClose()
{
	std::string ip_address = GetRemoteIPAddress().to_string();

	AuthLog->info("Closed connection from {}.", ip_address);
}

bool Horizon::Auth::AuthSession::Update()
{
	return AuthSocket::Update();
}

int Horizon::Auth::AuthSession::GetPacketVersion(uint16_t op_code, PacketBuffer buf)
{
	int packet_ver = 0;

	switch (op_code)
	{
	case CA_LOGIN:
	{
		PACKET_CA_LOGIN pkt;
		buf >> pkt;
		packet_ver = pkt.version;
	}
		break;
	default:
		return 0;
	}

	return packet_ver;
}

void Horizon::Auth::AuthSession::ReadHandler()
{
	while (GetReadBuffer().GetActiveSize()) {
		uint16_t op_code = 0x0;
		memcpy(&op_code, GetReadBuffer().GetReadPointer(), sizeof(uint16_t));

		PacketBuffer pkt(op_code, GetReadBuffer().GetReadPointer(), GetReadBuffer().GetActiveSize());
		GetReadBuffer().ReadCompleted(GetReadBuffer().GetActiveSize());

		/**
		 * Devise the a suitable packet handler
		 * based on the client's packet version.
		 */
		if (getSocketType() == SOCKET_ENDPOINT_TYPE_CLIENT) {
			if (op_code == CA_LOGIN) {
				int packet_ver = GetPacketVersion(op_code, pkt);
				setPacketHandler(PacketHandlerFactory::CreateAuthPacketHandler(packet_ver, shared_from_this()));
			}

			if (getPacketHandler() == nullptr) {
				AuthLog->error("Packet handler was null!");
				return;
			}

			if (!getPacketHandler()->HandleIncomingPacket(pkt))
				GetReadBuffer().Reset();
		} else if (getSocketType() == SOCKET_ENDPOINT_TYPE_SERVER) {
			if (getInterPacketHandler() == nullptr) // guessing that it was the inter-server.
				setInterPacketHandler(PacketHandlerFactory::CreateInterPacketHandler(shared_from_this()));
			if (!getInterPacketHandler()->HandleIncomingPacket(pkt))
				GetReadBuffer().Reset();
		}
	}
}

std::shared_ptr<GameAccount> Horizon::Auth::AuthSession::getGameAccount()
{
	return _game_account;
}

void Horizon::Auth::AuthSession::setGameAccount(std::shared_ptr<GameAccount> game_account)
{
	_game_account = game_account;
}

std::shared_ptr<SessionData> Horizon::Auth::AuthSession::getSessionData()
{
	return _session_data;
}

void Horizon::Auth::AuthSession::setSessionData(std::shared_ptr<SessionData> session_data)
{
	_session_data = session_data;
}

std::shared_ptr<Horizon::Auth::PacketHandler> Horizon::Auth::AuthSession::getPacketHandler()
{
	return _packet_handler;
}

void Horizon::Auth::AuthSession::setPacketHandler(std::shared_ptr<Horizon::Auth::PacketHandler> packet_handler)
{
	_packet_handler = packet_handler;
}

std::shared_ptr<Horizon::Auth::InterPacketHandler> Horizon::Auth::AuthSession::getInterPacketHandler()
{
	return _inter_packet_handler;
}

void Horizon::Auth::AuthSession::setInterPacketHandler(std::shared_ptr<Horizon::Auth::InterPacketHandler> inter_packet_handler)
{
	_inter_packet_handler = inter_packet_handler;
}
