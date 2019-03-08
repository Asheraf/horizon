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

#include "Status.hpp"
#include "Server/Common/Definitions/Horizon.hpp"
#include "Server/Common/Models/Character/Character.hpp"
#include "Server/Common/Models/Character/Status.hpp"
#include "Server/Zone/Game/StaticDB/JobDB.hpp"
#include "Server/Zone/Game/StaticDB/ExpDB.hpp"
#include "Server/Zone/Game/Status/Appearance.hpp"
#include "Server/Zone/Game/Status/Attributes.hpp"
#include "Server/Zone/Game/Status/SubAttributes.hpp"
#include "Server/Zone/Game/Status/ObservableStatus.hpp"
#include "Server/Zone/Game/Entities/Player/Player.hpp"
#include "Server/Zone/Packets/PacketHandler.hpp"
#include <stdio.h>

using namespace Horizon::Zone::Game::Status;
using namespace Horizon::Models;

void Status::initialize()
{
	set_movement_speed(std::make_shared<MovementSpeed>(_entity, DEFAULT_MOVEMENT_SPEED));

	set_base_level(std::make_shared<BaseLevel>(_entity, 1));
	set_job_level(std::make_shared<JobLevel>(_entity, 1));

	set_current_hp(std::make_shared<CurrentHP>(_entity, 1));
	set_current_sp(std::make_shared<CurrentSP>(_entity, 1));
	set_max_hp(std::make_shared<MaxHP>(_entity, 1));
	set_max_sp(std::make_shared<MaxSP>(_entity, 1));

	set_hair_color(std::make_shared<HairColor>(_entity, 0));
	set_cloth_color(std::make_shared<ClothColor>(_entity, 0));
	set_head_top_sprite(std::make_shared<HeadTopSprite>(_entity, 0));
	set_head_mid_sprite(std::make_shared<HeadMidSprite>(_entity, 0));
	set_head_bottom_sprite(std::make_shared<HeadBottomSprite>(_entity, 0));
	set_hair_style(std::make_shared<HairStyle>(_entity, 0));
	set_shield_sprite(std::make_shared<ShieldSprite>(_entity, 0));
	set_weapon_sprite(std::make_shared<WeaponSprite>(_entity, 0));
	set_robe_sprite(std::make_shared<RobeSprite>(_entity, 0));
	set_body_style(std::make_shared<BodyStyle>(_entity, 0));
}

