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

#include "Attributes.hpp"
#include "Server/Zone/Game/Entities/Player/Player.hpp"
#include "Server/Zone/Game/StaticDB/JobDB.hpp"
#include "Server/Zone/Game/StaticDB/ExpDB.hpp"
#include "Server/Zone/Game/Status/Status.hpp"
#include "Server/Zone/Packets/PacketHandler.hpp"
#include "Core/Logging/Logger.hpp"
#include <algorithm>
#include <cassert>
#include <iostream>

using namespace Horizon::Zone::Game::Entities;
using namespace Horizon::Zone::Game::Status;

void BaseExperience::add_base(uint32_t val, bool notify)
{
	assert(val > 0 && val < UINT32_MAX);
	assert(get_entity() != nullptr);

	int32_t job_id = get_entity()->get_job_id();

	assert(job_id > JOB_INVALID && job_id < JOB_MAX);

	std::shared_ptr<const job_db_data> job = JobDB->get(job_id);
	std::shared_ptr<const exp_group_data> bexpg = ExpDB->get_exp_group(job->base_exp_group, EXP_GROUP_TYPE_BASE);

	std::shared_ptr<BaseLevel> base_lv = get_entity()->get_status()->get_base_level();
	std::shared_ptr<NextBaseExperience> next_bexp = get_entity()->get_status()->get_next_base_experience();
	std::shared_ptr<StatusPoint> stpoint = get_entity()->get_status()->get_status_point();

	int total_exp = get_base() + val;
	int blvl = base_lv->get_base();
	do {
		if (*base_lv == bexpg->max_level)
			break;

		if (total_exp < next_bexp->get_base())
			break;

		total_exp -= next_bexp->get_base();
		base_lv->add_base(1, notify);
		base_lv->notify_observers();
		stpoint->add_base(ExpDB->get_status_point(base_lv->get_base()) - ExpDB->get_status_point(base_lv->get_base() - 1), true);
		next_bexp->set_base(bexpg->exp[blvl - 1], notify);
	} while (total_exp > next_bexp->get_base());

	set_base(total_exp, notify);
}

