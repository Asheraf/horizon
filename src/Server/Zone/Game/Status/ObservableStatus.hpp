/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 * Copyright (c) 2019 Horizon Dev Team.
 *
 * Base Author - Sxyz (sagunxp@gmail.com)
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

#ifndef HORIZON_ZONE_GAME_STATUS_OBSERVABLESTATUS_HPP
#define HORIZON_ZONE_GAME_STATUS_OBSERVABLESTATUS_HPP

#include <tuple>
#include <type_traits>

template <typename OBSERVABLE, typename ... OBSERVERS>
class ObservableStatus
{
public:
	explicit ObservableStatus(OBSERVERS ... args)
	: _observers(args...)
	{
	}
	~ObservableStatus() { }

	template<std::size_t I = 0, typename... Tp>
	inline typename std::enable_if<I == sizeof...(Tp), void>::type
	notify(std::tuple<Tp...>& /*t*/)
	{ }

	template<std::size_t I = 0, typename... Tp>
	inline typename std::enable_if<I < sizeof...(Tp), void>::type
	notify(std::tuple<Tp...>& t)
	{
		std::get<I>(_observers).lock()->on_observable_changed(_observable);
		notify<I + 1, Tp...>(t);
	}

	inline void notify_observers() { notify<0, OBSERVERS...>(_observers); }

	void register_observable(OBSERVABLE obs) { _observable = obs; }
	void register_observers(OBSERVERS... obs) { _observers = std::make_tuple(obs...); }

	OBSERVABLE _observable;
	std::tuple<OBSERVERS...> _observers;
};

#endif /* HORIZON_ZONE_GAME_STATUS_OBSERVABLESTATUS_HPP */