void Status::initialize(std::shared_ptr<Character::Character> character)
{
	std::shared_ptr<Horizon::Models::Character::Status> status_model = character->get_status_model();
	std::shared_ptr<const job_db_data> job = JobDB->get(status_model->get_job_id());
	std::shared_ptr<const exp_group_data> bexpg = ExpDB->get_exp_group(job->base_exp_group, EXP_GROUP_TYPE_BASE);
	std::shared_ptr<const exp_group_data> jexpg = ExpDB->get_exp_group(job->job_exp_group, EXP_GROUP_TYPE_JOB);

	uint32_t str = status_model->get_strength();
	uint32_t agi = status_model->get_agility();
	uint32_t vit = status_model->get_vitality();
	uint32_t _int = status_model->get_intelligence();
	uint32_t dex = status_model->get_dexterity();
	uint32_t luk = status_model->get_luck();

	// Status Data

	/**
	 * Main Attributes.
	 */
	// Strength
	set_strength(std::make_shared<Strength>(_entity, str));
	set_agility(std::make_shared<Agility>(_entity, agi, 0, 0));
	set_vitality(std::make_shared<Vitality>(_entity, vit, 0, 0));
	set_intelligence(std::make_shared<Intelligence>(_entity, _int, 0, 0));
	set_dexterity(std::make_shared<Dexterity>(_entity, dex, 0, 0));
	set_luck(std::make_shared<Luck>(_entity, luk, 0, 0));

	set_strength_cost(std::make_shared<StrengthPointCost>(_entity, get_required_statpoints(str, str + 1)));
	set_agility_cost(std::make_shared<AgilityPointCost>(_entity, get_required_statpoints(agi, agi + 1)));
	set_vitality_cost(std::make_shared<VitalityPointCost>(_entity, get_required_statpoints(vit, vit + 1)));
	set_intelligence_cost(std::make_shared<IntelligencePointCost>(_entity, get_required_statpoints(_int, _int + 1)));
	set_dexterity_cost(std::make_shared<DexterityPointCost>(_entity, get_required_statpoints(dex, dex + 1)));
	set_luck_cost(std::make_shared<LuckPointCost>(_entity, get_required_statpoints(luk, luk + 1)));

	set_status_point(std::make_shared<StatusPoint>(_entity, status_model->get_status_points()));
	set_skill_point(std::make_shared<SkillPoint>(_entity, status_model->get_skill_points()));

	set_current_hp(std::make_shared<CurrentHP>(_entity, status_model->get_hp()));
	set_current_sp(std::make_shared<CurrentSP>(_entity, status_model->get_sp()));
	set_max_hp(std::make_shared<MaxHP>(_entity, status_model->get_max_hp()));
	set_max_sp(std::make_shared<MaxSP>(_entity, status_model->get_max_sp()));

	set_base_level(std::make_shared<BaseLevel>(_entity, status_model->get_base_level()));
	set_job_level(std::make_shared<JobLevel>(_entity, status_model->get_job_level()));

	set_base_experience(std::make_shared<BaseExperience>(_entity, status_model->get_base_exp()));
	set_job_experience(std::make_shared<JobExperience>(_entity, status_model->get_job_exp()));
	set_next_base_experience(std::make_shared<NextBaseExperience>(_entity, bexpg->exp[status_model->get_base_level() - 1]));
	set_next_job_experience(std::make_shared<NextJobExperience>(_entity, bexpg->exp[status_model->get_job_level() - 1]));
	set_max_weight(std::make_shared<MaxWeight>(_entity, job->max_weight));
	set_current_weight(std::make_shared<CurrentWeight>(_entity, 0));
	set_movement_speed(std::make_shared<MovementSpeed>(_entity, DEFAULT_MOVEMENT_SPEED));

	set_hair_color(std::make_shared<HairColor>(_entity, status_model->get_hair_color_id()));
	set_cloth_color(std::make_shared<ClothColor>(_entity, status_model->get_cloth_color_id()));
	set_head_top_sprite(std::make_shared<HeadTopSprite>(_entity, status_model->get_head_top_view_id()));
	set_head_mid_sprite(std::make_shared<HeadMidSprite>(_entity, status_model->get_head_mid_view_id()));
	set_head_bottom_sprite(std::make_shared<HeadBottomSprite>(_entity, status_model->get_head_bottom_view_id()));
	set_hair_style(std::make_shared<HairStyle>(_entity, status_model->get_hair_style_id()));
	set_shield_sprite(std::make_shared<ShieldSprite>(_entity, status_model->get_shield_id()));
	set_weapon_sprite(std::make_shared<WeaponSprite>(_entity, status_model->get_weapon_id()));
	set_robe_sprite(std::make_shared<RobeSprite>(_entity, status_model->get_robe_view_id()));
	set_body_style(std::make_shared<BodyStyle>(_entity, status_model->get_body_id()));

	initialize_sub_attributes();
	initialize_observable_statuses();

	if (get_entity()->get_type() == ENTITY_PLAYER) {
		get_entity()->downcast<Entities::Player>()->get_packet_handler()->Send_ZC_STATUS();
	}
}

