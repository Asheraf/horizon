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

#ifndef HORIZON_ZONE_GAME_STATUS_ATTRIBUTES_HPP
#define HORIZON_ZONE_GAME_STATUS_ATTRIBUTES_HPP

#include "Server/Common/Definitions/EntityDefinitions.hpp"
#include "Server/Zone/Game/Entities/Entity.hpp"
#include "Server/Zone/Game/Status/ObservableStatus.hpp"

#include <cstdint>
#include <type_traits>
#include <memory>
#include <algorithm>
#include <vector>

namespace Horizon
{
namespace Zone
{
namespace Game
{
	namespace Entities
	{
		class Player;
	}
namespace Status
{
	class StatusATK;
	class StatusMATK;
	class SoftDEF;
	class SoftMDEF;
	class HIT;
	class CRIT;
	class FLEE;
	
	template <class T, class NOTIFIER_TYPE>
	class Attribute;

	class BasicAttributeNotifier // PAR_CHANGE
	{
	public:
		BasicAttributeNotifier() { }
		~BasicAttributeNotifier() { }

		template <class T, class NOTIFIER_TYPE>
		void notify(std::weak_ptr<Entity> entity, Attribute<T, NOTIFIER_TYPE> const &attr);
	};

	class ExpAttributeNotifier // LONG_PAR_CHANGE
	{
	public:
		ExpAttributeNotifier() { }
		~ExpAttributeNotifier() { }

		template <class T, class NOTIFIER_TYPE>
		void notify(std::weak_ptr<Entity> entity, Attribute<T, NOTIFIER_TYPE> const &attr);
	};

	class StatusPointRequirementNotifier // STATUS_CHANGE
	{
	public:
		StatusPointRequirementNotifier() { }
		~StatusPointRequirementNotifier() { }

		template <class T, class NOTIFIER_TYPE>
		void notify(std::weak_ptr<Entity> entity, Attribute<T, NOTIFIER_TYPE> const &attr);
	};

	class StatusPointNotifier // STATUS_CHANGE
	{
	public:
		StatusPointNotifier() { }
		~StatusPointNotifier() { }

		template <class T, class NOTIFIER_TYPE>
		void notify(std::weak_ptr<Entity> entity, Attribute<T, NOTIFIER_TYPE> const &attr);
	};

	class AttackRangeNotifier // ATTACK_RANGE
	{
	public:
		AttackRangeNotifier() { }
		~AttackRangeNotifier() { }

		template <class T, class NOTIFIER_TYPE>
		void notify(std::weak_ptr<Entity> entity, Attribute<T, NOTIFIER_TYPE> const &attr);
	};

	template <class T, class NOTIFIER_TYPE>
	class Attribute
	{
	public:
		Attribute(std::weak_ptr<Entity> entity, status_point_type type, uint32_t base = 0, uint32_t equip = 0, uint32_t status = 0)
		: _base_val(base), _equip_val(equip), _status_val(status), _entity(entity), _type(type)
		{
		}
		virtual ~Attribute() { }

		std::shared_ptr<Entity> get_entity() { return _entity.lock(); }
		void set_entity(std::shared_ptr<Entity> e) { _entity = e; }

		status_point_type get_type() const { return _type; }
		void set_type(status_point_type type) { _type = type; }

		virtual void set_base(uint32_t val, bool notify = false)
		{
			_base_val = val;

			if (notify)
				notify_update();
		}
		
		virtual void add_base(uint32_t val, bool notify = false) { set_base(_base_val + val, notify); }
		virtual void sub_base(uint32_t val, bool notify = false) { set_base(_base_val - std::min(_base_val, val), notify); }
		virtual uint32_t get_base() const { return _base_val; }

		virtual void set_equip(uint32_t val, bool notify = false)
		{
			_equip_val = val;

			if (notify)
				notify_update();
		}
		virtual void add_equip(uint32_t val, bool notify = false) { set_equip(_equip_val + val, notify); }
		virtual void sub_equip(uint32_t val, bool notify = false) { set_equip(_equip_val - std::min(_base_val, val), notify); }
		virtual uint32_t get_equip() const { return _equip_val; }

		virtual void set_status(uint32_t str, bool notify = false)
		{
			_status_val = str;

			if (notify)
				notify_update();
		}
		virtual void add_status(uint32_t val, bool notify = false) { set_status(_status_val + val, notify); }
		virtual void sub_status(uint32_t val, bool notify = false) { set_status(_status_val - std::min(_base_val, val), notify); }
		virtual uint32_t get_status() const { return _status_val; }

		virtual uint32_t total() const { return _base_val + _equip_val + _status_val; }

