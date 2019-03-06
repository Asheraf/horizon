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

#ifndef HORIZON_ZONE_GAME_STATUS_STATUSATK_HPP
#define HORIZON_ZONE_GAME_STATUS_STATUSATK_HPP

#include "Attributes.hpp"
#include "Server/Common/Definitions/EntityDefinitions.hpp"

#include <cstdint>

namespace Horizon
{
namespace Zone
{
namespace Game
{
class Entity;
namespace Status
{
	class Strength;
	class Dexterity;
	class Luck;
	class BaseLevel;
	class Vitality;
	class Intelligence;
	
	class StatusATK : public Attribute<StatusATK, BasicAttributeNotifier>
	{
	public:
		StatusATK(std::weak_ptr<Entity> entity)
		: Attribute(entity, STATUS_STATUS_ATK, 0, 0, 0)
		{ }
		~StatusATK() { }

		void on_observable_changed(std::weak_ptr<Strength>) { set_base(compute(), true); }
		void on_observable_changed(std::weak_ptr<Dexterity>) { set_base(compute(), true); }
		void on_observable_changed(std::weak_ptr<Luck>) { set_base(compute(), true); }
		void on_observable_changed(std::weak_ptr<BaseLevel>) { set_base(compute(), true); }
		
		uint32_t compute();

		void set_base_level(std::weak_ptr<BaseLevel> blvl) { _blvl = blvl; }
		void set_strength(std::weak_ptr<Strength> str) { _str = str; }
		void set_dexterity(std::weak_ptr<Dexterity> dex) { _dex = dex; }
		void set_luck(std::weak_ptr<Luck> luk) { _luk = luk; }
		
	private:
		std::weak_ptr<BaseLevel> _blvl;
		std::weak_ptr<Strength> _str;
		std::weak_ptr<Dexterity> _dex;
		std::weak_ptr<Luck> _luk;
	};

	class StatusMATK : public Attribute<StatusMATK, BasicAttributeNotifier>
	{
	public:
		StatusMATK(std::weak_ptr<Entity> entity)
		: Attribute(entity, STATUS_STATUS_MATK, 0, 0, 0)
		{ }
		~StatusMATK() { }

		void on_observable_changed(std::weak_ptr<Intelligence>) { set_base(compute(), true); }
		void on_observable_changed(std::weak_ptr<Dexterity>) { set_base(compute(), true); }
		void on_observable_changed(std::weak_ptr<Luck>) { set_base(compute(), true); }
		void on_observable_changed(std::weak_ptr<BaseLevel>) { set_base(compute(), true); }

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

	class SoftDEF : public Attribute<SoftDEF, BasicAttributeNotifier>
	{
	public:
		SoftDEF(std::weak_ptr<Entity> entity)
		: Attribute(entity, STATUS_SOFT_DEF, 0, 0, 0)
		{ }
		~SoftDEF() { }

		void on_observable_changed(std::weak_ptr<Vitality>) { set_base(compute(), true); }

		uint32_t compute();

		void set_vitality(std::weak_ptr<Vitality> vit) { _vit = vit; }

	private:
		std::weak_ptr<Vitality> _vit;
	};

	class SoftMDEF : public Attribute<SoftMDEF, BasicAttributeNotifier>
	{
	public:
		SoftMDEF(std::weak_ptr<Entity> entity)
		: Attribute(entity, STATUS_SOFT_MDEF, 0, 0, 0)
		{ }
		~SoftMDEF() { }

		void on_observable_changed(std::weak_ptr<Intelligence>) { set_base(compute(), true); }
		void on_observable_changed(std::weak_ptr<Dexterity>) { set_base(compute(), true); }
		void on_observable_changed(std::weak_ptr<Vitality>) { set_base(compute(), true); }
		void on_observable_changed(std::weak_ptr<BaseLevel>) { set_base(compute(), true); }

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

	class HIT : public Attribute<HIT, BasicAttributeNotifier>
	{
	public:
		HIT(std::weak_ptr<Entity> entity)
		: Attribute(entity, STATUS_HIT, 0, 0, 0)
		{ }
		~HIT() { }

		void on_observable_changed(std::weak_ptr<Dexterity>) { set_base(compute(), true); }
		void on_observable_changed(std::weak_ptr<Luck>) { set_base(compute(), true); }
		void on_observable_changed(std::weak_ptr<BaseLevel>) { set_base(compute(), true); }

		uint32_t compute();

		void set_base_level(std::weak_ptr<BaseLevel> blvl) { _blvl = blvl; }
		void set_dexterity(std::weak_ptr<Dexterity> dex) { _dex = dex; }
		void set_luck(std::weak_ptr<Luck> luk) { _luk = luk; }

	private:
		std::weak_ptr<BaseLevel> _blvl;
		std::weak_ptr<Dexterity> _dex;
		std::weak_ptr<Luck> _luk;
	};

	class CRIT : public Attribute<CRIT, BasicAttributeNotifier>
	{
	public:
		CRIT(std::weak_ptr<Entity> entity)
		: Attribute(entity, STATUS_CRITICAL, 0, 0, 0)
		{ }
		~CRIT() { }

		void on_observable_changed(std::weak_ptr<Luck>) { set_base(compute(), true); }

		uint32_t compute();

		void set_luck(std::weak_ptr<Luck> luk) { _luk = luk; }

	private:
		std::weak_ptr<Luck> _luk;
	};

	class FLEE : public Attribute<FLEE, BasicAttributeNotifier>
	{
	public:
		FLEE(std::weak_ptr<Entity> entity)
		: Attribute(entity, STATUS_FLEE, 0, 0, 0)
		{ }
		~FLEE() { }

		void on_observable_changed(std::weak_ptr<Agility>) { set_base(compute(), true); }
		void on_observable_changed(std::weak_ptr<BaseLevel>) { set_base(compute(), true); }
		void on_observable_changed(std::weak_ptr<Luck>) { set_base(compute(), true); }

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

#endif /* HORIZON_ZONE_GAME_STATUS_STATUSATK_HPP */
