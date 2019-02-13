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

#include "ZoneSocket.hpp"

#include "Server/Common/Models/Character/Character.hpp"
#include "Server/Common/Models/SessionData.hpp"
#include "Server/Zone/Game/Entities/Unit/Player/Player.hpp"
#include "Server/Zone/Game/Map/MapManager.hpp"
#include "Server/Zone/Game/Map/Map.hpp"
#include "Server/Zone/SocketMgr/ClientSocketMgr.hpp"
#include "Server/Zone/Session/ZoneSession.hpp"
#include "Server/Zone/Zone.hpp"

using namespace Horizon::Zone;

ZoneSocket::ZoneSocket(std::shared_ptr<tcp::socket> socket)
: Socket(socket)
{
	//
}

/**
 * Session dependency.
 * @note required atomic setting/loading.
 * @thread set by network thread, retrieved by main thread.
 */
std::shared_ptr<ZoneSession> ZoneSocket::get_session() { return std::atomic_load(&_session); }
void ZoneSocket::set_session(std::shared_ptr<ZoneSession> session) { std::atomic_store(&_session, session); }

/**
 * @brief Initial method invoked once from the network thread that handles the ZoneSocket.
 */
void ZoneSocket::start()
{
	ZoneLog->info("Established connection from {}.", remote_ip_address());
	set_session(std::make_shared<ZoneSession>(shared_from_this()));
	async_read();
}

/**
 * @brief Socket cleanup method on connection closure.
 */
void ZoneSocket::on_close()
{
	ZoneLog->info("Closed connection from {}.", remote_ip_address());
}

void ZoneSocket::on_error()
{
	// Session cleanup if client has not exited properly.
	if (get_session()) {
		get_session()->cleanup_on_error();
	}
}

/**
 * @brief Asynchronous update method periodically called from network threads.
 * @thread NetworkThread
 * @return true on successful update, false on failure.
 */
bool ZoneSocket::update()
{
	return BaseSocket::update();
}

/**
 * Incoming buffer read handler.
 */
void ZoneSocket::read_handler()
{
	while (get_read_buffer().get_active_size()) {
		uint16_t packet_id = 0x0;
		memcpy(&packet_id, get_read_buffer().get_read_pointer(), sizeof(uint16_t));

		int16_t packet_length = GET_ZONE_PACKETLEN(packet_id);

		if (packet_length == -1) {
			memcpy(&packet_length, get_read_buffer().get_read_pointer() + 2, sizeof(int16_t));
		} else if (packet_length == 0) {
			ZoneLog->warn("Received non-existent packet id {0:x}, disconnecting session...", packet_id);
			close_socket();
			break;
		}

		PacketBuffer buf(get_read_buffer().get_read_pointer(), packet_length);
		get_read_buffer().read_completed(packet_length);

		_packet_recv_queue.push(std::move(buf));
	}
}

void ZoneSocket::update_session(uint32_t diff)
{
	get_session()->update(diff);
}
