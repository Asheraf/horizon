//
//  PacketHandler.h
//  Horizon
//
//  Created by SagunKho on 02/02/2018.
//
#ifndef HORIZON_BASE_PACKETHANDLER_HPP
#define HORIZON_BASE_PACKETHANDLER_HPP

#include "Core/Logging/Logger.hpp"
#include "Server/Common/Horizon.hpp"
#include "Server/Inter/PacketHandler/Packets.hpp"

#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <unordered_map>
#include <memory>
#include <boost/optional.hpp>

typedef boost::function<void(PacketBuffer &)> PacketHandlerFunc;
typedef std::unordered_map<uint16_t, PacketHandlerFunc> PacketHandlerMap;

namespace Horizon
{
namespace Base
{
template <class SessionType>
class PacketHandler
{
public:
	PacketHandler(std::shared_ptr<SessionType> session)
	: _socket(session)
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
		func(buf);

		return true;
	}

	/**
	 * @brief Send an Asynchronous packet by queueing
	 *        a buffer of a particular size to the
	 *        connected session.
	 * @param T type of the packet being queued.
	 * @param[in|out] pkt    packet buffer to be queued.
	 */
	template <typename T>
	void send_packet(T pkt)
	{
		PacketBuffer buf;

		buf << pkt;

		if (!_socket->IsOpen())
			return;

		if (!buf.empty()) {
			MessageBuffer buffer;
			buffer.write(buf.contents(), sizeof(T));
			_socket->QueuePacket(std::move(buffer));
		}
	}

	/**
	 * @brief Send an Asynchronous packet by queueing
	 *        a buffer of a particular size to the
	 *        connected session.
	 * @param T type of the packet being queued.
	 * @param[in|out] buf    packet buffer to be queued.
	 * @param[in]     size   size of the buffer to be queued (default sizeof type T)
	 */
	void send_packet(PacketBuffer &buf, std::size_t size)
	{
		if (!_socket->IsOpen())
			return;

		if (!buf.empty()) {
			MessageBuffer buffer;
			buffer.write(buf.contents(), size);
			_socket->QueuePacket(std::move(buffer));
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

		if (!_socket->IsOpen())
			return;

		if (!buf.empty()) {
			MessageBuffer buffer;
			buffer.write(buf.contents(), size);
			_socket->synchronous_write(buffer, size);
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
		if (!_socket->IsOpen())
			return;

		if (!buf.empty()) {
			MessageBuffer buffer;
			buffer.write(buf.contents(), size);
			_socket->synchronous_write(buffer, size);
		}
	}

	/**
	 * @brief Synchronous Packet Sending & Receiving function.
	 *        - This function will block until buffer is sent and recieved.
	 * @param SEND_T type of packet to be sent.
	 * @param RECV_T type of packet to be received.
	 * @param[in|out] send_pkt
	 */
	template <typename SEND_T, typename RECV_T>
	bool SendAndReceive(SEND_T &send_pkt, RECV_T *recv_pkt)
	{
		PacketBuffer buf;
		std::size_t send_size = 0, recv_size = 0;
		bool ret = false;

		buf << send_pkt;

		if (!_socket->IsOpen())
			return false;

		if (!buf.empty()) {
			MessageBuffer recv_buf, send_buf;
			send_buf.write(buf.contents(), sizeof(SEND_T));

			/* Block until data is sent. */
			send_size = _socket->synchronous_write(send_buf, sizeof(SEND_T));

			/* Block until data is received. */
			recv_size = _socket->SyncRead(recv_buf);

			if (recv_size > 0) {
				uint16_t op_code = 0x0;
				memcpy(&op_code, recv_buf.GetReadPointer(), sizeof(uint16_t));

				if (op_code == Horizon::Inter::INTER_ACK_RECEIVED) {
					PACKET_INTER_ACK_RECEIVED ack_pkt;
					memcpy(&ack_pkt, (PACKET_INTER_ACK_RECEIVED *) recv_buf.GetReadPointer(), recv_size);
					CoreLog->trace("Could not find data for requested packet {}.", send_pkt.op_code);
				} else if (recv_pkt->op_code != op_code) {
					CoreLog->warn("Inter server sent the wrong packet! received id {}, expected {}", op_code, recv_pkt->op_code);
				} else {
					memcpy(recv_pkt, (RECV_T *) recv_buf.GetReadPointer(), recv_size);
					ret = true;
				}
			}
		}

		return ret;
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
	const std::shared_ptr<SessionType> &get_socket() const { return _socket; }

	/**
	 * @brief Pure virtual handler initializer on construction.
	 */
	virtual void initialize_handlers() = 0;

private:
	std::shared_ptr<SessionType> _socket;   ///< Shared pointer to the instantiated session object.
	PacketHandlerMap _handlers;              ///< Packet handler function map.
};
}
}

#endif /* HORIZON_BASE_PACKETHANDLER_HPP */