		virtual void notify_update()
		{
			_notifier.notify(_entity, *this);
		}
		
		template <class TT, class NTYPE>
		float operator + (Attribute<TT, NTYPE> const &right) const { return total() + right.total() ; }
		template <typename TT, typename std::enable_if<std::is_integral<TT>::value>::type* = nullptr>
		TT operator + (TT right) { return total() + right; }

		template <class TT, class NTYPE>
		float operator / (Attribute<TT, NTYPE> const &right) { return right.total() / total(); }
		template <typename TT, typename std::enable_if<std::is_integral<TT>::value>::type* = nullptr>
		TT operator / (TT right) { return total() / right; }

		template <class TT, class NTYPE>
		float operator * (Attribute<TT, NTYPE> const &right) { return right.total() * total(); }
		template <typename TT, typename std::enable_if<std::is_integral<TT>::value>::type* = nullptr>
		TT operator * (TT right) { return total() * right; }

		template <class TT, class NTYPE>
		float operator - (Attribute<TT, NTYPE> const &right) { return right.total() - total(); }
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

		Attribute<T, NOTIFIER_TYPE> operator = (Attribute<T, NOTIFIER_TYPE> const &right)
		{
			set_entity(right.get_entity());
			set_type(right.get_type());
			set_base(right.get_base());
			set_equip(right.get_equip());
			set_status(right.get_status());

			return *this;
		}

	protected:
		uint32_t _base_val{0};
		uint32_t _equip_val{0};
		uint32_t _status_val{0};
	private:
		std::weak_ptr<Entity> _entity;
		NOTIFIER_TYPE _notifier;
		status_point_type _type;
	};

	class BaseLevel
	: public Attribute<BaseLevel, BasicAttributeNotifier>,
	  public ObservableStatus<std::weak_ptr<BaseLevel>, std::weak_ptr<StatusATK>, std::weak_ptr<StatusMATK>, std::weak_ptr<SoftMDEF>, std::weak_ptr<HIT>, std::weak_ptr<FLEE>>
	{
	public:
		BaseLevel(std::weak_ptr<Entity> entity,  uint32_t base = 0)
		: Attribute(entity, STATUS_BASELEVEL, base, 0, 0),
		  ObservableStatus(std::weak_ptr<StatusATK>(), std::weak_ptr<StatusMATK>(), std::weak_ptr<SoftMDEF>(), std::weak_ptr<HIT>(), std::weak_ptr<FLEE>())
		{ }
		~BaseLevel() { };
	};

	class JobLevel : public Attribute<JobLevel, BasicAttributeNotifier>
	{
	public:
		JobLevel(std::weak_ptr<Entity> entity, uint32_t base = 0)
		: Attribute(entity, STATUS_JOBLEVEL, base, 0, 0)
		{ }
		~JobLevel() { };
	};

	class MaxHP : public Attribute<MaxHP, BasicAttributeNotifier>
	{
	public:
		MaxHP(std::weak_ptr<Entity> entity, uint32_t base = 0, uint32_t equip = 0, uint32_t status = 0)
		: Attribute(entity, STATUS_MAXHP, base, equip, status)
		{ }
		~MaxHP() { };
	};

	class MaxSP : public Attribute<MaxSP, BasicAttributeNotifier>
	{
	public:
		MaxSP(std::weak_ptr<Entity> entity, uint32_t base = 0, uint32_t equip = 0, uint32_t status = 0)
		: Attribute(entity, STATUS_MAXSP, base, equip, status)
		{ }
		~MaxSP() { };
	};

	class CurrentHP : public Attribute<CurrentHP, BasicAttributeNotifier>
	{
	public:
		CurrentHP(std::weak_ptr<Entity> entity, uint32_t base = 0, uint32_t equip = 0, uint32_t status = 0)
		: Attribute(entity, STATUS_CURRENTHP, base, equip, status)
		{ }
		~CurrentHP() { };
	};

	class CurrentSP : public Attribute<CurrentSP, BasicAttributeNotifier>
	{
	public:
		CurrentSP(std::weak_ptr<Entity> entity, uint32_t base = 0, uint32_t equip = 0, uint32_t status = 0)
		: Attribute(entity, STATUS_CURRENTSP, base, equip, status)
		{ }
		~CurrentSP() { };
	};

	class MovementSpeed : public Attribute<MovementSpeed, BasicAttributeNotifier>
	{
	public:
		MovementSpeed(std::weak_ptr<Entity> entity, uint32_t base = 0, uint32_t equip = 0, uint32_t status = 0)
		: Attribute(entity, STATUS_MOVEMENT_SPEED, base, equip, status)
		{ }
		~MovementSpeed() { }