void Status::initialize_sub_attributes()
{
	set_status_atk(std::make_shared<StatusATK>(_entity));
	get_status_atk()->set_base_level(get_base_level());
	get_status_atk()->set_strength(get_strength());
	get_status_atk()->set_dexterity(get_dexterity());
	get_status_atk()->set_luck(get_luck());
	get_status_atk()->set_base(get_status_atk()->compute(), true);

	set_status_matk(std::make_shared<StatusMATK>(_entity));
	get_status_matk()->set_base_level(get_base_level());
	get_status_matk()->set_intelligence(get_intelligence());
	get_status_matk()->set_dexterity(get_dexterity());
	get_status_matk()->set_luck(get_luck());
	get_status_matk()->set_base(get_status_matk()->compute(), true);

	set_soft_def(std::make_shared<SoftDEF>(_entity));
	get_soft_def()->set_vitality(get_vitality());
	get_soft_def()->set_base(get_soft_def()->compute(), true);

	set_soft_mdef(std::make_shared<SoftMDEF>(_entity));
	get_soft_mdef()->set_base_level(get_base_level());
	get_soft_mdef()->set_intelligence(get_intelligence());
	get_soft_mdef()->set_dexterity(get_dexterity());
	get_soft_mdef()->set_vitality(get_vitality());
	get_soft_mdef()->set_base(get_status_matk()->compute(), true);

	set_hit(std::make_shared<HIT>(_entity));
	get_hit()->set_base_level(get_base_level());
	get_hit()->set_dexterity(get_dexterity());
	get_hit()->set_luck(get_luck());
	get_hit()->set_base(get_hit()->compute(), true);

	set_crit(std::make_shared<CRIT>(_entity));
	get_crit()->set_luck(get_luck());
	get_crit()->set_base(get_crit()->compute(), true);

	set_flee(std::make_shared<FLEE>(_entity));
	get_flee()->set_base_level(get_base_level());
	get_flee()->set_agility(get_agility());
	get_flee()->set_luck(get_luck());
	get_flee()->set_base(get_flee()->compute(), true);
}

void Status::initialize_observable_statuses()
{
	// Register Status Observables
	get_strength()->register_observable(get_strength());
	get_agility()->register_observable(get_agility());
	get_vitality()->register_observable(get_vitality());
	get_intelligence()->register_observable(get_intelligence());
	get_dexterity()->register_observable(get_dexterity());
	get_luck()->register_observable(get_luck());
	get_base_level()->register_observable(get_base_level());

	// Register Status Observers
	get_strength()->register_observers(get_status_atk());
	get_agility()->register_observers(get_flee());
	get_intelligence()->register_observers(get_status_matk(), get_soft_mdef());
	get_dexterity()->register_observers(get_status_atk(), get_status_matk(), get_soft_mdef(), get_hit());
	get_luck()->register_observers(get_status_atk(), get_status_matk(), get_hit(), get_crit(), get_flee());
	get_base_level()->register_observers(get_status_atk(), get_status_matk(), get_soft_mdef(), get_hit(), get_flee());
	get_vitality()->register_observers(get_soft_def(), get_soft_mdef());
}

uint32_t Status::get_required_statpoints(uint16_t from, uint16_t to)
{
	uint32_t sp = 0;

	for (; from < to; from++)
		sp += (from < 100) ? (2 + (from - 1) / 10) : (16 + 4 * ((from - 100) / 5));

	return sp;
}

uint32_t Status::get_status_total(status_point_type type)
{
	uint32_t value = 0;
	switch (type)
	{
		case STATUS_STRENGTH: value = get_strength()->get_base(); break;
		case STATUS_AGILITY: value = get_agility()->get_base(); break;
		case STATUS_VITALITY: value = get_vitality()->get_base(); break;
		case STATUS_INTELLIGENCE: value = get_intelligence()->get_base(); break;
		case STATUS_DEXTERITY: value = get_dexterity()->get_base(); break;
		case STATUS_LUCK: value = get_luck()->get_base(); break;
		default: return 0;
	}

	return value;
}

uint32_t Status::increase_status_point(status_point_type type, uint16_t limit)
{
	uint32_t value = 0;

	if (limit <= 0 || limit > MAX_STATUS_POINTS)
		return 0;

	if (_entity.expired())
		return 0;

	uint32_t available_points = get_status_point()->get_base();
	uint32_t required_points = 0;

	limit += get_status_total(type);

	do {
		value = get_status_total(type);
		required_points = get_required_statpoints(value + 1, value + 2);

		if (required_points > available_points)
			break;

		available_points -= required_points;

		switch (type)
		{
			case STATUS_STRENGTH:
				get_strength()->add_base(1);
				get_strength()->notify_observers();
				if (get_strength_cost()->get_base() != required_points)
					get_strength_cost()->set_base(required_points, true);
				break;
			case STATUS_AGILITY:
				get_agility()->add_base(1);
				get_agility()->notify_observers();
				if (get_agility_cost()->get_base() != required_points)
					get_agility_cost()->set_base(required_points, true);
				break;
			case STATUS_VITALITY:
				get_vitality()->add_base(1);
				get_vitality()->notify_observers();
				if (get_vitality_cost()->get_base() != required_points)
					get_vitality_cost()->set_base(required_points, true);
				break;
			case STATUS_INTELLIGENCE:
				get_intelligence()->add_base(1);
				get_intelligence()->notify_observers();
				if (get_intelligence_cost()->get_base() != required_points)
					get_intelligence_cost()->set_base(required_points, true);
				break;
			case STATUS_DEXTERITY:
				get_dexterity()->add_base(1);
				get_dexterity()->notify_observers();
				if (get_dexterity_cost()->get_base() != required_points)
					get_dexterity_cost()->set_base(required_points, true);
				break;
			case STATUS_LUCK:
				get_luck()->add_base(1);
				get_luck()->notify_observers();
				if (get_luck_cost()->get_base() != required_points)
					get_luck_cost()->set_base(required_points, true);
				break;
			default: return false;
		}

		get_status_point()->set_base(available_points, true);
	} while (get_status_total(type) < limit);

	return get_status_total(type);
}

