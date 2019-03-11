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

#ifndef HORIZON_CORE_MULTITHREADING_THREADSAFEQUEUE_HPP
#define HORIZON_CORE_MULTITHREADING_THREADSAFEQUEUE_HPP

#include <memory>
#include <thread>
#include <mutex>

template<typename T>
class ThreadSafeQueue
{
private:
    struct node
    {
        std::shared_ptr<T> data;
        std::unique_ptr<node> next;
    };

    std::mutex head_mutex;
    std::unique_ptr<node> head;
    std::mutex tail_mutex;
    node *tail;

    node *get_tail()
    {
		std::unique_lock<std::mutex> tail_lock(tail_mutex);
        return tail;
    }

    std::unique_ptr<node> pop_head()
    {
        std::unique_lock<std::mutex> head_lock(head_mutex);

        if(head.get() == get_tail())
            return nullptr;

        std::unique_ptr<node> old_head = std::move(head);
        head = std::move(old_head->next);
        return old_head;
    }

public:
    ThreadSafeQueue():
        head(new node), tail(head.get())
    {}

	~ThreadSafeQueue()
	{
		std::size_t qsize = size();

		for (std::size_t i = 0; i < qsize; i++)
			try_pop();
	}

    ThreadSafeQueue(const ThreadSafeQueue &other)=delete;
    ThreadSafeQueue &operator=(const ThreadSafeQueue &other)=delete;

    std::shared_ptr<T> try_pop()
    {
        std::unique_ptr<node> old_head = pop_head();
        return old_head ? old_head->data : std::shared_ptr<T>();
    }

    void push(T &&new_value)
    {
        std::shared_ptr<T> new_data(
            std::make_shared<T>(std::move(new_value)));
        std::unique_ptr<node> p(new node);
		node *new_tail = p.get();
        std::unique_lock<std::mutex> tail_lock(tail_mutex);
        tail->data = new_data;
        tail->next = std::move(p);
        tail = new_tail;
    }

	std::size_t size()
	{
		int count = 0;
		std::unique_lock<std::mutex> head_lock(head_mutex);
		std::unique_lock<std::mutex> tail_lock(tail_mutex);
		node const *n = head.get();

		while ((n = n->next.get())) {
			count++;
		}

		return count;
	}

	bool empty()
	{
		std::unique_lock<std::mutex> head_lock(head_mutex);

		if(head.get() == get_tail())
			return true;

		return false;
	}

	std::shared_ptr<T> front()
	{
		std::unique_lock<std::mutex> head_lock(head_mutex);
		std::shared_ptr<T> front = head != nullptr ? std::make_shared<T>(*head->data) : nullptr;
		return std::move(front);
	}
};

#endif // HORIZON_CORE_MULTITHREADING_THREADSAFEQUEUE_HPP
