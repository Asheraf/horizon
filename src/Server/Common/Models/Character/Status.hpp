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

#ifndef HORIZON_MODELS_CHARACTERS_STATUSDATA_HPP
#define HORIZON_MODELS_CHARACTERS_STATUSDATA_HPP

#include <cstdint>

class Server;

namespace Horizon
{
namespace Models
{
namespace Character
{
class Status
{
public:

	Status(uint32_t char_id)
	: _character_id(char_id), _base_level(1), _job_level(1), _zeny(0)
	{
		//
	}

	Status(uint32_t z, uint8_t str, uint8_t agi, uint8_t int_, uint8_t vit, uint8_t dex, uint8_t luk)
	: _base_level(1), _job_level(1), _zeny(z), _strength(str), _agility(agi), _vitality(vit), _intelligence(int_), _dexterity(dex), _luck(luk)
	{
		_hp = _maximum_hp = (40 * (100 + vit)/100);
		_sp = _maximum_sp = (11 * (100 + int_)/100);
	}

	~Status() {}

	/**
	 * Load all fields from the database into this instance.
	 * @param server
	 * @param char_id
	 * @return
	 */
	bool load(Server *server, uint32_t char_id);

	/**
	 * @brief Save this model to the database in its current state.
	 * @param[in|out] server   instance of the server object used to borrow mysql connections.
	 */
	bool save(Server *server);

