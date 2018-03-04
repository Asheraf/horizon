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
 * Under a proprietary license this file is not for use
 * or viewing without permission.
 **************************************************/

#ifndef HORIZON_CORE_MULTITHREADING_THREADSAFEQUEUE_HPP
#define HORIZON_CORE_MULTITHREADING_THREADSAFEQUEUE_HPP

#include <memory>
#include <boost/thread.hpp>

template<typename T>
class ThreadSafeQueue
{
private:
    struct node
    {
        std::shared_ptr<T> data;
        std::unique_ptr<node> next;
    };

    boost::mutex head_mutex;
    std::unique_ptr<node> head;
    boost::mutex tail_mutex;
    node *tail;

    node *get_tail()
    {
		boost::unique_lock<boost::mutex> tail_lock(tail_mutex);
        return tail;
    }

    std::unique_ptr<node> pop_head()
    {
        boost::unique_lock<boost::mutex> head_lock(head_mutex);

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
        boost::unique_lock<boost::mutex> tail_lock(tail_mutex);
        tail->data = new_data;
        tail->next = std::move(p);
        tail = new_tail;
    }

	std::size_t size()
	{
		int count = 0;
		boost::unique_lock<boost::mutex> head_lock(head_mutex);
		boost::unique_lock<boost::mutex> tail_lock(tail_mutex);
		node const *n = head.get();

		while ((n = n->next.get())) {
			count++;
		}

		return count;
	}
};

#endif // HORIZON_CORE_MULTITHREADING_THREADSAFEQUEUE_HPP
