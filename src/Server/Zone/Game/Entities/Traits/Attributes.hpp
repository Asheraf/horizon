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

#ifndef HORIZON_ZONE_GAME_TRAITS_ATTRIBUTES_HPP
#define HORIZON_ZONE_GAME_TRAITS_ATTRIBUTES_HPP

#include "Server/Common/Definitions/EntityDefinitions.hpp"
#include "Server/Zone/Game/Entities/Traits/ObservableStatus.hpp"

#include <cstdint>
#include <type_traits>
#include <memory>
#include <algorithm>
#include <vector>
#include <tuple>

namespace Horizon
{
namespace Zone
{
class Entity;
namespace Entities
{
class Player;
namespace Traits
{
	class StatusATK;
	class EquipATK;
	class StatusMATK;
	class SoftDEF;
	class SoftMDEF;
	class HIT;
	class CRIT;
	class FLEE;
	class StrengthPointCost;
	class AgilityPointCost;
	class VitalityPointCost;
	class IntelligencePointCost;
	class DexterityPointCost;
	class LuckPointCost;
	class BaseExperience;
	class JobExperience;
	class StatusPoint;
	class SkillPoint;
	class NextBaseExperience;
	class NextJobExperience;
	class MaxWeight;

	template <class T>
	class Attribute;
	
	template <class T>
	class Attribute
	{
	public:
		Attribute(std::weak_ptr<Entity> entity, uint32_t base = 0, uint32_t equip = 0, uint32_t status = 0)
		: _base_val(base), _equip_val(equip), _status_val(status), _entity(entity)
		{
		}
		virtual ~Attribute() { }

		std::shared_ptr<Entity> get_entity() { return _entity.lock(); }
		void set_entity(std::shared_ptr<Entity> e) { _entity = e; }

		virtual void set_base(uint32_t val)
		{
			_base_val = val;
		}

		virtual void add_base(uint32_t val) { set_base(_base_val + val); }
		virtual void sub_base(uint32_t val) { set_base(_base_val - std::min(_base_val, val)); }
		virtual uint32_t get_base() const { return _base_val; }

		virtual void set_equip(uint32_t val)
		{
			_equip_val = val;
		}
		virtual void add_equip(uint32_t val) { set_equip(_equip_val + val); }
		virtual void sub_equip(uint32_t val) { set_equip(_equip_val - std::min(_base_val, val)); }
		virtual uint32_t get_equip() const { return _equip_val; }

		virtual void set_status(uint32_t str)
		{
			_status_val = str;
		}
		virtual void add_status(uint32_t val) { set_status(_status_val + val); }
		virtual void sub_status(uint32_t val) { set_status(_status_val - std::min(_base_val, val)); }
		virtual uint32_t get_status() const { return _status_val; }

		virtual uint32_t total() const { return _base_val + _equip_val + _status_val; }

		template <class TT>
		float operator + (Attribute<TT> const &right) const { return total() + right.total() ; }
		template <typename TT, typename std::enable_if<std::is_integral<TT>::value>::type* = nullptr>
		TT operator + (TT right) { return total() + right; }

		template <class TT>
		float operator / (Attribute<TT> const &right) { return right.total() / total(); }
		template <typename TT, typename std::enable_if<std::is_integral<TT>::value>::type* = nullptr>
		TT operator / (TT right) { return total() / right; }

		template <class TT>
		float operator * (Attribute<TT> const &right) { return right.total() * total(); }
		template <typename TT, typename std::enable_if<std::is_integral<TT>::value>::type* = nullptr>
		TT operator * (TT right) { return total() * right; }

		template <class TT>
		float operator - (Attribute<TT> const &right) { return right.total() - total(); }
		template <typename TT, typename std::enable_if<std::is_integral<TT>::value>::type* = nullptr>
		TT operator - (TT right) { return total() - right; }

		template <typename TT, typename std::enable_if<std::is_integral<TT>::value>::type* = nullptr>
		bool operator == (TT right) { return total() == right; }
		template <typename TT, typename std::enable_if<std::is_integral<TT>::value>::type* = nullptr>
		bool operator != (TT right) { return total() != right; }
		template <typename TT, typename std::enable_if<std::is_integral<TT>::value>::type* = nullptr>
		bool operator > (TT right) { return total() > right; }
		template <typename TT, typename std::enable_if<std::is_integral<TT>::value>::type* = nullptr>
		bool operator >= (TT right) { return total() >= right; }
		template <typename TT, typename std::enable_if<std::is_integral<TT>::value>::type* = nullptr>
		bool operator < (TT right) { return total() < right; }
		template <typename TT, typename std::enable_if<std::is_integral<TT>::value>::type* = nullptr>
		bool operator <= (TT right) { return total() <= right; }