	/* Character ID */
	uint32_t get_character_id() const { return _character_id; }
	void set_character_id(uint32_t character_id) { _character_id = character_id; }
	/* Job Class */
	uint16_t get_job_id() const { return _job_id; }
	void set_job_id(uint16_t id) { _job_id = id; }
	/* Base Level */
	uint16_t get_base_level() const { return _base_level; }
	void set_base_level(uint16_t base_level) { _base_level = base_level; }
	/* Job Level */
	uint16_t get_job_level() const { return _job_level; }
	void set_job_level(uint16_t job_level) { _job_level = job_level; }
	/* Base Experience */
	uint64_t get_base_exp() const { return _base_experience; }
	void set_base_exp(uint64_t base_experience) { _base_experience = base_experience; }
	/* Job Experience */
	uint64_t get_job_exp() const { return _job_experience; }
	void set_job_exp(uint64_t job_experience) { _job_experience = job_experience; }
	/* Zeny */
	uint32_t get_zeny() const { return _zeny; }
	void set_zeny(uint32_t zeny) { _zeny = zeny; }
	/* Strength */
	uint16_t get_strength() const { return _strength; }
	void set_strength(uint16_t strength) { _strength = strength; }
	/* Agility */
	uint16_t get_agility() const { return _agility; }
	void set_agility(uint16_t agility) { _agility = agility; }
	/* Vitality */
	uint16_t get_vitality() const { return _vitality; }
	void set_vitality(uint16_t vitality) { _vitality = vitality; }
	/* Intelligence */
	uint16_t get_intelligence() const { return _intelligence; }
	void set_intelligence(uint16_t intelligence) { _intelligence = intelligence; }
	/* Dexterity */
	uint16_t get_dexterity() const { return _dexterity; }
	void set_dexterity(uint16_t dexterity) { _dexterity = dexterity; }
	/* Luck */
	uint16_t get_luck() const { return _luck; }
	void set_luck(uint16_t luck) { _luck = luck; }
	/* Maximum HP */
	uint32_t get_max_hp() const { return _maximum_hp; }
	void set_max_hp(uint32_t maximum_hp) { _maximum_hp = maximum_hp; }
	/* Maximum SP */
	uint32_t get_max_sp() const { return _maximum_sp; }
	void set_max_sp(uint32_t maximum_sp) { _maximum_sp = maximum_sp; }
	/* HP */
	uint32_t get_hp() const { return _hp; }
	void set_hp(uint32_t hp) { _hp = hp; }
	/* SP */
	uint32_t get_sp() const { return _sp; }
	void set_sp(uint32_t sp) { _sp = sp; }
	/* Status Point */
	uint32_t get_status_points() const { return _status_points; }
	void set_status_points(uint32_t status_points) { _status_points = status_points; }
	/* Skill Points */
	uint32_t get_skill_points() const { return _skill_points; }
	void set_skill_points(uint32_t skill_points) { _skill_points = skill_points; }
	/* Body State */
	uint32_t get_body_state() const { return _body_state; }
	void set_body_state(uint32_t body_state) { _body_state = body_state; }
	/* Virtue */
	int16_t get_virtue() const { return _virtue; }
	void set_virtue(int16_t virtue) { _virtue = virtue; }
	/* Honor */
	uint32_t get_honor() const { return _honor; }
	void set_honor(uint32_t honor) { _honor = honor; }
	/* Manner */
	int16_t get_manner() const { return _manner; }
	void set_manner(int16_t manner) { _manner = manner; }
	/* Hair Style ID */
	uint8_t get_hair_style_id() const { return _hair_style_id; }
	void set_hair_style_id(uint8_t hair_style_id) { _hair_style_id = hair_style_id; }
	/* Hair Color ID */
	uint16_t get_hair_color_id() const { return _hair_color_id; }
	void set_hair_color_id(uint16_t hair_color_id) { _hair_color_id = hair_color_id; }
	/* Cloth Color ID */
	uint16_t get_cloth_color_id() const { return _cloth_color_id; }
	void set_cloth_color_id(uint16_t cloth_color_id) { _cloth_color_id = cloth_color_id; }
	/* Body ID */
	uint16_t get_body_id() const { return _body_id; }
	void set_body_id(uint16_t body_id) { _body_id = body_id; }
	/* Weapon ID */
	uint16_t get_weapon_id() const { return _weapon_id; }
	void set_weapon_id(uint16_t weapon_id) { _weapon_id = weapon_id; }
	/* Shield ID */
	uint16_t get_shield_id() const { return _shield_id; }
	void set_shield_id(uint16_t shield_id) { _shield_id = shield_id; }
	/* Head Top View ID */
	uint16_t get_head_top_view_id() const { return _head_top_view_id; }
	void set_head_top_view_id(uint16_t head_top_view_id) { _head_top_view_id = head_top_view_id; }
	/* Head Mid View ID */
	uint16_t get_head_mid_view_id() const { return _head_mid_view_id; }
	void set_head_mid_view_id(uint16_t head_mid_view_id) { _head_mid_view_id = head_mid_view_id; }
	/* Head Bottom View ID */
	uint16_t get_head_bottom_view_id() const { return _head_bottom_view_id; }
	void set_head_bottom_view_id(uint16_t head_bottom_view_id) { _head_bottom_view_id = head_bottom_view_id; }
	/* Robe View ID */
	uint16_t get_robe_view_id() const { return _robe_view_id; }
	void set_robe_view_id(uint16_t robe_view_id) { _robe_view_id = robe_view_id; }
private:
	uint32_t _character_id{0};
	uint16_t _job_id{0};
	uint16_t _base_level{0};
	uint16_t _job_level{0};
	uint64_t _base_experience{0};
	uint64_t _job_experience{0};
	uint32_t _zeny{0};
	uint16_t _strength{0};
	uint16_t _agility{0};
	uint16_t _vitality{0};
	uint16_t _intelligence{0};
	uint16_t _dexterity{0};
	uint16_t _luck{0};
	uint32_t _maximum_hp{0}, _maximum_sp{0};
	uint32_t _hp{0}, _sp{0};
	uint32_t _status_points{0}, _skill_points{0};
	uint32_t _body_state{0};
	int16_t _virtue{0};
	uint32_t _honor{0};
	int16_t _manner{0};
	uint8_t _hair_style_id{0};
	uint16_t _hair_color_id{0};
	uint16_t _cloth_color_id{0};
	uint16_t _body_id{0};
	uint16_t _weapon_id{0};
	uint16_t _shield_id{0};
	uint16_t _head_top_view_id{0};
	uint16_t _head_mid_view_id{0};
	uint16_t _head_bottom_view_id{0};
	uint16_t _robe_view_id{0};
};
}
}
}
#endif // HORIZON_MODELS_CHARACTERS_STATUSDATA_HPP
