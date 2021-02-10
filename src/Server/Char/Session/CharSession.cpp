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

#include "CharSession.hpp"

#include "Server/Char/Socket/CharSocket.hpp"
#include "Server/Char/Char.hpp"

using namespace Horizon::Char;

CharSession::CharSession(std::shared_ptr<CharSocket> socket)
: Horizon::Networking::Session<CharSocket, CharSession>(socket)
{
}

CharSession::~CharSession()
{
	//
}

void CharSession::initialize()
{
	_pkt_tbl = std::make_unique<ClientPacketLengthTable>(shared_from_this());
	_clif = std::make_unique<CharClientInterface>(shared_from_this());
}

void CharSession::transmit_buffer(ByteBuffer _buffer, std::size_t size)
{
	if (get_socket() == nullptr || !get_socket()->is_open())
		return;
	
	if (!_buffer.is_empty()) {
		// The first packet in the character server has no packet_id
		// and is the account id so its length is not deduceable as it can't be looked up.
		if(_first_packet_sent == true) {
			uint16_t packet_id = 0x0;
			int16_t packet_len = 0;
			
			memcpy(&packet_id, _buffer.get_read_pointer(), sizeof(int16_t));
			
			TPacketTablePairType p = _pkt_tbl->get_tpacket_info(packet_id);

			if (p.first == -1) {
				memcpy(&packet_len, _buffer.get_read_pointer() + 2, sizeof(int16_t));
			} else {
				packet_len = p.first;
			}

			if (packet_len != _buffer.active_length()) {
				HLog(warning) << "Packet 0x" << std::hex << packet_id << " has length len " << std::dec << packet_len << " but buffer has " << _buffer.active_length() << " bytes... ignoring.";
				return;
			}
		} else {
			_first_packet_sent = true;
		}

		get_socket()->queue_buffer(std::move(_buffer));
	}
}

void CharSession::update(uint32_t /*diff*/)
{
	std::shared_ptr<ByteBuffer> read_buf;
	while ((read_buf = get_socket()->_buffer_recv_queue.try_pop())) {
		uint16_t packet_id = 0x0;
		memcpy(&packet_id, read_buf->get_read_pointer(), sizeof(uint16_t));
		HPacketTablePairType p = _pkt_tbl->get_hpacket_info(packet_id);
		
		HLog(debug) << "Handling packet 0x" << std::hex << packet_id << " - 0x" << p.first << std::endl;
		
		p.second->handle(std::move(*read_buf));
	}
}


