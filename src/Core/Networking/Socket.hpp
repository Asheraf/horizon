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
#include "Server/Common/Models/SessionData.hpp"
#include "Server/Common/Models/GameAccount.hpp"

#include <atomic>
#include <queue>
#include <memory>
#include <functional>
#include <future>
#include <type_traits>
#include <boost/asio/ip/tcp.hpp>
#include <boost/bind.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/use_future.hpp>

#include <iostream>

using boost::asio::ip::tcp;

#define READ_BLOCK_SIZE 4096

class SocketMgr;

template <class SocketType>
class Socket : public std::enable_shared_from_this<SocketType>
{
public:
	explicit Socket(std::shared_ptr<tcp::socket> socket)
	: _socket_id(0), _socket(socket), _remote_ip_address(_socket->remote_endpoint().address().to_string()),
	  _remote_port(_socket->remote_endpoint().port()), _readBuffer(), _closed(false), _closing(false), _isWritingAsync(false)
	{
		_readBuffer.Resize(READ_BLOCK_SIZE);
		// Initialize account-related objects.
		_session_data = std::make_shared<SessionData>();
		_game_account = std::make_shared<GameAccount>();
	}

	virtual ~Socket()
	{
		boost::system::error_code error;
		_socket->close(error);
	}

	virtual void start() = 0;
	virtual bool update()
	{
		if (_closed)
			return false;

		if (_isWritingAsync || (_writeQueue.empty() && !_closing))
			return true;

		while (handleQueue())
			;

		return true;
	}

	/* Socket Id */
	uint64_t getSocketId() const { return _socket_id; }
	void setSocketId(uint64_t socket_id) { Socket::_socket_id = socket_id; }
	/* Remote IP and Port */
	std::string getRemoteIPAddress() const { return _remote_ip_address; }
	uint16_t getRemotePort() const { return _remote_port; }

	void asyncRead()
	{
		if (!isOpen())
			return;

		_readBuffer.normalize();
		_readBuffer.ensureFreeSpace();

		_socket->async_read_some(boost::asio::buffer(_readBuffer.getWritePointer(), _readBuffer.getRemainingSpace()),
				boost::bind(&Socket<SocketType>::readHandlerInternal, this, boost::placeholders::_1, boost::placeholders::_2));
	}

	void asyncReadWithCallback(MessageBuffer &buf, void (Socket<SocketType>::*/*callback*/)(boost::system::error_code, std::size_t))
	{
		if (!isOpen())
			return;

		_readBuffer.normalize();
		_readBuffer.ensureFreeSpace();

		_socket->async_read_some(boost::asio::buffer(buf.getWritePointer(), buf.getRemainingSpace()),
		                         boost::bind(&Socket<SocketType>::readHandlerInternal, this, boost::placeholders::_1, boost::placeholders::_2));
	}

	/**
	 * Synchronous reading.
	 * @return size of the read buffer.
	 */
	std::size_t syncRead(MessageBuffer &buf, std::size_t read_size)
	{
		std::size_t size = 0;

		try {
			size = _socket->read_some(boost::asio::buffer(buf.getWritePointer(), read_size));
			buf.writeCompleted(size);
		} catch (boost::system::system_error &e) {
			CoreLog->info("Error '{}' while reading data from client at {}.", e.what(), _remote_ip_address);
		}

		return size;
	}

	/**
	 * Synchronous writing.
	 * @return size of the written buffer.
	 */
	std::size_t syncWrite(MessageBuffer &message, std::size_t bytes_to_send)
	{
		boost::system::error_code error;
		std::size_t size = 0;

		try {
			size = _socket->write_some(boost::asio::buffer(message.getReadPointer(), bytes_to_send), error);
			message.readCompleted(size);
		} catch (boost::system::system_error &e) {
			CoreLog->info("Error '{}' while writing data to client at {}.", e.what(), _remote_ip_address);
		}

		return size;
	}

	void queuePacket(MessageBuffer &&buffer)
	{
		_writeQueue.push(std::move(buffer));
	}

	bool isOpen() { return !_closed && !_closing; }

