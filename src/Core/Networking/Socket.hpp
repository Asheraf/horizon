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

#ifndef HORIZON_SOCKET_HPP
#define HORIZON_SOCKET_HPP

#include "Core/Logging/Logger.hpp"
#include "Buffer/MessageBuffer.hpp"

#include <atomic>
#include <queue>
#include <memory>
#include <functional>
#include <type_traits>
#include <boost/asio/ip/tcp.hpp>
#include <boost/bind.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/use_future.hpp>
#include <iostream>
#include <future>

using boost::asio::ip::tcp;

#define READ_BLOCK_SIZE 4096

enum socket_endpoint_type
{
	SOCKET_ENDPOINT_TYPE_CLIENT,
	SOCKET_ENDPOINT_TYPE_SERVER
};

template <class T>
class Socket : public std::enable_shared_from_this<T>
{
public:
	explicit Socket(std::shared_ptr<tcp::socket> &socket)
	: _socket_id(0), _socket(socket), _type(SOCKET_ENDPOINT_TYPE_CLIENT), _readBuffer(), _closed(false), _closing(false), _isWritingAsync(false)
	{
		_readBuffer.Resize(READ_BLOCK_SIZE);
	}

	virtual ~Socket()
	{
		boost::system::error_code error;
		_closed = true;
		_socket->close(error);
	}

	virtual void Start() = 0;
	virtual bool Update()
	{
		if (_closed)
			return false;

		if (_isWritingAsync || (_writeQueue.empty() && !_closing))
			return true;

		while (HandleQueue())
			;

		return true;
	}

	/* Socket Id */
	uint64_t getSocketId() const { return _socket_id; }
	void setSocketId(uint64_t socket_id) { Socket::_socket_id = socket_id; }
	/* Socket Type */
	socket_endpoint_type getSocketType() const { return _type; }
	void setSocketType(socket_endpoint_type _type) { Socket::_type = _type; }
	/* Remote IP and Port */
	boost::asio::ip::address GetRemoteIPAddress() const { return _socket->remote_endpoint().address(); }
	uint16_t GetRemotePort() const { return _socket->remote_endpoint().port(); }

	void AsyncRead()
	{
		if (!IsOpen())
			return;

		_readBuffer.Normalize();
		_readBuffer.EnsureFreeSpace();

		_socket->async_read_some(boost::asio::buffer(_readBuffer.GetWritePointer(), _readBuffer.GetRemainingSpace()),
				boost::bind(&Socket<T>::ReadHandlerInternal, this, boost::placeholders::_1, boost::placeholders::_2));
	}

	void AsyncReadWithCallback(void (Socket<T>::*callback)(boost::system::error_code, std::size_t))
	{
		if (!IsOpen())
			return;

		_readBuffer.Normalize();
		_readBuffer.EnsureFreeSpace();
		_socket->async_read_some(boost::asio::buffer(_readBuffer.GetWritePointer(), _readBuffer.GetRemainingSpace()),
		                         boost::bind(&Socket<T>::ReadHandlerInternal, this, boost::placeholders::_1, boost::placeholders::_2));
	}

	/**
	 * Asynchronous reading with a future value.
	 * @return future to the size when complete.
	 */
	std::size_t ReadFuture()
	{
		return _socket->async_read_some(boost::asio::buffer(_readBuffer.GetWritePointer(), _readBuffer.GetRemainingSpace()), boost::asio::use_future);
	}

	/**
	 * Asynchronous reading with a future value.
	 * @return future to the size when complete.
	 */
	std::future<std::size_t> WriteFuture(MessageBuffer &message, std::size_t bytes_to_send)
	{
		return _socket->async_write_some(boost::asio::buffer(message.GetReadPointer(), bytes_to_send), boost::asio::use_future);
	}

	void QueuePacket(MessageBuffer &&buffer)
	{
		_writeQueue.push(std::move(buffer));
	}

	bool IsOpen() { return !_closed && !_closing; }

