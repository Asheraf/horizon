#ifndef HORIZON_NETWORKING_SESSION_HPP
#define HORIZON_NETWORKING_SESSION_HPP

#include <memory>

namespace Horizon
{
namespace Networking
{
template <class SocketType>
class Session
{
public:
	Session(std::weak_ptr<SocketType> socket)
	: _socket(socket)
	{
		//
	}

	~Session()
	{
		//
	}

	/* Socket Type */
	std::shared_ptr<SocketType> get_socket() { return _socket.lock(); }
	void set_socket(std::weak_ptr<SocketType> socket) { _socket.swap(socket); }

	virtual void update(uint32_t diff) = 0;

	virtual void initialize() = 0;

private:
	std::weak_ptr<SocketType> _socket;
};
}
}

#endif /* HORIZON_NETWORKING_SESSION_HPP */