		Attribute<T> operator = (Attribute<T> const &right)
		{
			set_entity(right.get_entity());
			set_base(right.get_base(), false);
			set_equip(right.get_equip(), false);
			set_status(right.get_status(), false);

			return *this;
		}

	protected:
		uint32_t _base_val{0};
		uint32_t _equip_val{0};
		uint32_t _status_val{0};
	private:
		std::weak_ptr<Entity> _entity;
	};

	class BaseLevel
	: public Attribute<BaseLevel>,
	  public ObservableStatus<std::weak_ptr<BaseLevel>, std::weak_ptr<StatusPoint>, std::weak_ptr<NextBaseExperience>, std::weak_ptr<StatusATK>, std::weak_ptr<StatusMATK>, std::weak_ptr<SoftMDEF>, std::weak_ptr<HIT>, std::weak_ptr<FLEE>>
	{
	public:
		BaseLevel(std::weak_ptr<Entity> entity,  uint32_t base = 0)
		: Attribute(entity, base, 0, 0),
		  ObservableStatus(std::weak_ptr<StatusPoint>(), std::weak_ptr<NextBaseExperience>(), std::weak_ptr<StatusATK>(), std::weak_ptr<StatusMATK>(), std::weak_ptr<SoftMDEF>(), std::weak_ptr<HIT>(), std::weak_ptr<FLEE>())
		{ }
		~BaseLevel() { };

		void set_base(uint32_t val) override
		{
			Attribute::set_base(val);
			this->notify_observers();
		}

		void on_observable_changed(std::weak_ptr<BaseExperience> wbexp);
	};

	class JobLevel
	: public Attribute<JobLevel>,
	  public ObservableStatus<std::weak_ptr<JobLevel>, std::weak_ptr<SkillPoint>, std::weak_ptr<NextJobExperience>>
	{
	public:
		JobLevel(std::weak_ptr<Entity> entity, uint32_t base = 0)
		: Attribute(entity, base, 0, 0),
		  ObservableStatus(std::weak_ptr<SkillPoint>(), std::weak_ptr<NextJobExperience>())
		{ }
		~JobLevel() { };

		void set_base(uint32_t val) override
		{
			Attribute::set_base(val);
			this->notify_observers();
		}

		void on_observable_changed(std::weak_ptr<JobExperience> wjexp);
	};

	class MaxHP
	: public Attribute<MaxHP>
	{
	public:
		MaxHP(std::weak_ptr<Entity> entity, uint32_t base = 0, uint32_t equip = 0, uint32_t status = 0)
		: Attribute(entity, base, equip, status)
		{ }
		~MaxHP() { };
	};

	class MaxSP
	: public Attribute<MaxSP>
	{
	public:
		MaxSP(std::weak_ptr<Entity> entity, uint32_t base = 0, uint32_t equip = 0, uint32_t status = 0)
		: Attribute(entity, base, equip, status)
		{ }
		~MaxSP() { };
	};

	class CurrentHP
	: public Attribute<CurrentHP>
	{
	public:
		CurrentHP(std::weak_ptr<Entity> entity, uint32_t base = 0, uint32_t equip = 0, uint32_t status = 0)
		: Attribute(entity, base, equip, status)
		{ }
		~CurrentHP() { };
	};

	class CurrentSP
	: public Attribute<CurrentSP>
	{
	public:
		CurrentSP(std::weak_ptr<Entity> entity, uint32_t base = 0, uint32_t equip = 0, uint32_t status = 0)
		: Attribute(entity, base, equip, status)
		{ }
		~CurrentSP() { };
	};

	class MovementSpeed
	: public Attribute<MovementSpeed>
	{
	public:
		MovementSpeed(std::weak_ptr<Entity> entity, uint32_t base = 0, uint32_t equip = 0, uint32_t status = 0)
		: Attribute(entity, base, equip, status)
		{ }
		~MovementSpeed() { }

		uint32_t get_with_cost(int cost) { return total() * cost / 10; };
	};

	class StatusPoint
	: public Attribute<StatusPoint>
	{
	public:
		StatusPoint(std::weak_ptr<Entity> entity, uint32_t base = 0)
		: Attribute(entity, base, 0, 0)
		{ }
		~StatusPoint() { };

		void on_observable_changed(std::weak_ptr<BaseLevel> wblvl);
	};

	class SkillPoint
	: public Attribute<SkillPoint>
	{
	public:
		SkillPoint(std::weak_ptr<Entity> entity, uint32_t base = 0)
		: Attribute(entity, base, 0, 0)
		{ }
		~SkillPoint() { };

		void on_observable_changed(std::weak_ptr<JobLevel> wjlvl);
	};

