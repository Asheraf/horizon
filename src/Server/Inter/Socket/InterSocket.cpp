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

#include "InterSocket.hpp"

#include "Server/Inter/SocketMgr/ClientSocketMgr.hpp"
#include "Server/Inter/PacketHandler/PacketHandlerFactory.hpp"

#include "Core/Logging/Logger.hpp"
#include "Packets.hpp"

Horizon::Inter::InterSocket::InterSocket(std::shared_ptr<tcp::socket> socket)
: Socket(socket)
{
	//
}

/**
 * @brief Start method invoked once from the network thread that the socket is in,
 *        on start of the socket connection.
 */
void Horizon::Inter::InterSocket::start()
{
	std::string ip_address = remote_ip_address();

	InterLog->info("Established connection from {}.", ip_address);

	if (get_packet_handler() == nullptr) {
		set_packet_handler(PacketHandlerFactory::create_packet_handler(shared_from_this()));
		get_packet_handler()->Send_INTER_CONNECT_INIT();
	}
	async_read();
}

/**
 * @brief Socket cleanup method on connection closure.
 */
void Horizon::Inter::InterSocket::on_close()
{
	InterLog->info("Closed connection from {}.", remote_ip_address());

	/* Perform socket manager cleanup. */
	ClientSocktMgr->clear_socket(shared_from_this());
}

/**
 * @brief Asynchronous update() method periodically called from network threads.
 * @return true on successful update, false on failure.
 */
bool Horizon::Inter::InterSocket::update()
{
	return BaseSocket::update();
}

/**
 * Incoming buffer read handler.
 */
void Horizon::Inter::InterSocket::read_handler()
{
	while (get_read_buffer().get_active_size()) {
		uint16_t op_code;
		memcpy(&op_code, get_read_buffer().get_read_pointer(), sizeof(uint16_t));

		PacketBuffer pkt(op_code, get_read_buffer().get_read_pointer(), get_read_buffer().get_active_size());
		get_read_buffer().read_completed(get_read_buffer().get_active_size());

		if (get_packet_handler() == nullptr) {
			set_packet_handler(PacketHandlerFactory::create_packet_handler(shared_from_this()));
			get_packet_handler()->Send_INTER_CONNECT_INIT();
		}

		if (!get_packet_handler()->handle_received_packet(pkt))
			get_read_buffer().reset();
	}
}
