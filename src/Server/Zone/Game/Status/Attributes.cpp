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

template <class STATUS_COST_T, class STATUS_T>
void set_new_point_cost(std::shared_ptr<Horizon::Zone::Game::Entity> entity, STATUS_COST_T *cost_t, std::weak_ptr<STATUS_T> stat)
{
	std::shared_ptr<STATUS_T> sstat = stat.lock();
	if (!entity || !sstat)
		return;

	uint32_t new_cost = entity->get_status()->get_required_statpoints(sstat->get_base(), sstat->get_base() + 1);

	cost_t->set_base(new_cost);
}

void StrengthPointCost::on_observable_changed(std::weak_ptr<Strength> str)
{
	set_new_point_cost(get_entity(), this, str);
}

void AgilityPointCost::on_observable_changed(std::weak_ptr<Agility> agi)
{
	set_new_point_cost(get_entity(), this, agi);
}

void VitalityPointCost::on_observable_changed(std::weak_ptr<Vitality> vit)
{
	set_new_point_cost(get_entity(), this, vit);
}

void IntelligencePointCost::on_observable_changed(std::weak_ptr<Intelligence> _int)
{
	set_new_point_cost(get_entity(), this, _int);
}

void DexterityPointCost::on_observable_changed(std::weak_ptr<Dexterity> dex)
{
	set_new_point_cost(get_entity(), this, dex);
}

void LuckPointCost::on_observable_changed(std::weak_ptr<Luck> luk)
{
	set_new_point_cost(get_entity(), this, luk);
}

void BaseLevel::on_observable_changed(std::weak_ptr<BaseExperience> wbexp)
{
	std::shared_ptr<BaseExperience> bexp = wbexp.lock();

	if (get_entity() == nullptr || wbexp.expired())
		return;

	if (get_base() >= MAX_LEVEL)
		return;

	if (bexp->get_base() == get_entity()->get_status()->get_next_base_experience()->get_base()) {
		add_base(1);
		bexp->set_base(0);
	}
}

void JobLevel::on_observable_changed(std::weak_ptr<JobExperience> wjexp)
{
	std::shared_ptr<JobExperience> jexp = wjexp.lock();

	if (get_entity() == nullptr || wjexp.expired())
		return;

	if (jexp->get_base() == get_entity()->get_status()->get_next_job_experience()->get_base()) {
		add_base(1);
		jexp->set_base(0);
	}
}

void NextBaseExperience::on_observable_changed(std::weak_ptr<BaseLevel> wblvl)
{
	if (get_entity() == nullptr || wblvl.expired())
		return;

	std::shared_ptr<BaseLevel> blvl = wblvl.lock();
	std::shared_ptr<const job_db_data> job = JobDB->get(get_entity()->get_job_id());
	std::shared_ptr<const exp_group_data> bexpg = ExpDB->get_exp_group(job->base_exp_group, EXP_GROUP_TYPE_BASE);

	set_base(bexpg->exp[blvl->get_base() - 1]);
}

void NextJobExperience::on_observable_changed(std::weak_ptr<JobLevel> jlvl)
{
	if (get_entity() == nullptr || jlvl.expired())
		return;

	std::shared_ptr<const job_db_data> job = JobDB->get(get_entity()->get_job_id());
	std::shared_ptr<const exp_group_data> jexpg = ExpDB->get_exp_group(job->job_exp_group, EXP_GROUP_TYPE_JOB);

	set_base(jexpg->exp[get_base() - 1]);
}

void StatusPoint::on_observable_changed(std::weak_ptr<BaseLevel> wblvl)
{
	std::shared_ptr<BaseLevel> blvl = wblvl.lock();

	if (get_entity() == nullptr || wblvl.expired())
		return;

	add_base(ExpDB->get_status_point(blvl->get_base()) - ExpDB->get_status_point(*blvl - 1));
}

void SkillPoint::on_observable_changed(std::weak_ptr<JobLevel> wjlvl)
{
	std::shared_ptr<JobLevel> jlvl = wjlvl.lock();

	if (get_entity() == nullptr || wjlvl.expired())
		return;

	add_base(1);
}
