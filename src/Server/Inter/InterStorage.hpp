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

#ifndef HORIZON_INTER_STORAGE_HPP
#define HORIZON_INTER_STORAGE_HPP

#include "Server/Common/Models/SessionData.hpp"
#include "Server/Common/Models/GameAccount.hpp"
#include <map>
#include <boost/thread.hpp>

namespace Horizon
{
namespace Inter
{
template <class StorageType>
class Storage
{
public:
	Storage() {}
	~Storage() {}

	static Storage *getInstance()
	{
		static Storage s;
		return &s;
	}

	/**
	 * @brief Adds a session to the inter storage.
	 * @param[in|out] sess session data reference.
	 */
	void add(uint32_t id, StorageType &data)
	{
		boost::unique_lock<boost::shared_mutex> lock(_storage_lock);

		findAndRemove(id);
		_storage.insert(std::make_pair(id, std::make_shared<StorageType>(data)));
	}

	/**
	 * @brief Removes a session from the inter storage.
	 * @param[in] auth_code identifier for the session data.
	 */
	void remove(uint32_t id)
	{
		boost::unique_lock<boost::shared_mutex> lock(_storage_lock);

		findAndRemove(id);
	}

	/**
	 * @brief Retrieves session data from the inter storage.
	 * @param[in|out] sess session data reference.
	 * @return shared pointer to the session data or null if not found.
	 */
	std::shared_ptr<StorageType> get(uint32_t id)
	{
		boost::shared_lock<boost::shared_mutex> lock(_storage_lock);
		
		auto it = _storage.find(id);

		if (it != _storage.end())
			return it->second;
		else
			return nullptr;
	}

	/**
	 * @brief Retrieves the size of the storage.
	 * @return size of the storage.
	 */
	std::size_t size() { return _storage.size(); }


private:
	/**
	 * @brief Searches and removes an entry from the storage.
	 * @param[in] id session identifier as key.
	 * @return true on success, false on failure.
	 */
	bool findAndRemove(uint32_t id)
	{
		auto it = _storage.find(id);

		if (it != _storage.end()) {
			_storage.erase(id);
			return true;
		}

		return false;
	}

	// Storage Map
	std::map<uint32_t, std::shared_ptr<StorageType>> _storage;
	boost::shared_mutex _storage_lock;
};
}
}

#define SessionStore Horizon::Inter::Storage<SessionData>::getInstance()
#define AccountStore Horizon::Inter::Storage<GameAccount>::getInstance()

#endif // HORIZON_INTER_STORAGE_HPP
