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

#ifndef HORIZON_ZONE_GAME_TRAITS_SUBATTRIBUTES_HPP
#define HORIZON_ZONE_GAME_TRAITS_SUBATTRIBUTES_HPP

#include "Attributes.hpp"
#include "Server/Common/Definitions/EntityDefinitions.hpp"
#include "Server/Common/Definitions/ItemDefinitions.hpp"
#include <cstdint>

namespace Horizon
{
namespace Zone
{
class Entity;
namespace Entities
{
namespace Traits
{
	class Strength;
	class Dexterity;
	class Luck;
	class BaseLevel;
	class Vitality;
	class Intelligence;
	class EquipATK;

	class MaxWeight
	: public Attribute<MaxWeight, BasicAttributeNotifier<STATUS_MAX_WEIGHT, std::weak_ptr<MaxWeight>>>
	{
	public:
		MaxWeight(std::weak_ptr<Entity> entity, uint32_t base = 0, uint32_t equip = 0, uint32_t status = 0)
		: Attribute(entity, base, equip, status)
		{ }
		~MaxWeight() { };

		void on_observable_changed(std::weak_ptr<Strength> wstr) { set_base(compute()); }

		uint32_t compute();

		void set_strength(std::weak_ptr<Strength> str) { _str = str; }

	private:
		std::weak_ptr<Strength> _str;
	};

	class CurrentWeight
	: public Attribute<CurrentWeight, BasicAttributeNotifier<STATUS_CURRENT_WEIGHT, std::weak_ptr<CurrentWeight>>>
	{
	public:
		CurrentWeight(std::weak_ptr<Entity> entity, uint32_t base = 0, uint32_t equip = 0, uint32_t status = 0)
		: Attribute(entity, base, equip, status)
		{ }
		~CurrentWeight() { };
	};

	class StatusATK
	: public Attribute<StatusATK, BasicAttributeNotifier<STATUS_STATUS_ATK, std::weak_ptr<StatusATK>>>
	{
	public:
		StatusATK(std::weak_ptr<Entity> entity)
		: Attribute(entity)
		{ }
		~StatusATK() { }

		void on_observable_changed(std::weak_ptr<Strength>) { set_base(compute()); }
		void on_observable_changed(std::weak_ptr<Dexterity>) { set_base(compute()); }
		void on_observable_changed(std::weak_ptr<Luck>) { set_base(compute()); }
		void on_observable_changed(std::weak_ptr<BaseLevel>) { set_base(compute()); }

		uint32_t compute();

		void set_base_level(std::weak_ptr<BaseLevel> blvl) { _blvl = blvl; }
		void set_strength(std::weak_ptr<Strength> str) { _str = str; }
		void set_dexterity(std::weak_ptr<Dexterity> dex) { _dex = dex; }
		void set_luck(std::weak_ptr<Luck> luk) { _luk = luk; }
		void set_weapon_type(item_weapon_type type) { _weapon_type = type; set_base(compute()); }

	private:
		std::weak_ptr<BaseLevel> _blvl;
		std::weak_ptr<Strength> _str;
		std::weak_ptr<Dexterity> _dex;
		std::weak_ptr<Luck> _luk;
		item_weapon_type _weapon_type;
	};

	class WeaponATK
	: public Attribute<WeaponATK, BasicAttributeNotifier<STATUS_EQUIP_ATK, std::weak_ptr<WeaponATK>, std::weak_ptr<EquipATK>>>
	{
	public:
		WeaponATK(std::weak_ptr<Entity> entity)
		: Attribute(entity)
		{ }
		~WeaponATK() { }

		void on_observable_changed(std::weak_ptr<Strength>) { set_base(compute()); }
		void on_observable_changed(std::weak_ptr<Dexterity>) { set_base(compute()); }
		void on_equipment_change() { set_base(compute()); }

		void set_strength(std::weak_ptr<Strength> str) { _str = str; }
		void set_dexterity(std::weak_ptr<Dexterity> dex) { _dex = dex; }

		uint32_t compute();
		uint32_t compute_variance(uint8_t weapon_lvl, uint32_t base_weapon_dmg);

		void notify_update() override { _notifier.notify_sum(); }

		uint32_t get_lhw_overupgrade() { return _lhw_overupgrade; }
		uint32_t get_rhw_overupgrade() { return _rhw_overupgrade; }

	private:
		std::weak_ptr<Strength> _str;
		std::weak_ptr<Dexterity> _dex;
		uint32_t _left_hand_val{0};
		uint32_t _right_hand_val{0};
		uint32_t _lhw_overupgrade{0};
		uint32_t _rhw_overupgrade{0};
	};

	class EquipATK
	: public Attribute<WeaponATK, BasicAttributeNotifier<STATUS_EQUIP_ATK, std::weak_ptr<WeaponATK>, std::weak_ptr<EquipATK>>>
	{
	public:
		EquipATK(std::weak_ptr<Entity> entity)
		: Attribute(entity)
		{ }
		~EquipATK() { }

		void on_equipments_changed() { set_base(compute()); }

		uint32_t compute() { return 0; }

		void notify_update() override { _notifier.notify_sum(); }
	};

