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

#include "GridNotifiers.hpp"

#include "Server/Zone/Session/ZoneSession.hpp"
#include "Server/Zone/Game/Map/Grid/GridRefManager.hpp"

void GridPlayerNotifier::notify(GridRefManager<Horizon::Zone::Entities::Player> &m)
{
	using namespace Horizon::Zone::Entities;

	std::shared_ptr<Player> pl = _entity.lock()->template downcast<Player>();

	if (pl == nullptr)
		return;

	for (typename GridRefManager<Player>::iterator iter = m.begin(); iter != typename GridRefManager<Player>::iterator(nullptr); ++iter) {
		if (iter->source() == nullptr)
			continue;

		switch (_type)
		{
			case GRID_NOTIFY_AREA_WOS:
				if (iter->source()->guid() == pl->guid())
					continue;
			default:
				break;
		}
		iter->source()->get_session()->transmit_buffer(_buf, _buf.active_length());
	}
}
