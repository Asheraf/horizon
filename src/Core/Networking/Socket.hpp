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

using boost::asio::ip::tcp;

#define READ_BLOCK_SIZE 4096

template <class T>
class Socket : public std::enable_shared_from_this<T>
{
public:
	explicit Socket(tcp::socket &&socket)
	: _socket(std::move(socket)), _remoteAddress(_socket.remote_endpoint().address()),
	  _remotePort(_socket.remote_endpoint().port()), _readBuffer(), _closed(false), _closing(false), _isWritingAsync(false)
	{
		_readBuffer.Resize(READ_BLOCK_SIZE);
	}

	virtual ~Socket()
	{
		boost::system::error_code error;

		_closed = true;

		_socket.close(error);
	}

	/* Socket Id */
	uint64_t getSocketId() const { return _socket_id; }
	void setSocketId(uint64_t socket_id) { Socket::_socket_id = socket_id; }

	virtual void Start() = 0;

	virtual bool Update()
	{
		if (_closed)
			return false;

		if (_isWritingAsync || (_writeQueue.empty() && !_closing))
			return true;

		for (; HandleQueue();)
			;
		return true;
	}

	boost::asio::ip::address GetRemoteIPAddress() const
	{
		return _remoteAddress;
	}

	uint16_t GetRemotePort() const
	{
		return _remotePort;
	}

	void AsyncRead()
	{
		if (!IsOpen())
			return;

		_readBuffer.Normalize();
		_readBuffer.EnsureFreeSpace();
		_socket.async_receive(boost::asio::buffer(_readBuffer.GetWritePointer(), _readBuffer.GetRemainingSpace()),
				std::bind(&Socket<T>::ReadHandlerInternal, this->shared_from_this(), std::placeholders::_1, std::placeholders::_2));
	}

	void AsyncReadWithCallback(void (T::*callback)(boost::system::error_code, std::size_t))
	{
		if (!IsOpen())
			return;

		_readBuffer.Normalize();
		_readBuffer.EnsureFreeSpace();
		_socket.async_receive(boost::asio::buffer(_readBuffer.GetWritePointer(), _readBuffer.GetRemainingSpace()),
				std::bind(callback, this->shared_from_this(), std::placeholders::_1, std::placeholders::_2));
	}

	void QueuePacket(MessageBuffer &&buffer)
	{
		_writeQueue.push(std::move(buffer));

		AsyncProcessQueue();
	}

	bool IsOpen() const { return !_closed && !_closing; }

	void CloseSocket()
	{
		if (_closed.exchange(true))
			return;

		boost::system::error_code shutdownError;
		_socket.shutdown(boost::asio::socket_base::shutdown_send, shutdownError);

		if (shutdownError) {
			CoreLog->error("Error when shutting down socket from IP {} (error code: {} - {})",
				GetRemoteIPAddress().to_string(), shutdownError.value(), shutdownError.message().c_str());
		}

		OnClose();
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

		_socket.async_write_some(boost::asio::null_buffers(), std::bind(&Socket<T>::WriteHandlerWrapper,
				this->shared_from_this(), std::placeholders::_1, std::placeholders::_2));

		return false;
	}

	void SetNoDelay(bool enable)
	{
		boost::system::error_code error;
		_socket.set_option(tcp::no_delay(enable), error);
		if (error) {
			CoreLog->error("Networking: Socket::SetNoDelay: failed to set_option(boost::asio::ip::tcp::no_delay) for IP {} (error_code: {} - {})",
					GetRemoteIPAddress().to_string().c_str(), error.value(), error.message().c_str());
		}
	}
private:
	void ReadHandlerInternal(boost::system::error_code error, size_t transferredBytes)
	{
		if (error) {
			CloseSocket();
			return;
		}

		_readBuffer.WriteCompleted(transferredBytes);
		ReadHandler();
	}

	void WriteHandlerWrapper(boost::system::error_code /*error*/, std::size_t /*transferedBytes*/)
	{
		_isWritingAsync = false;
		HandleQueue();
	}

	bool HandleQueue()
	{
		if (_writeQueue.empty())
			return false;

		MessageBuffer &queuedMessage = _writeQueue.front();

		std::size_t bytesToSend = queuedMessage.GetActiveSize();

		boost::system::error_code error;
		std::size_t bytesSent = _socket.write_some(boost::asio::buffer(queuedMessage.GetReadPointer(), bytesToSend), error);

		if (error) {
			if (error == boost::asio::error::would_block || error == boost::asio::error::try_again)
				return AsyncProcessQueue();

			_writeQueue.pop();
			if (_closing && _writeQueue.empty())
				CloseSocket();
			return false;
		} else if (bytesSent == 0) {
			_writeQueue.pop();
			if (_closing && _writeQueue.empty())
				CloseSocket();
			return false;
		} else if (bytesSent < bytesToSend) { // now n > 0
			queuedMessage.ReadCompleted(bytesSent);
			return AsyncProcessQueue();
		}

		_writeQueue.pop();

		if (_closing && _writeQueue.empty())
			CloseSocket();

		return !_writeQueue.empty();
	}

private:
	uint64_t _socket_id;
	tcp::socket _socket;
	boost::asio::ip::address _remoteAddress;
	uint16_t _remotePort;

	MessageBuffer _readBuffer;
	std::queue<MessageBuffer> _writeQueue;
	std::atomic<bool> _closed;
	std::atomic<bool> _closing;

	bool _isWritingAsync;
};

#endif //HORIZON_SOCKET_HPP
