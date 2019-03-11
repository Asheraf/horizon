/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
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

#ifndef HORIZON_NETWORKING_SOCKET_HPP
#define HORIZON_NETWORKING_SOCKET_HPP

#include "Core/Logging/Logger.hpp"
#include "Buffer/MessageBuffer.hpp"
#include "Core/Multithreading/ThreadSafeQueue.hpp"

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

namespace Horizon
{
namespace Networking
{
template <class SocketType>
class Socket : public std::enable_shared_from_this<SocketType>
{
public:
	explicit Socket(std::shared_ptr<tcp::socket> socket)
	: _socket_id(0), _socket(socket), _remote_ip_address(_socket->remote_endpoint().address().to_string()),
	_remote_port(_socket->remote_endpoint().port()), _read_buffer(), _closed(false), _closing(false), _is_writing_async(false)
	{
		_read_buffer.resize(READ_BLOCK_SIZE);
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

		if (_is_writing_async || (_write_queue.empty() && !_closing))
			return true;

		while (handle_queue())
			;

		return true;
	}

	/* Socket Id */
	uint64_t get_socket_id() { return _socket_id; }
	void set_socket_id(uint64_t socket_id) { _socket_id = socket_id; }

	/* Remote IP and Port */
	std::string &remote_ip_address() { return _remote_ip_address; }
	uint16_t remote_port() const { return _remote_port; }

	void async_read()
	{
		if (!is_open())
			return;

		_read_buffer.normalize();
		_read_buffer.ensureFreeSpace();

		_socket->async_read_some(boost::asio::buffer(_read_buffer.get_write_pointer(), _read_buffer.get_remaining_space()),
								 boost::bind(&Socket<SocketType>::read_handler_internal, this, boost::placeholders::_1, boost::placeholders::_2));
	}

	void async_read_with_callback(MessageBuffer &buf, void (Socket<SocketType>::*/*callback*/)(boost::system::error_code, std::size_t))
	{
		if (!is_open())
			return;

		_read_buffer.normalize();
		_read_buffer.ensureFreeSpace();

		_socket->async_read_some(boost::asio::buffer(buf.get_write_pointer(), buf.get_remaining_space()),
								 boost::bind(&Socket<SocketType>::read_handler_internal, this, boost::placeholders::_1, boost::placeholders::_2));
	}

	/**
	 * Synchronous reading.
	 * @return size of the read buffer.
	 */
	std::size_t sync_read(MessageBuffer &buf, std::size_t read_size)
	{
		std::size_t size = 0;

		try {
			size = _socket->read_some(boost::asio::buffer(buf.get_write_pointer(), read_size));
			buf.write_completed(size);
		} catch (boost::system::system_error &e) {
			CoreLog->info("Error '{}' while reading data from client at {}.", e.what(), _remote_ip_address);
		}

		return size;
	}

	/**
	 * Synchronous writing.
	 * @return size of the written buffer.
	 */
	std::size_t sync_write(MessageBuffer &message, std::size_t bytes_to_send)
	{
		boost::system::error_code error;
		std::size_t size = 0;

		try {
			size = _socket->write_some(boost::asio::buffer(message.get_read_pointer(), bytes_to_send), error);
			message.read_completed(size);
		} catch (boost::system::system_error &e) {
			CoreLog->info("Error '{}' while writing data to client at {}.", e.what(), _remote_ip_address);
		}

		return size;
	}

	void queue_packet(MessageBuffer &&buffer) { _write_queue.push(std::move(buffer)); }

	bool is_open() { return !_closed && !_closing; }

	void close_socket()
	{
		boost::system::error_code socket_error;

		if (_closed.exchange(true))
			return;

		// Finalise the child-class socket first.
		on_close();

		/**
		 * Socket finalisation.
		 */
		// Shutdown the socket.
		_socket->shutdown(boost::asio::socket_base::shutdown_send, socket_error);
		// Close the socket.
		_socket->close();

		if (socket_error) {
			CoreLog->error("Error when shutting down socket from IP {} (error code: {} - {})",
						   remote_ip_address(), socket_error.value(), socket_error.message().c_str());
		}
	}

