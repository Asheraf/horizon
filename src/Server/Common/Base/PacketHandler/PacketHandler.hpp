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
template <class SocketType>
class PacketHandler
{
public:
	PacketHandler(std::shared_ptr<SocketType> session)
	: _session(session)
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
	bool HandleReceivedPacket(PacketBuffer &buf)
	{
		boost::optional<PacketHandlerFunc> optional_handler = getPacketHandler(buf.getOpCode());

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
	void SendPacket(T pkt)
	{
		PacketBuffer buf;

		buf << pkt;

		if (!_session->IsOpen())
			return;

		if (!buf.empty()) {
			MessageBuffer buffer;
			buffer.Write(buf.contents(), sizeof(T));
			_session->QueuePacket(std::move(buffer));
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
	void SendPacket(PacketBuffer &buf, std::size_t size)
	{
		if (!_session->IsOpen())
			return;

		if (!buf.empty()) {
			MessageBuffer buffer;
			buffer.Write(buf.contents(), size);
			_session->QueuePacket(std::move(buffer));
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
	void SendSyncPacket(T pkt, std::size_t size = sizeof(T))
	{
		PacketBuffer buf;

		buf << pkt;

		if (!_session->IsOpen())
			return;

		if (!buf.empty()) {
			MessageBuffer buffer;
			buffer.Write(buf.contents(), size);
			_session->SyncWrite(buffer, size);
		}
	}

	/**
	 * @brief Send Synchronous packet with a buffer of a particular size
	 *        to the connected session.
	 * @param[in|out] buf    packet buffer to be sent.
	 * @param[in]     size   size of the buffer to be sent.
	 */
	void SendSyncPacket(PacketBuffer &buf, std::size_t size)
	{
		if (!_session->IsOpen())
			return;

		if (!buf.empty()) {
			MessageBuffer buffer;
			buffer.Write(buf.contents(), size);
			_session->SyncWrite(buffer, size);
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
	uint16_t SendAndReceive(SEND_T &send_pkt, RECV_T *recv_pkt)
	{
		PacketBuffer buf;
		uint16_t op_code = 0x0;

		buf << send_pkt;

		if (!_session->IsOpen())
			return false;

		if (!buf.empty()) {
			std::size_t recv_size = 0;
			MessageBuffer recv_buf, send_buf;
			send_buf.Write(buf.contents(), sizeof(SEND_T));

			/* Block until data is sent. */
			_session->SyncWrite(send_buf, sizeof(SEND_T));

			/* Block until data is received. */
			recv_size = _session->SyncRead(recv_buf);

			if (recv_size > 0) {
				op_code = 0x0;
				memcpy(&op_code, recv_buf.GetReadPointer(), sizeof(uint16_t));

				if (recv_pkt->op_code == op_code)
					memcpy(recv_pkt, (RECV_T *) recv_buf.GetReadPointer(), recv_size);
			}
		}

		return op_code;
	}

	/**
	 * @brief Retrieves the handler map.
	 * @return PacketHandlerMap.
	 */
	const PacketHandlerMap &getHandlers() const { return _handlers; }

	/**
	 * @brief Retrieves a packet handler function from the handler map.
	 * @param[in] packet_id  Id of the packet.
	 * @return instance of initialized boost::optional<PacketHandlerFunc>,
	 *         empty if not found.
	 */
	boost::optional<PacketHandlerFunc> getPacketHandler(uint16_t packet_id)
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
	void addPacketHandler(uint16_t packet_id, PacketHandlerFunc const &func)
	{
		if (getPacketHandler(packet_id))
			_handlers.erase(packet_id);

		_handlers.insert(std::make_pair(packet_id, func));
	}

	/**
	 * @brief Retrieves the session from this handler instance.
	 * @return shared_ptr to an object of the session type.
	 */
	const std::shared_ptr<SocketType> &getSession() const { return _session; }

	/**
	 * @brief Pure virtual handler initializer on construction.
	 */
	virtual void InitializeHandlers() = 0;

private:
	std::shared_ptr<SocketType> _session;   ///< Shared pointer to the instantiated session object.
	PacketHandlerMap _handlers;              ///< Packet handler function map.
};
}
}

#endif /* HORIZON_BASE_PACKETHANDLER_HPP */