	void CloseSocket()
	{
		boost::system::error_code error;

		if (_closed.exchange(true))
			return;

		// Finalise the child-class socket first.
		OnClose();

		/**
		 * Socket finalisation.
		 */
		// Shutdown the socket.
		_socket->shutdown(boost::asio::socket_base::shutdown_send, error);
		// Close the socket.
		_socket->close();

		if (error) {
			CoreLog->error("Error when shutting down socket from IP {} (error code: {} - {})",
				GetRemoteIPAddress().to_string(), error.value(), error.message().c_str());
		}

	}

	void DelayedCloseSocket() { _closing = true; }

	MessageBuffer &GetReadBuffer() { return _readBuffer; }
protected:
	virtual void OnClose() = 0;
	virtual void ReadHandler() = 0;

	bool AsyncProcessQueue()
	{
		if (_isWritingAsync)
			return false;

		_isWritingAsync = true;

		_socket->async_write_some(boost::asio::null_buffers(), boost::bind(&Socket<T>::WriteHandlerWrapper,
				this, boost::placeholders::_1, boost::placeholders::_2));

		return true;
	}

	/**
	 * Disable the Nagle Algorithm on our socket.
	 * @param enable
	 */
	void SetNoDelay(bool enable)
	{
		boost::system::error_code error;
		_socket->set_option(tcp::no_delay(enable), error);
		if (error) {
			CoreLog->error("Networking: Socket::SetNoDelay: failed to set_option(boost::asio::ip::tcp::no_delay) for IP {} (error_code: {} - {})",
					GetRemoteIPAddress().to_string().c_str(), error.value(), error.message().c_str());
		}
	}

	/**
	 * Write a message to the buffer.
	 * @param to_send
	 * @param error
	 * @return
	 */
	std::size_t WriteToBufferAndSend(MessageBuffer &to_send, boost::system::error_code &error)
	{
		std::size_t bytes_to_send = to_send.GetActiveSize();
		std::size_t bytes_sent = _socket->write_some(boost::asio::buffer(to_send.GetReadPointer(), bytes_to_send), error);
		return bytes_sent;
	}
private:
	/**
	 * Aysnchronous reading handler method.
	 * @param error
	 * @param transferredBytes
	 */
	void ReadHandlerInternal(boost::system::error_code error, size_t transferredBytes)
	{
		if (error) {
			CloseSocket();
			return;
		}

		if (transferredBytes > 0) {
			_readBuffer.WriteCompleted(transferredBytes);
			ReadHandler();
		}
		AsyncRead();
	}

	/**
	 *
	 */
	void WriteHandlerWrapper(boost::system::error_code /*error*/, std::size_t /*transferedBytes*/)
	{
		_isWritingAsync = false;
		HandleQueue();
	}

	/**
	 * Handle the queue
	 * @return true on success, false on failure.
	 */
	bool HandleQueue()
	{
		boost::system::error_code error;

		if (_writeQueue.empty())
			return false;

		MessageBuffer &to_send = _writeQueue.front();
		std::size_t bytes_sent = WriteToBufferAndSend(to_send, error);

		if (error == boost::asio::error::would_block || error == boost::asio::error::try_again)
			return AsyncProcessQueue();

		/**
		 * Re-process queue if we have remaining bytes.
		 */
		if (!error && bytes_sent < to_send.GetActiveSize()) {
			to_send.ReadCompleted(bytes_sent);
			return AsyncProcessQueue();
		}

		// Pop the front element.
		_writeQueue.pop();
		// Close if required.
		if (_closing && _writeQueue.empty())
			CloseSocket();

		return !_writeQueue.empty() && bytes_sent;
	}

private:
	uint64_t _socket_id;
	std::shared_ptr<tcp::socket> _socket;               ///< After accepting, the reference count of this pointer should be 1.
	enum socket_endpoint_type _type;
	MessageBuffer _readBuffer;
	std::queue<MessageBuffer> _writeQueue;
	std::atomic<bool> _closed;
	std::atomic<bool> _closing;
	bool _isWritingAsync;
};

#endif //HORIZON_SOCKET_HPP