	class Strength
	: public Attribute<Strength>,
	  public ObservableStatus<std::weak_ptr<Strength>, std::weak_ptr<StrengthPointCost>, std::weak_ptr<MaxWeight>, std::weak_ptr<StatusATK>, std::weak_ptr<EquipATK>>
	{
	public:
		Strength(std::weak_ptr<Entity> entity, uint32_t base = 0, uint32_t equip = 0, uint32_t status = 0)
		: Attribute(entity, base, equip, status),
		  ObservableStatus(std::weak_ptr<StrengthPointCost>(), std::weak_ptr<MaxWeight>(), std::weak_ptr<StatusATK>(), std::weak_ptr<EquipATK>())
		{ }
		~Strength() { };

		void set_base(uint32_t val) override
		{
			Attribute::set_base(val);
			this->notify_observers();
		}
	};

	class Agility
	: public Attribute<Agility>,
	  public ObservableStatus<std::weak_ptr<Agility>, std::weak_ptr<AgilityPointCost>, std::weak_ptr<FLEE>>
	{
	public:
		Agility(std::weak_ptr<Entity> entity, uint32_t base = 0, uint32_t equip = 0, uint32_t status = 0)
		: Attribute(entity, base, equip, status),
		  ObservableStatus(std::weak_ptr<AgilityPointCost>(), std::weak_ptr<FLEE>())
		{ }
		~Agility() { };

		void set_base(uint32_t val) override
		{
			Attribute::set_base(val);
			this->notify_observers();
		}
	};

	class Vitality
	: public Attribute<Vitality>,
	  public ObservableStatus<std::weak_ptr<Vitality>, std::weak_ptr<VitalityPointCost>, std::weak_ptr<SoftDEF>, std::weak_ptr<SoftMDEF>>
	{
	public:
		Vitality(std::weak_ptr<Entity> entity, uint32_t base = 0, uint32_t equip = 0, uint32_t status = 0)
		: Attribute(entity, base, equip, status),
		  ObservableStatus(std::weak_ptr<VitalityPointCost>(), std::weak_ptr<SoftDEF>(), std::weak_ptr<SoftMDEF>())
		{ }
		~Vitality() { };

		void set_base(uint32_t val) override
		{
			Attribute::set_base(val);
			this->notify_observers();
		}
	};

	class Intelligence
	: public Attribute<Intelligence>,
	  public ObservableStatus<std::weak_ptr<Intelligence>, std::weak_ptr<IntelligencePointCost>, std::weak_ptr<StatusMATK>, std::weak_ptr<SoftMDEF>>
	{
	public:
		Intelligence(std::weak_ptr<Entity> entity, uint32_t base = 0, uint32_t equip = 0, uint32_t status = 0)
		: Attribute(entity, base, equip, status),
		  ObservableStatus(std::weak_ptr<IntelligencePointCost>(), std::weak_ptr<StatusMATK>(), std::weak_ptr<SoftMDEF>())
		{ }
		~Intelligence() { };

		void set_base(uint32_t val) override
		{
			Attribute::set_base(val);
			this->notify_observers();
		}
	};

	class Dexterity
	: public Attribute<Dexterity>,
	  public ObservableStatus<std::weak_ptr<Dexterity>, std::weak_ptr<DexterityPointCost>, std::weak_ptr<StatusATK>, std::weak_ptr<EquipATK>, std::weak_ptr<StatusMATK>, std::weak_ptr<SoftMDEF>, std::weak_ptr<HIT>>
	{
	public:
		Dexterity(std::weak_ptr<Entity> entity, uint32_t base = 0, uint32_t equip = 0, uint32_t status = 0)
		: Attribute(entity, base, equip, status),
		  ObservableStatus(std::weak_ptr<DexterityPointCost>(), std::weak_ptr<StatusATK>(), std::weak_ptr<EquipATK>(), std::weak_ptr<StatusMATK>(), std::weak_ptr<SoftMDEF>(), std::weak_ptr<HIT>())
		{ }
		~Dexterity() { };

		void set_base(uint32_t val) override
		{
			Attribute::set_base(val);
			this->notify_observers();
		}
	};