		uint32_t get_with_cost(int cost) { return total() * cost / 10; };
	};

	class MaxWeight : public Attribute<MaxWeight, BasicAttributeNotifier>
	{
	public:
		MaxWeight(std::weak_ptr<Entity> entity, uint32_t base = 0, uint32_t equip = 0, uint32_t status = 0)
		: Attribute(entity, STATUS_MAX_WEIGHT, base, equip, status)
		{ }
		~MaxWeight() { };
	};

	class CurrentWeight : public Attribute<CurrentWeight, BasicAttributeNotifier>
	{
	public:
		CurrentWeight(std::weak_ptr<Entity> entity, uint32_t base = 0, uint32_t equip = 0, uint32_t status = 0)
		: Attribute(entity, STATUS_CURRENT_WEIGHT, base, equip, status)
		{ }
		~CurrentWeight() { };
	};

	class StatusPoint : public Attribute<StatusPoint, BasicAttributeNotifier>
	{
	public:
		StatusPoint(std::weak_ptr<Entity> entity, uint32_t base = 0)
		: Attribute(entity, STATUS_STATUSPOINT, base, 0, 0)
		{ }
		~StatusPoint() { };
	};

	class SkillPoint : public Attribute<SkillPoint, BasicAttributeNotifier>
	{
	public:
		SkillPoint(std::weak_ptr<Entity> entity, uint32_t base = 0)
		: Attribute(entity, STATUS_SKILLPOINT, base, 0, 0)
		{ }
		~SkillPoint() { };
	};

	class Strength
	: public Attribute<Strength, StatusPointNotifier>,
	  public ObservableStatus<std::weak_ptr<Strength>, std::weak_ptr<StatusATK>>
	{
		typedef ObservableStatus<std::weak_ptr<Strength>, std::weak_ptr<StatusATK>> Observable;
	public:
		Strength(std::weak_ptr<Entity> entity, uint32_t base = 0, uint32_t equip = 0, uint32_t status = 0)
		: Attribute(entity, STATUS_STRENGTH, base, equip, status), ObservableStatus(std::weak_ptr<StatusATK>())
		{ }
		~Strength() { };
	};

	class Agility
	: public Attribute<Agility, StatusPointNotifier>,
	  public ObservableStatus<std::weak_ptr<Agility>, std::weak_ptr<FLEE>>
	{
	public:
		Agility(std::weak_ptr<Entity> entity, uint32_t base = 0, uint32_t equip = 0, uint32_t status = 0)
		: Attribute(entity, STATUS_AGILITY, base, equip, status),
		  ObservableStatus(std::weak_ptr<FLEE>())
		{ }
		~Agility() { };
	};

	class Vitality
	: public Attribute<Vitality, StatusPointNotifier>,
	  public ObservableStatus<std::weak_ptr<Vitality>, std::weak_ptr<SoftDEF>, std::weak_ptr<SoftMDEF>>
	{
	public:
		Vitality(std::weak_ptr<Entity> entity, uint32_t base = 0, uint32_t equip = 0, uint32_t status = 0)
		: Attribute(entity, STATUS_VITALITY, base, equip, status),
		  ObservableStatus(std::weak_ptr<SoftDEF>(), std::weak_ptr<SoftMDEF>())
		{ }
		~Vitality() { };
	};

	class Intelligence
	: public Attribute<Intelligence, StatusPointNotifier>,
	  public ObservableStatus<std::weak_ptr<Intelligence>, std::weak_ptr<StatusMATK>, std::weak_ptr<SoftMDEF>>
	{
	public:
		Intelligence(std::weak_ptr<Entity> entity, uint32_t base = 0, uint32_t equip = 0, uint32_t status = 0)
		: Attribute(entity, STATUS_INTELLIGENCE, base, equip, status),
		  ObservableStatus(std::weak_ptr<StatusMATK>(), std::weak_ptr<SoftMDEF>())
		{ }
		~Intelligence() { };
	};

	class Dexterity
	: public Attribute<Dexterity, StatusPointNotifier>,
	  public ObservableStatus<std::weak_ptr<Dexterity>, std::weak_ptr<StatusATK>, std::weak_ptr<StatusMATK>, std::weak_ptr<SoftMDEF>, std::weak_ptr<HIT>>
	{
	public:
		Dexterity(std::weak_ptr<Entity> entity, uint32_t base = 0, uint32_t equip = 0, uint32_t status = 0)
		: Attribute(entity, STATUS_DEXTERITY, base, equip, status),
		  ObservableStatus(std::weak_ptr<StatusATK>(), std::weak_ptr<StatusMATK>(), std::weak_ptr<SoftMDEF>(), std::weak_ptr<HIT>())
		{ }
		~Dexterity() { };
	};

