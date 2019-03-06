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

#ifndef HORIZON_BASE_PACKETHANDLER_HPP
#define HORIZON_BASE_PACKETHANDLER_HPP

#include "Core/Logging/Logger.hpp"
#include "Server/Common/Definitions/Horizon.hpp"

#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <unordered_map>
#include <memory>
#include <boost/optional.hpp>

typedef boost::function<bool(PacketBuffer &)> PacketHandlerFunc;
typedef std::unordered_map<uint16_t, PacketHandlerFunc> PacketHandlerMap;

namespace Horizon
{
namespace Base
{
template <class SocketType>
class PacketHandler
{
public:
	PacketHandler(std::shared_ptr<SocketType> socket)
	: _socket(socket)
	{
		//
	}

	~PacketHandler()
	{
		//
	}

	/**
	 * @brief Handle the reception of a packet buffer
	 *        using the registered handlers.
	 * @param[in|out] buf    packet buffer to be queued.
	 * @return true on success false on failure.
	 */
	bool handle_received_packet(PacketBuffer &buf)
	{
		boost::optional<PacketHandlerFunc> optional_handler = get_packet_handler(buf.getOpCode());

		if (!optional_handler) {
			CoreLog->trace("Unknown packet with ID received: {0:x}", buf.getOpCode());
			return false;
		}

		PacketHandlerFunc func = *optional_handler;

		if (!func(buf)) {
			_socket.lock()->delayed_close_socket();
			return false;
		}

		return true;
	}

	/**
	 * @brief Send an Asynchronous packet by queueing
	 *        a buffer of a particular size to the
	 *        connected session.
	 * @param[in|out] buf    packet buffer to be queued.
	 */
	void send_packet(PacketBuffer &buf)
	{
		send_packet(buf, buf.size());
	}

	void send_packet(PacketBuffer &&buf)
	{
		send_packet(buf, buf.size());
	}

	/**
	 * @brief Send an Asynchronous packet by queueing
	 *        a buffer of a particular size to the
	 *        connected session.
	 * @param[in|out] buf    packet buffer to be queued.
	 * @param[in]     size   size of the buffer to be queued (default sizeof type T)
	 */
	void send_packet(PacketBuffer &buf, std::size_t size)
	{
		if (get_socket() == nullptr || !get_socket()->is_open())
			return;

		if (!buf.empty()) {
			MessageBuffer buffer;
			buffer.write(buf.contents(), size);
			get_socket()->queue_packet(std::move(buffer));
		}
	}


	/**
	 * @brief Send Synchronous packet with a buffer of a particular size
	 *        to the connected session.
	 * @param T type of the packet being sent.
	 * @param[in|out] pkt    data of type T to be sent.
	 * @param[in]     size   size of the buffer to be sent (default sizeof type T)
	 */
	template <typename T>
	void send_synchronous_packet(T pkt, std::size_t size = sizeof(T))
	{
		PacketBuffer buf;

		buf << pkt;

		if (!get_socket()->is_open())
			return;

		if (!buf.empty()) {
			MessageBuffer buffer;
			buffer.write(buf.contents(), size);
			get_socket()->sync_write(buffer, size);
		}
	}

	/**
	 * @brief Send Synchronous packet with a buffer of a particular size
	 *        to the connected session.
	 * @param[in|out] buf    packet buffer to be sent.
	 * @param[in]     size   size of the buffer to be sent.
	 */
	void send_synchronous_packet(PacketBuffer &buf, std::size_t size)
	{
		if (!get_socket()->is_open())
			return;

		if (!buf.empty()) {
			MessageBuffer buffer;
			buffer.write(buf.contents(), size);
			get_socket()->sync_write(buffer, size);
		}
	}

	/**
	 * @brief Synchronous Packet Sending & Receiving function.
	 *        - This method will block until buffer is sent and received.
	 *        - The only raw types this function deals with are well-defined, fixed-length
	 *          packet structures.
	 * @param SEND_T type of packet to be sent.
	 * @param RECV_T type of packet to be received.
	 * @param[in|out] send_pkt
	 */
	template <typename SEND_T, typename RECV_T>
	uint16_t send_and_receive_packet(SEND_T &send_pkt, RECV_T *recv_pkt)
	{
		PacketBuffer buf;
		uint16_t packet_id = 0x0;

		buf << send_pkt;

		if (!get_socket()->is_open())
			return 0;

		if (!buf.empty()) {
			std::size_t recv_size = 0;
			MessageBuffer recv_buf, send_buf;
			send_buf.write(buf.contents(), sizeof(SEND_T));

			/* Block until data is sent. */
			get_socket()->sync_write(send_buf, sizeof(SEND_T));

			/* Block until data is received. */
			recv_size = get_socket()->sync_read(recv_buf, sizeof(RECV_T));

			if (recv_size > 0) {
				packet_id = 0x0;
				memcpy(&packet_id, recv_buf.get_read_pointer(), sizeof(uint16_t));

				if (recv_pkt->packet_id == packet_id)
					memcpy(recv_pkt, (RECV_T *) recv_buf.get_read_pointer(), recv_size);
			}
		}

		return packet_id;
	}

	/**
	 * @brief Retrieves the handler map.
	 * @return PacketHandlerMap.
	 */
	const PacketHandlerMap &get_handlers() const { return _handlers; }

	/**
	 * @brief Retrieves a packet handler function from the handler map.
	 * @param[in] packet_id  Id of the packet.
	 * @return instance of initialized boost::optional<PacketHandlerFunc>,
	 *         empty if not found.
	 */
	boost::optional<PacketHandlerFunc> get_packet_handler(uint16_t packet_id)
	{
		auto it = _handlers.find(packet_id);

		if (it != _handlers.end())
			return boost::optional<PacketHandlerFunc>(it->second);

		return boost::optional<PacketHandlerFunc>();
	}

	/**
	 * @brief Register a packet handler to the handler map.
	 * @param[in] packet_id   Id of the packet being added.
	 * @param[in|out] func    Packet handler function.
	 */
	void add_packet_handler(uint16_t packet_id, PacketHandlerFunc const &func)
	{
		if (get_packet_handler(packet_id))
			_handlers.erase(packet_id);

		_handlers.insert(std::make_pair(packet_id, func));
	}

	/**
	 * @brief Retrieves the session from this handler instance.
	 * @return shared_ptr to an object of the session type.
	 */
	std::shared_ptr<SocketType> get_socket() { return _socket.lock(); }

	/**
	 * @brief Pure virtual handler initializer on construction.
	 */
	virtual void initialize_handlers() = 0;

private:
	std::weak_ptr<SocketType> _socket;     ///< Pointer to the instantiated session object.
	PacketHandlerMap _handlers;              ///< Packet handler function map.
};
}
}

#endif /* HORIZON_BASE_PACKETHANDLER_HPP */