	class Luck
	: public Attribute<Luck>,
	  public ObservableStatus<std::weak_ptr<Luck>, std::weak_ptr<LuckPointCost>, std::weak_ptr<StatusATK>, std::weak_ptr<StatusMATK>, std::weak_ptr<HIT>, std::weak_ptr<CRIT>, std::weak_ptr<FLEE>>
	{
	public:
		Luck(std::weak_ptr<Entity> entity, uint32_t base = 0, uint32_t equip = 0, uint32_t status = 0)
		: Attribute(entity, base, equip, status),
		  ObservableStatus(std::weak_ptr<LuckPointCost>(), std::weak_ptr<StatusATK>(), std::weak_ptr<StatusMATK>(), std::weak_ptr<HIT>(), std::weak_ptr<CRIT>(), std::weak_ptr<FLEE>())
		{ }
		~Luck() { };

		void set_base(uint32_t val) override
		{
			Attribute::set_base(val);
			this->notify_observers();
		}
	};

	class StrengthPointCost
	: public Attribute<StrengthPointCost>
	{
	public:
		StrengthPointCost(std::weak_ptr<Entity> entity, uint32_t base = 0)
		: Attribute(entity, base, 0, 0)
		{ }
		~StrengthPointCost() { };

		void on_observable_changed(std::weak_ptr<Strength>);
	};

	class AgilityPointCost
	: public Attribute<AgilityPointCost>
	{
	public:
		AgilityPointCost(std::weak_ptr<Entity> entity, uint32_t base = 0)
		: Attribute(entity, base, 0, 0)
		{ }
		~AgilityPointCost() { };

		void on_observable_changed(std::weak_ptr<Agility>);
	};

	class VitalityPointCost
	: public Attribute<VitalityPointCost>
	{
	public:
		VitalityPointCost(std::weak_ptr<Entity> entity, uint32_t base = 0)
		: Attribute(entity, base, 0, 0)
		{ }
		~VitalityPointCost() { };

		void on_observable_changed(std::weak_ptr<Vitality>);
	};

	class IntelligencePointCost
	: public Attribute<IntelligencePointCost>
	{
	public:
		IntelligencePointCost(std::weak_ptr<Entity> entity, uint32_t base = 0)
		: Attribute(entity, base, 0, 0)
		{ }
		~IntelligencePointCost() { };

		void on_observable_changed(std::weak_ptr<Intelligence>);
	};

	class DexterityPointCost
	: public Attribute<DexterityPointCost>
	{
	public:
		DexterityPointCost(std::weak_ptr<Entity> entity, uint32_t base = 0)
		: Attribute(entity, base, 0, 0)
		{ }
		~DexterityPointCost() { };

		void on_observable_changed(std::weak_ptr<Dexterity>);
	};

	class LuckPointCost
	: public Attribute<LuckPointCost>
	{
	public:
		LuckPointCost(std::weak_ptr<Entity> entity, uint32_t base = 0)
		: Attribute(entity, base, 0, 0)
		{ }
		~LuckPointCost() { };

		void on_observable_changed(std::weak_ptr<Luck>);
	};

	class BaseExperience
	: public Attribute<BaseExperience>,
	  public ObservableStatus<std::weak_ptr<BaseExperience>, std::weak_ptr<BaseLevel>>
	{
	public:
		BaseExperience(std::weak_ptr<Entity> entity,  uint32_t base = 0)
		: Attribute(entity, base, 0, 0),
		  ObservableStatus(std::weak_ptr<BaseLevel>())
		{ }
		~BaseExperience() { };

		void set_base(uint32_t val) override
		{
			Attribute::set_base(val);
			this->notify_observers();
		}
	};

	class JobExperience
	: public Attribute<JobExperience>,
	  public ObservableStatus<std::weak_ptr<JobExperience>, std::weak_ptr<JobLevel>>
	{
	public:
		JobExperience(std::weak_ptr<Entity> entity,  uint32_t base = 0)
		: Attribute(entity, base, 0, 0),
		ObservableStatus(std::weak_ptr<JobLevel>())
		{ }
		~JobExperience() { };

		void set_base(uint32_t val) override
		{
			Attribute::set_base(val);
			this->notify_observers();
		}
	};

	class NextBaseExperience
	: public Attribute<NextBaseExperience>
	{
	public:
		NextBaseExperience(std::weak_ptr<Entity> entity,  uint32_t base = 0)
		: Attribute(entity, base, 0, 0)
		{ }
		~NextBaseExperience() { };

		void on_observable_changed(std::weak_ptr<BaseLevel> blvl);
	};

	class NextJobExperience
	: public Attribute<NextJobExperience>
	{
	public:
		NextJobExperience(std::weak_ptr<Entity> entity,  uint32_t base = 0)
		: Attribute(entity, base, 0, 0)
		{ }
		~NextJobExperience() { };

		void on_observable_changed(std::weak_ptr<JobLevel> jlvl);
	};
}
}
}
}

#include "AttributesImpl.hpp"

#endif /* HORIZON_ZONE_GAME_STATUS_ATTRIBUTES_HPP */