bool Status::sync_to_model(std::shared_ptr<Models::Character::Status> status)
{
	if (get_strength()->get_base() == status->get_strength()
		&& get_agility()->get_base() == status->get_agility()
		&& get_vitality()->get_base() == status->get_vitality()
		&& get_intelligence()->get_base() == status->get_intelligence()
		&& get_dexterity()->get_base() == status->get_dexterity()
		&& get_luck()->get_base() == status->get_luck()
		&& get_status_point()->get_base() == status->get_status_points()
		&& get_skill_point()->get_base() == status->get_skill_points()
		&& get_max_hp()->get_base() == status->get_max_hp()
		&& get_max_sp()->get_base() == status->get_max_sp()
		&& get_current_hp()->get_base() == status->get_hp()
		&& get_current_sp()->get_base() == status->get_sp()
		&& get_base_level()->get_base() == status->get_base_level()
		&& get_job_level()->get_base() == status->get_job_level()
		&& get_base_experience()->get_base() == status->get_base_exp()
		&& get_job_experience()->get_base() == status->get_job_exp()
		&& get_hair_color()->get() == status->get_hair_color_id()
		&& get_cloth_color()->get() == status->get_cloth_color_id()
		&& get_weapon_sprite()->get() == status->get_weapon_id()
		&& get_shield_sprite()->get() == status->get_shield_id()
		&& get_robe_sprite()->get() == status->get_robe_view_id()
		&& get_head_top_sprite()->get() == status->get_head_top_view_id()
		&& get_head_mid_sprite()->get() == status->get_head_mid_view_id()
		&& get_head_bottom_sprite()->get() == status->get_head_bottom_view_id()
		&& get_hair_style()->get() == status->get_hair_style_id()
		&& get_body_style()->get() == status->get_body_id())
		return true;

	status->set_strength(get_strength()->get_base());
	status->set_agility(get_agility()->get_base());
	status->set_vitality(get_vitality()->get_base());
	status->set_intelligence(get_intelligence()->get_base());
	status->set_dexterity(get_dexterity()->get_base());
	status->set_luck(get_luck()->get_base());
	status->set_status_points(get_status_point()->get_base());
	status->set_skill_points(get_skill_point()->get_base());
	status->set_max_hp(get_max_hp()->get_base());
	status->set_max_sp(get_max_sp()->get_base());
	status->set_sp(get_current_hp()->get_base());
	status->set_hp(get_current_sp()->get_base());
	status->set_base_level(get_base_level()->get_base());
	status->set_job_level(get_job_level()->get_base());
	status->set_base_exp(get_base_experience()->get_base());
	status->set_job_exp(get_job_experience()->get_base());
	status->set_hair_color_id(get_hair_color()->get());
	status->set_hair_color_id(get_cloth_color()->get());
	status->set_hair_color_id(get_weapon_sprite()->get());
	status->set_hair_color_id(get_shield_sprite()->get());
	status->set_hair_color_id(get_robe_sprite()->get());
	status->set_hair_color_id(get_head_top_sprite()->get());
	status->set_hair_color_id(get_head_mid_sprite()->get());
	status->set_hair_color_id(get_head_bottom_sprite()->get());
	status->set_hair_color_id(get_hair_style()->get());
	status->set_hair_color_id(get_body_style()->get());

	return false;
}
