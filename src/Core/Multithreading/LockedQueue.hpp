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
 * Copyright (C) 2008-2017 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2008 MaNGOS <http://getmangos.com/>
 *
 * Under a proprietary license this file is not for use
 * or viewing without permission.
 **************************************************/

#ifndef HORIZON_LOCKEDQUEUE_H
#define HORIZON_LOCKEDQUEUE_H

#include <deque>
#include <mutex>

/**
 * @brief Thread-safe Locking Queue
 * @tparam T
 * @tparam QueueType
 */
template <class T, typename QueueType = std::deque<T>>
class LockedQueue
{
public:
	/**
	 * @brief Create a LockedQueue.
	 */
    LockedQueue()
        : _canceled(false)
    {
    }

	/**
	 * @brief Destroy a LockedQueue.
	 */
     virtual ~LockedQueue()
    {
    }

	/**
	 * @brief Adds an item to the queue.
	 * @param item
	 */
	void add(const T &item)
    {
        lock();

        _queue.push_back(item);

        unlock();
    }

	/**
	 * @brief Adds items back to front of the queue
	 * @tparam Iterator
	 * @param begin
	 * @param end
	 */
	template<class Iterator>
    void readd(Iterator begin, Iterator end)
    {
        std::lock_guard<std::mutex> lock(_lock);
        _queue.insert(_queue.begin(), begin, end);
    }

	/**
	 * @brief Gets the next result in the queue, if any.
	 * @param result
	 * @return
	 */
	bool next(T &result)
    {
        std::lock_guard<std::mutex> lock(_lock);

        if (_queue.empty())
            return false;

        result = _queue.front();
        _queue.pop_front();

        return true;
    }

	/**
	 * @brief Peeks at the front of the queue,
	 * Checks if the queue is empty before calling!
	 * Remember to unlock after use if unlock == false.
	 * @param unlock
	 * @return
	 */
	T &peek(bool unlock_queue = false)
    {
        lock();

        T &result = _queue.front();

        if (unlock_queue)
            unlock();

        return result;
    }

	/**
	 * @brief Marks the queue as "Cancelled"
	 */
	void cancel()
    {
        std::lock_guard<std::mutex> lock(_lock);

        _canceled = true;
    }

    /**
     * @brief Checks if the queue is cancelled.
     */
     bool cancelled()
    {
        std::lock_guard<std::mutex> lock(_lock);
        return _canceled;
    }

    /**
     * @brief Locks the queue for access.
     */
     void lock()
    {
        this->_lock.lock();
    }

    /**
     * @brief Unlocks the queue.
     */
     void unlock()
    {
        this->_lock.unlock();
    }

    /**
     * @brief Calls pop_front of the queue
     */
     void pop_front()
    {
        std::lock_guard<std::mutex> lock(_lock);
        _queue.pop_front();
    }

    /**
     * @brief Checks if we're empty or not with locks held
     */
     bool empty()
    {
        std::lock_guard<std::mutex> lock(_lock);
        return _queue.empty();
    }

private:
	/*
     * Queue Mutual Lock
	 */
     std::mutex _lock;

	/*
     * The base queue.
	 */
     QueueType _queue;

	/*
     * Cancellation flag.
	 */
     std::atomic<bool> _canceled;
};
#endif // HORIZON_LOCKEDQUEUE_H
