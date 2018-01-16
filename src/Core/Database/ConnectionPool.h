//
// Created by SagunKho on 29/11/2017.
//

#ifndef HORIZON_CONNECTIONPOOL_H
#define HORIZON_CONNECTIONPOOL_H

#include <deque>
#include <set>
#include <boost/shared_ptr.hpp>
#include <boost/thread/mutex.hpp>
#include <exception>
#include <string>

struct ConnectionUnavailable : std::exception
{
	char const *what() const throw()
	{
		return "Unable to allocate connection";
	};
};


class Connection
{
public:
	Connection()
	{
		//
	};

	virtual ~Connection()
	{
		//
	};

};

class ConnectionFactory
{
public:
	virtual boost::shared_ptr<Connection> create() = 0;
};

struct ConnectionPoolStats
{
	size_t pool_size;
	size_t borrowed_size;
};

template<class T>
class ConnectionPool
{
public:
	ConnectionPoolStats get_stats()
	{
		// Lock
		boost::mutex::scoped_lock lock(this->io_mutex);
		// Get stats
		ConnectionPoolStats stats;
		stats.pool_size = this->pool.size();
		stats.borrowed_size = this->borrowed.size();
		return stats;
	};

	ConnectionPool(size_t pool_size, boost::shared_ptr<ConnectionFactory> factory)
	{
		// Setup
		this->pool_size = pool_size;
		this->factory = factory;

		DBLog->info("Initializing MySQL Connection pool.");

		// Fill the pool
		while (this->pool.size() < this->pool_size) {
			this->pool.push_back(this->factory->create());
		}
	};

	~ConnectionPool()
	{
		// Destructor.
	};

	/**
	 * Borrow a connection for temporary use
	 *
	 * When done, either
	 * (a) call unborrow() to return it, or
	 * (b) (if it's bad) just let it go out of scope.
	 * This will cause it to automatically be replaced.
	 * @retval a shared_ptr to the connection object
	 */
	boost::shared_ptr<T> borrow()
	{
		// Lock
		boost::mutex::scoped_lock lock(this->io_mutex);

		// Check for a free connection
		if (this->pool.size() == 0) {
			// Are there any crashed connections listed as "borrowed"?
			for (auto it = this->borrowed.begin(); it != this->borrowed.end(); ++it){

				if ((*it).unique()) {
					// This connection has been abandoned! Destroy it and create a new connection
					try {
						// If we are able to create a new connection, return it
						DBLog->info("Creating new connection to replace discarded connection.");

						boost::shared_ptr<Connection> conn = this->factory->create();

						this->borrowed.erase(it);
						this->borrowed.insert(conn);

						return boost::static_pointer_cast<T>(conn);

					} catch(std::exception &e) {
						DBLog->error("Unable to connect.");
						// Error creating a replacement connection
						throw ConnectionUnavailable();
					}
				}
			}

			// Nothing available
			throw ConnectionUnavailable();
		}

		// Take one off the front
		boost::shared_ptr<Connection>conn = this->pool.front();

		this->pool.pop_front();

		// Add it to the borrowed list
		this->borrowed.insert(conn);

		return boost::static_pointer_cast<T>(conn);
	};

	/**
	 * Unborrow a connection
	 *
	 * Only call this if you are returning a working connection.  If the connection was bad, just let it go out of scope (so the connection manager can replace it).
	 * @param the connection
	 */
	void unborrow(boost::shared_ptr<T> conn)
	{
		// Lock
		boost::mutex::scoped_lock lock(this->io_mutex);
		// Push onto the pool
		this->pool.push_back(boost::static_pointer_cast<Connection>(conn));
		// Unborrow
		this->borrowed.erase(conn);

	};


protected:
	boost::shared_ptr<ConnectionFactory> factory;
	size_t pool_size;
	std::deque<boost::shared_ptr<Connection>> pool;
	std::set<boost::shared_ptr<Connection>> borrowed;
	boost::mutex io_mutex;

};

#endif //HORIZON_CONNECTIONPOOL_H