	void closeSocket()
	{
		boost::system::error_code error;

		if (_closed.exchange(true))
			return;

		// Finalise the child-class socket first.
		onClose();

		/**
		 * Socket finalisation.
		 */
		// Shutdown the socket.
		_socket->shutdown(boost::asio::socket_base::shutdown_send, error);
		// Close the socket.
		_socket->close();

		if (error) {
			CoreLog->error("Error when shutting down socket from IP {} (error code: {} - {})",
				getRemoteIPAddress(), error.value(), error.message().c_str());
		}
	}

	void delayedCloseSocket() { if (_closing.exchange(true)) return; }

	MessageBuffer &getReadBuffer() { return _readBuffer; }

	/* Game Account Data */
	std::shared_ptr<GameAccount> getGameAccount() const { return _game_account; }
	void setGameAccount(std::shared_ptr<GameAccount> account) { _game_account = account; }
	/* Session Data */
	std::shared_ptr<SessionData> getSessionData() { return _session_data; }
	void setSessionData(std::shared_ptr<SessionData> sess) { _session_data = sess; }

protected:
	virtual void onClose() = 0;
	virtual void readHandler() = 0;

	bool asyncProcessQueue()
	{
		if (_isWritingAsync)
			return false;

		_isWritingAsync = true;

		_socket->async_write_some(boost::asio::null_buffers(), boost::bind(&Socket<SocketType>::writeHandlerWrapper,
				this, boost::placeholders::_1, boost::placeholders::_2));

		return true;
	}

	/**
	 * Disable the Nagle Algorithm on our socket.
	 * @param enable
	 */
	void setNoDelay(bool enable)
	{
		boost::system::error_code error;
		_socket->set_option(tcp::no_delay(enable), error);
		if (error) {
			CoreLog->error("Networking: Socket::setNoDelay: failed to set_option(boost::asio::ip::tcp::no_delay) for IP {} (error_code: {} - {})",
					getRemoteIPAddress(), error.value(), error.message().c_str());
		}
	}

	/**
	 * Write a message to the buffer.
	 * @param to_send
	 * @param error
	 * @return
	 */
	std::size_t writeToBufferAndSend(MessageBuffer &to_send, boost::system::error_code &error)
	{
		std::size_t bytes_to_send = to_send.GetActiveSize();
		std::size_t bytes_sent = _socket->write_some(boost::asio::buffer(to_send.getReadPointer(), bytes_to_send), error);
		return bytes_sent;
	}
private:
	/**
	 * Aysnchronous reading handler method.
	 * @param error
	 * @param transferredBytes
	 */
	void readHandlerInternal(boost::system::error_code error, size_t transferredBytes)
	{
		if (error) {
			closeSocket();
			return;
		}

		if (transferredBytes > 0) {
			_readBuffer.writeCompleted(transferredBytes);
			readHandler();
		}

		asyncRead();
	}

	/**
	 *
	 */
	void writeHandlerWrapper(boost::system::error_code /*error*/, std::size_t /*transferedBytes*/)
	{
		_isWritingAsync = false;
		handleQueue();
	}

	/**
	 * Handle the queue
	 * @return true on success, false on failure.
	 */
	bool handleQueue()
	{
		boost::system::error_code error;

		if (_writeQueue.empty())
			return false;

		MessageBuffer &to_send = _writeQueue.front();
		std::size_t bytes_sent = writeToBufferAndSend(to_send, error);

		if (error == boost::asio::error::would_block || error == boost::asio::error::try_again)
			return asyncProcessQueue();

		/**
		 * Re-process queue if we have remaining bytes.
		 */
		if (!error && bytes_sent < to_send.GetActiveSize()) {
			to_send.readCompleted(bytes_sent);
			return asyncProcessQueue();
		}

		// Pop the front element.
		_writeQueue.pop();
		// Close if required.
		if (_closing && _writeQueue.empty())
			closeSocket();

		return !_writeQueue.empty() && bytes_sent;
	}

private:
	uint64_t _socket_id;
	std::shared_ptr<tcp::socket> _socket;               ///< After accepting, the reference count of this pointer should be 1.
	std::string _remote_ip_address;
	uint16_t _remote_port;
	MessageBuffer _readBuffer;
	std::queue<MessageBuffer> _writeQueue;
	std::atomic<bool> _closed;
	std::atomic<bool> _closing;
	bool _isWritingAsync;
	std::shared_ptr<GameAccount> _game_account;
	std::shared_ptr<SessionData> _session_data;
};

#endif //HORIZON_SOCKET_HPP
