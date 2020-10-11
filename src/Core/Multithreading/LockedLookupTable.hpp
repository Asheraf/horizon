/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 *
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

#ifndef HORIZON_CORE_MULTITHREADING_LOCKEDLOOKUPTABLE_HPP
#define HORIZON_CORE_MULTITHREADING_LOCKEDLOOKUPTABLE_HPP

#include <iostream>
#include <string>
#include <boost/thread/shared_mutex.hpp>
#include <boost/thread.hpp>
#include <memory>
#include <list>
#include <vector>
#include <utility>

template <typename Key, typename Value, typename Hash = std::hash<Key>>
class LockedLookupTable
{
	class bucket_type;
public:
	typedef Key key_type;
	typedef Value mapped_type;
	typedef Hash hash_type;

	LockedLookupTable(unsigned num_buckets = 19, const Hash &hasher_ = Hash())
	: _buckets(num_buckets), hasher(hasher_)
	{
		for (unsigned i = 0; i < num_buckets; ++i)
			_buckets[i].reset(new bucket_type);
	}

	LockedLookupTable(const LockedLookupTable &other) = delete;
	LockedLookupTable &operator=(const LockedLookupTable &other) = delete;

	Value at(Key const &key, Value const &default_value = Value()) const
	{
		return get_bucket(key).at(key, default_value);
	}

	void insert(const Key &key, const Value &value)
	{
		get_bucket(key).insert(key, value);
	}

	void erase(const Key &key)
	{
		get_bucket(key).erase(key);
	}

	std::map<Key, Value> get_map() const
	{
		std::map<Key, Value> res;

		for (unsigned i = 0; i < _buckets.size(); ++i) {
			boost::unique_lock<boost::shared_mutex> lock(_buckets[i]->_mutex);
			for (typename bucket_type::bucket_iterator it = _buckets[i]->data.begin();
				 it != _buckets[i]->data.end();
				 ++it) {
				res.insert(*it);
			}
		}

		return res;
	}

	int max_collisions() { return _buckets[0]->data.size() ? _buckets[0]->data.size() - 1 : 0; }

	std::size_t size()
	{
		std::size_t count = 0;

		for (unsigned i = 0; i < _buckets.size(); ++i) {
			boost::unique_lock<boost::shared_mutex> lock(_buckets[i]->_mutex);
			for (typename bucket_type::bucket_iterator it = _buckets[i]->data.begin();
				 it != _buckets[i]->data.end();
				 ++it) {
				count++;
			}
		}

		return count;
	}

	void clear()
	{
		for (unsigned i = 0; i < _buckets.size(); ++i) {
			boost::unique_lock<boost::shared_mutex> lock(_buckets[i]->_mutex);
			_buckets[i]->data.clear();
		}
	}
	
private:
	std::vector<std::unique_ptr<bucket_type>> _buckets;
	Hash hasher;

	bucket_type &get_bucket(Key const &key) const
	{
		const std::size_t bucket_index = hasher(key) % _buckets.size();
		return *_buckets[bucket_index];
	}

	class bucket_type
	{
		typedef std::pair<Key, Value> bucket_value;
		typedef std::vector<bucket_value> bucket_data;

	public:
		typedef typename bucket_data::iterator bucket_iterator;

		Value at(Key const &key, Value const &default_value)
		{
			boost::shared_lock<boost::shared_mutex> lock(_mutex);
			bucket_iterator const found_entry = find_entry_for(key);
			return (found_entry == data.end()) ? default_value : found_entry->second;
		}

		void insert(Key const &key, Value const &value)
		{
			boost::unique_lock<boost::shared_mutex> lock(_mutex);
			bucket_iterator found_entry = find_entry_for(key);

			if (found_entry != data.end())
				data.erase(found_entry);

			data.push_back(bucket_value(key, value));
		}

		void erase(Key const &key)
		{
			boost::unique_lock<boost::shared_mutex> lock(_mutex);
			bucket_iterator const found_entry = find_entry_for(key);
			if (found_entry != data.end())
				data.erase(found_entry);
		}

		bucket_data data;
		mutable boost::shared_mutex _mutex;

	private:
		bucket_iterator find_entry_for(Key const &key)
		{
			return std::find_if(data.begin(), data.end(),
				[&](bucket_value const &item)
				{
					return item.first == key;
				});
		}
	};
};

#endif /* HORIZON_CORE_MULTITHREADING_LOCKEDLOOKUPTABLE_HPP */