	class Luck
	: public Attribute<Luck, StatusPointNotifier>,
	  public ObservableStatus<std::weak_ptr<Luck>, std::weak_ptr<StatusATK>, std::weak_ptr<StatusMATK>, std::weak_ptr<HIT>, std::weak_ptr<CRIT>, std::weak_ptr<FLEE>>
	{
	public:
		Luck(std::weak_ptr<Entity> entity, uint32_t base = 0, uint32_t equip = 0, uint32_t status = 0)
		: Attribute(entity, STATUS_LUCK, base, equip, status),
		  ObservableStatus(std::weak_ptr<StatusATK>(), std::weak_ptr<StatusMATK>(), std::weak_ptr<HIT>(), std::weak_ptr<CRIT>(), std::weak_ptr<FLEE>())
		{ }
		~Luck() { };
	};

	class StrengthPointCost : public Attribute<StrengthPointCost, StatusPointRequirementNotifier>
	{
	public:
		StrengthPointCost(std::weak_ptr<Entity> entity, uint32_t base = 0)
		: Attribute(entity, STATUS_STRENGTH_COST, base, 0, 0)
		{ }
		~StrengthPointCost() { };
	};

	class AgilityPointCost : public Attribute<AgilityPointCost, StatusPointRequirementNotifier>
	{
	public:
		AgilityPointCost(std::weak_ptr<Entity> entity, uint32_t base = 0)
		: Attribute(entity, STATUS_AGILITY_COST, base, 0, 0)
		{ }
		~AgilityPointCost() { };
	};

	class VitalityPointCost : public Attribute<VitalityPointCost, StatusPointRequirementNotifier>
	{
	public:
		VitalityPointCost(std::weak_ptr<Entity> entity, uint32_t base = 0)
		: Attribute(entity, STATUS_VITALITY_COST, base, 0, 0)
		{ }
		~VitalityPointCost() { };
	};

	class IntelligencePointCost : public Attribute<IntelligencePointCost, StatusPointRequirementNotifier>
	{
	public:
		IntelligencePointCost(std::weak_ptr<Entity> entity, uint32_t base = 0)
		: Attribute(entity, STATUS_INTELLIGENCE_COST, base, 0, 0)
		{ }
		~IntelligencePointCost() { };
	};

	class DexterityPointCost : public Attribute<DexterityPointCost, StatusPointRequirementNotifier>
	{
	public:
		DexterityPointCost(std::weak_ptr<Entity> entity, uint32_t base = 0)
		: Attribute(entity, STATUS_DEXTERITY_COST, base, 0, 0)
		{ }
		~DexterityPointCost() { };
	};

	class LuckPointCost : public Attribute<LuckPointCost, StatusPointRequirementNotifier>
	{
	public:
		LuckPointCost(std::weak_ptr<Entity> entity, uint32_t base = 0)
		: Attribute(entity, STATUS_LUCK_COST, base, 0, 0)
		{ }
		~LuckPointCost() { };
	};

	class BaseExperience : public Attribute<BaseExperience, ExpAttributeNotifier>
	{
	public:
		BaseExperience(std::weak_ptr<Entity> entity,  uint32_t base = 0)
		: Attribute(entity, STATUS_BASEEXP, base, 0, 0)
		{ }
		~BaseExperience() { };

		void add_base(uint32_t val, bool notify = true) override;
	};

	class JobExperience : public Attribute<JobExperience, ExpAttributeNotifier>
	{
	public:
		JobExperience(std::weak_ptr<Entity> entity,  uint32_t base = 0)
		: Attribute(entity, STATUS_JOBEXP, base, 0, 0)
		{ }
		~JobExperience() { };
	};

	class NextBaseExperience : public Attribute<NextBaseExperience, ExpAttributeNotifier>
	{
	public:
		NextBaseExperience(std::weak_ptr<Entity> entity,  uint32_t base = 0)
		: Attribute(entity, STATUS_NEXTBASEEXP, base, 0, 0)
		{ }
		~NextBaseExperience() { };
	};

	class NextJobExperience : public Attribute<NextJobExperience, ExpAttributeNotifier>
	{
	public:
		NextJobExperience(std::weak_ptr<Entity> entity,  uint32_t base = 0)
		: Attribute(entity, STATUS_NEXTJOBEXP, base, 0, 0)
		{ }
		~NextJobExperience() { };
	};
}
}
}
}
#include "AttributesImpl.hpp"

#endif /* HORIZON_ZONE_GAME_STATUS_ATTRIBUTES_HPP */
