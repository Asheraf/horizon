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

#include "PacketHandler/AuthPackets.hpp"
#include "Server/Common/Factories/PacketHandlerFactory.hpp"
#include "PacketHandler/AuthPacketHandler.hpp"

#include <random>

AuthSession::AuthSession(std::shared_ptr<tcp::socket> socket)
: Socket(socket)
{
	_session_data = std::make_shared<SessionData>();
}

void AuthSession::Start()
{
	std::string ip_address = GetRemoteIPAddress().to_string();

	AuthLog->info("Established connection from {}.", ip_address);

	AsyncRead();
}

void AuthSession::OnClose()
{
	std::string ip_address = GetRemoteIPAddress().to_string();

	AuthLog->info("Closed connection from {}.", ip_address);
}

bool AuthSession::Update()
{
	return AuthSocket::Update();
}

int AuthSession::GetPacketVersion(uint16_t op_code, PacketBuffer buf)
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

void AuthSession::ReadHandler()
{
	uint16_t op_code;

	while (GetReadBuffer().GetActiveSize()) {
		memcpy(&op_code, GetReadBuffer().GetReadPointer(), sizeof(uint16_t));

		PacketBuffer pkt(op_code, std::move(GetReadBuffer()));

		/**
		 * Devise the a suitable packet handler
		 * based on the client's packet version.
		 */
		if (op_code == CA_LOGIN) {
			int packet_ver = GetPacketVersion(op_code, pkt);
			_packet_handler = PacketHandlerFactory::CreateAuthPacketHandler(packet_ver, shared_from_this());
		} else if (_packet_handler == nullptr) {
			return;
		}

		if (!_packet_handler->HandleIncomingPacket(pkt))
			GetReadBuffer().Reset();
	}
}

std::shared_ptr<GameAccount> AuthSession::getGameAccount()
{
	return _game_account;
}

void AuthSession::setGameAccount(std::shared_ptr<GameAccount> game_account)
{
	_game_account = game_account;
}

std::shared_ptr<SessionData> AuthSession::getSessionData()
{
	return _session_data;
}

void AuthSession::setSessionData(std::shared_ptr<SessionData> session_data)
{
	_session_data = session_data;
}

std::shared_ptr<AuthPacketHandler> AuthSession::getPacketHandler()
{
	return _packet_handler;
}

void AuthSession::setPacketHandler(std::shared_ptr<AuthPacketHandler> packet_handler)
{
	_packet_handler = packet_handler;
}
