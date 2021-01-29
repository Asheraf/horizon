/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 *
 * Copyright (c) 2019 Sagun K. (sagunxp@gmail.com).
 * Copyright (c) 2019 Horizon Dev Team.
 *
 * Base Author - Sagun K. (sagunxp@gmail.com)
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
#include "ZoneSession.hpp"

#include "Server/Zone/Game/Entities/Player/Player.hpp"
#include "Server/Zone/Game/Map/MapManager.hpp"
#include "Server/Zone/Game/Map/Map.hpp"
#include "Server/Zone/Socket/ZoneSocket.hpp"
#include "Server/Zone/Zone.hpp"

using namespace Horizon::Zone;
using namespace Horizon::Zone::Entities;

ZoneSession::ZoneSession(std::shared_ptr<ZoneSocket> socket)
: Session(socket)
{
}

ZoneSession::~ZoneSession()
{
	//
}

/**
 * @brief Initializes the zone session's members.
 */
void ZoneSession::initialize()
{
	_pkt_tbl = std::make_unique<ClientPacketLengthTable>(shared_from_this());
	_clif = std::make_unique<ZoneClientInterface>(shared_from_this());
}

void ZoneSession::transmit_buffer(ByteBuffer _buffer, std::size_t size)
{
	if (get_socket() == nullptr || !get_socket()->is_open())
		return;
	
	if (!_buffer.is_empty()) {
		get_socket()->queue_buffer(std::move(_buffer));
	}
}

/**
 * @brief Update loop for each Zone Session.
 * @thread called from MapContainerThread.
 */
void ZoneSession::update(uint32_t /*diff*/)
{
	std::shared_ptr<ByteBuffer> read_buf;
	while ((read_buf = get_socket()->_buffer_recv_queue.try_pop())) {
		uint16_t packet_id = 0x0;
		memcpy(&packet_id, read_buf->get_read_pointer(), sizeof(uint16_t));
		HPacketTablePairType p = _pkt_tbl->get_hpacket_info(packet_id);
		
		HLog(debug) << "Handling packet 0x" << std::hex << packet_id << " - len:" << p.first << std::endl;
		
		p.second->handle(std::move(*read_buf));
	}
}

/**
 * @brief Performs generic logout of player in cases where the
 * connection was closed abruptly or by instruction.
 * Also marks the player for removal from the MapContainerThread.
 * @thread Called from the NetworkThread.
 */
void ZoneSession::perform_cleanup()
{
	if (player() != nullptr) {
		player()->set_logged_in(false);
		player()->notify_nearby_players_of_self(EVP_NOTIFY_LOGGED_OUT);
		player()->remove_grid_reference();
		player()->sync_with_models();
		player()->map_container()->remove_player(player());
	}
}
