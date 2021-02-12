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

#ifndef HORIZON_CORE_MULTITHREADING_WORKERTHREADPOOL_HPP
#define HORIZON_CORE_MULTITHREADING_WORKERTHREADPOOL_HPP

#include "ThreadSafeQueue.hpp"
#include <thread>
#include <vector>
#include <future>
#include <type_traits>

class FunctionWrapper
{
	struct impl_base
    {
		virtual void call()=0;
		virtual ~impl_base() {}
	};
	template<typename F>
	struct impl_type: impl_base
	{
		F f;
		impl_type(F &&f_): f(std::move(f_)) {}
		void call() { f(); }
	};
public:
	template<typename F>
	FunctionWrapper(F &&f)
    : impl(new impl_type<F>(std::move(f)))
	{}

	void call() { impl->call(); }

	FunctionWrapper(FunctionWrapper &&other)
    : impl(std::move(other.impl))
	{}

	FunctionWrapper &operator= (FunctionWrapper&& other)
	{
		impl = std::move(other.impl);
		return *this;
	}

	FunctionWrapper(const FunctionWrapper&)=delete;
	FunctionWrapper(FunctionWrapper&)=delete;
	FunctionWrapper& operator=(const FunctionWrapper&)=delete;

private:
	std::unique_ptr<impl_base> impl;
};

class WorkerThreadPool
{
public:
	WorkerThreadPool(unsigned const thread_count = std::thread::hardware_concurrency())
	:  _done(false)
	{
		try {
			for (unsigned i = 0; i < thread_count; ++i)
				_threads.push_back(std::thread(&WorkerThreadPool::worker_thread, this));
		} catch (...) {
			_done = true;
			throw;
		}
	}

	~WorkerThreadPool()
	{
		_done = true;

		for (unsigned long i = 0; i < _threads.size(); i++)
			if (_threads.at(i).joinable())
				_threads.at(i).join();
	}

	template<typename FunctionType>
	std::future<typename std::invoke_result<FunctionType()>::type>
	submit(FunctionType f)
	{
		typedef typename std::invoke_result<FunctionType()>::type result_type;

		std::packaged_task<result_type()> task(std::move(f));
		std::future<result_type> res(task.get_future());
		_work_queue.push(std::move(task));
		return res;
	}

private:
	void worker_thread()
	{
		while (!_done) {
			std::shared_ptr<FunctionWrapper> task;
			if ((task = _work_queue.try_pop()))
				task->call();
			else
				std::this_thread::yield();
		}
	}

	std::vector<std::thread> _threads;
	std::atomic_bool _done;
	ThreadSafeQueue<FunctionWrapper> _work_queue;
};

#endif /* HORIZON_CORE_MULTITHREADING_WORKERTHREADPOOL_HPP */
