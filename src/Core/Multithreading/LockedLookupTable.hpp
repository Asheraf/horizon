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

#ifndef HORIZON_CORE_MULTITHREADING_LOCKEDLOOKUPTABLE_HPP
#define HORIZON_CORE_MULTITHREADING_LOCKEDLOOKUPTABLE_HPP

#include <iostream>
#include <string>
#include <thread>
#include <boost/thread/shared_mutex.hpp>
#include <memory>
#include <list>
#include <vector>

template <typename Key, typename Value, typename Hash=std::hash<Key>>
class LockedLookupTable
{
class bucket_type;
public:
	typedef Key key_type;
	typedef Value mapped_type;
	typedef Hash hash_type;

	LockedLookupTable(unsigned num_buckets = 19, const Hash &hasher_ = Hash())
	: buckets(num_buckets), hasher(hasher_)
	{
		for (unsigned i = 0; i < num_buckets; ++i)
			buckets[i].reset(new bucket_type);
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
		std::vector<boost::unique_lock<boost::shared_mutex>> locks;
		std::map<Key, Value> res;

		for (unsigned i = 0;  i < buckets.size(); ++i)
			locks.push_back(boost::unique_lock<boost::shared_mutex>(buckets[i]->_mutex));

		for (unsigned i = 0; i < buckets.size(); ++i) {
			for (typename bucket_type::bucket_iterator it = buckets[i]->data.begin();
				 it != buckets[i]->data.end();
				 ++it) {
				res.insert(*it);
			}
		}

		return res;
	}

	int max_collisions() { return buckets[0]->data.size() ? buckets[0]->data.size() - 1 : 0; }
	std::size_t size()
	{
		std::vector<boost::unique_lock<boost::shared_mutex>> locks;
		std::size_t count = 0;

		for (unsigned i = 0;  i < buckets.size(); ++i)
			locks.push_back(boost::unique_lock<boost::shared_mutex>(buckets[i]->_mutex));

		for (unsigned i = 0; i < buckets.size(); ++i) {
			for (typename bucket_type::bucket_iterator it = buckets[i]->data.begin();
				 it != buckets[i]->data.end();
				 ++it) {
				count++;
			}
		}

		return count;
	}
private:
	std::vector<std::unique_ptr<bucket_type>> buckets;
	Hash hasher;

	bucket_type &get_bucket(Key const &key) const
	{
		const std::size_t bucket_index = hasher(key) % buckets.size();
		return *buckets[bucket_index];
	}

	class bucket_type
	{
		typedef std::pair<Key, Value> bucket_value;
		typedef std::list<bucket_value> bucket_data;
	
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