	class StatusMATK
	: public Attribute<StatusMATK, BasicAttributeNotifier<STATUS_STATUS_MATK, std::weak_ptr<StatusMATK>>>
	{
	public:
		StatusMATK(std::weak_ptr<Entity> entity)
		: Attribute(entity)
		{ }
		~StatusMATK() { }

		void on_observable_changed(std::weak_ptr<Intelligence>) { set_base(compute()); }
		void on_observable_changed(std::weak_ptr<Dexterity>) { set_base(compute()); }
		void on_observable_changed(std::weak_ptr<Luck>) { set_base(compute()); }
		void on_observable_changed(std::weak_ptr<BaseLevel>) { set_base(compute()); }

		uint32_t compute();

		void set_base_level(std::weak_ptr<BaseLevel> blvl) { _blvl = blvl; }
		void set_intelligence(std::weak_ptr<Intelligence> int_) { _int = int_; }
		void set_dexterity(std::weak_ptr<Dexterity> dex) { _dex = dex; }
		void set_luck(std::weak_ptr<Luck> luk) { _luk = luk; }

	private:
		std::weak_ptr<BaseLevel> _blvl;
		std::weak_ptr<Intelligence> _int;
		std::weak_ptr<Dexterity> _dex;
		std::weak_ptr<Luck> _luk;
	};

	class SoftDEF
	: public Attribute<SoftDEF, BasicAttributeNotifier<STATUS_SOFT_DEF, std::weak_ptr<SoftDEF>>>
	{
	public:
		SoftDEF(std::weak_ptr<Entity> entity)
		: Attribute(entity)
		{ }
		~SoftDEF() { }

		void on_observable_changed(std::weak_ptr<Vitality>) { set_base(compute()); }

		uint32_t compute();

		void set_vitality(std::weak_ptr<Vitality> vit) { _vit = vit; }

	private:
		std::weak_ptr<Vitality> _vit;
	};

	class SoftMDEF
	: public Attribute<SoftMDEF, BasicAttributeNotifier<STATUS_SOFT_MDEF, std::weak_ptr<SoftMDEF>>>
	{
	public:
		SoftMDEF(std::weak_ptr<Entity> entity)
		: Attribute(entity)
		{ }
		~SoftMDEF() { }

		void on_observable_changed(std::weak_ptr<Intelligence>) { set_base(compute()); }
		void on_observable_changed(std::weak_ptr<Dexterity>) { set_base(compute()); }
		void on_observable_changed(std::weak_ptr<Vitality>) { set_base(compute()); }
		void on_observable_changed(std::weak_ptr<BaseLevel>) { set_base(compute()); }

		uint32_t compute();

		void set_base_level(std::weak_ptr<BaseLevel> blvl) { _blvl = blvl; }
		void set_intelligence(std::weak_ptr<Intelligence> int_) { _int = int_; }
		void set_dexterity(std::weak_ptr<Dexterity> dex) { _dex = dex; }
		void set_vitality(std::weak_ptr<Vitality> vit) { _vit = vit; }

	private:
		std::weak_ptr<BaseLevel> _blvl;
		std::weak_ptr<Intelligence> _int;
		std::weak_ptr<Dexterity> _dex;
		std::weak_ptr<Vitality> _vit;
	};

	class HIT
	: public Attribute<HIT, BasicAttributeNotifier<STATUS_HIT, std::weak_ptr<HIT>>>
	{
	public:
		HIT(std::weak_ptr<Entity> entity)
		: Attribute(entity)
		{ }
		~HIT() { }

		void on_observable_changed(std::weak_ptr<Dexterity>) { set_base(compute()); }
		void on_observable_changed(std::weak_ptr<Luck>) { set_base(compute()); }
		void on_observable_changed(std::weak_ptr<BaseLevel>) { set_base(compute()); }

		uint32_t compute();

		void set_base_level(std::weak_ptr<BaseLevel> blvl) { _blvl = blvl; }
		void set_dexterity(std::weak_ptr<Dexterity> dex) { _dex = dex; }
		void set_luck(std::weak_ptr<Luck> luk) { _luk = luk; }

	private:
		std::weak_ptr<BaseLevel> _blvl;
		std::weak_ptr<Dexterity> _dex;
		std::weak_ptr<Luck> _luk;
	};

	class CRIT
	: public Attribute<CRIT, BasicAttributeNotifier<STATUS_CRITICAL, std::weak_ptr<CRIT>>>
	{
	public:
		CRIT(std::weak_ptr<Entity> entity)
		: Attribute(entity)
		{ }
		~CRIT() { }

		void on_observable_changed(std::weak_ptr<Luck>) { set_base(compute()); }

		uint32_t compute();

		void set_luck(std::weak_ptr<Luck> luk) { _luk = luk; }

	private:
		std::weak_ptr<Luck> _luk;
	};

	class FLEE
	: public Attribute<FLEE, BasicAttributeNotifier<STATUS_FLEE, std::weak_ptr<FLEE>>>
	{
	public:
		FLEE(std::weak_ptr<Entity> entity)
		: Attribute(entity)
		{ }
		~FLEE() { }

		void on_observable_changed(std::weak_ptr<Agility>) { set_base(compute()); }
		void on_observable_changed(std::weak_ptr<BaseLevel>) { set_base(compute()); }
		void on_observable_changed(std::weak_ptr<Luck>) { set_base(compute()); }

		uint32_t compute();

		void set_agility(std::weak_ptr<Agility> agi) { _agi = agi; }
		void set_base_level(std::weak_ptr<BaseLevel> blvl) { _blvl = blvl; }
		void set_luck(std::weak_ptr<Luck> luk) { _luk = luk; }

	private:
		std::weak_ptr<Agility> _agi;
		std::weak_ptr<BaseLevel> _blvl;
		std::weak_ptr<Luck> _luk;
	};
}
}
}
}

#endif /* HORIZON_ZONE_GAME_STATUS_SUBATTRIBUTES_HPP */