	void delayed_close_socket() { if (_closing.exchange(true)) return; }

	MessageBuffer &get_read_buffer() { return _read_buffer; }

protected:
	virtual void on_close() = 0;
	virtual void read_handler() = 0;
	virtual void on_error() = 0;

	bool async_process_queue()
	{
		if (_is_writing_async)
			return false;

		_is_writing_async = true;

		_socket->async_write_some(boost::asio::null_buffers(),
								  boost::bind(&Socket<SocketType>::write_handler_wrapper,
											  this, boost::placeholders::_1, boost::placeholders::_2));

		return true;
	}

	/**
	 * Disable the Nagle Algorithm on our socket.
	 * @param enable
	 */
	void set_no_delay(bool enable)
	{
		boost::system::error_code error;
		_socket->set_option(tcp::no_delay(enable), error);
		if (error) {
			CoreLog->error("Networking: Socket::set_no_delay: failed to set_option(boost::asio::ip::tcp::no_delay) for IP {} (error_code: {} - {})",
						   remote_ip_address(), error.value(), error.message().c_str());
		}
	}

	/**
	 * Write a message to the buffer.
	 * @param to_send
	 * @param error
	 * @return
	 */
	std::size_t write_buffer_and_send(MessageBuffer &to_send, boost::system::error_code &error)
	{
		std::size_t bytes_to_send = to_send.get_active_size();
		std::size_t bytes_sent = _socket->write_some(boost::asio::buffer(to_send.get_read_pointer(), bytes_to_send), error);
		return bytes_sent;
	}
private:
	/**
	 * Aysnchronous reading handler method.
	 * @param error
	 * @param transferredBytes
	 */
	void read_handler_internal(boost::system::error_code error, size_t transferredBytes)
	{
		if (error) {
			if (error.value() == boost::asio::error::eof) {
				close_socket();
			} else if (error.value() == boost::system::errc::connection_reset
					   || error.value() == boost::system::errc::timed_out) {
				on_error();
				close_socket();
			} else {
				on_error();
				close_socket();
				CoreLog->debug("Socket::read_handler_internal: {} (Code: {}).", error.value(), error.message());
			}
			return;
		}

		if (transferredBytes > 0) {
			_read_buffer.write_completed(transferredBytes);
			read_handler();
		}

		async_read();
	}

	/**
	 *
	 */
	void write_handler_wrapper(boost::system::error_code /*error*/, std::size_t /*transferedBytes*/)
	{
		_is_writing_async = false;
		handle_queue();
	}

	/**
	 * Handle the queue
	 * @return true on success, false on failure.
	 */
	bool handle_queue()
	{
		boost::system::error_code error;

		if (_write_queue.empty())
			return false;

		std::shared_ptr<MessageBuffer> to_send = _write_queue.front();

		std::size_t bytes_sent = write_buffer_and_send(*to_send, error);

		if (error == boost::asio::error::would_block || error == boost::asio::error::try_again)
			return async_process_queue();

		/**
		 * Re-process queue if we have remaining bytes.
		 */
		if (!error && bytes_sent < to_send->get_active_size()) {
			to_send->read_completed(bytes_sent);
			return async_process_queue();
		}

		// Pop the front element.
		_write_queue.try_pop();

		// Close if required.
		if (_closing && _write_queue.empty())
			close_socket();

		return !_write_queue.empty() && bytes_sent;
	}

private:
	uint64_t _socket_id;
	std::shared_ptr<tcp::socket> _socket;               ///< After accepting, the reference count of this pointer should be 1.
	std::string _remote_ip_address;
	uint16_t _remote_port;
	MessageBuffer _read_buffer;
	ThreadSafeQueue<MessageBuffer> _write_queue;
	std::atomic<bool> _closed;
	std::atomic<bool> _closing;
	bool _is_writing_async;
};
}
}

#endif //HORIZON_NETWORKING_SOCKET_HPP
