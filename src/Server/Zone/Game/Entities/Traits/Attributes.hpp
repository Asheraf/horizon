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
	class WeaponATK;
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

	template <class T, class NOTIFIER_TYPE>
	class Attribute;

	template <status_point_type NOTIFIABLE_TYPE, class ... NOTIFIABLES>
	class BasicAttributeNotifier // PAR_CHANGE
	{
	public:
		BasicAttributeNotifier(std::weak_ptr<Entity> entity)
		: _entity(entity)
		{ }
		~BasicAttributeNotifier() { }

		std::shared_ptr<Entity> get_entity() { return _entity.lock(); }

		template<std::size_t I = 0, typename... Tp>
		inline typename std::enable_if<(I == sizeof...(Tp)), void>::type
		notify(std::tuple<Tp...> &/*t*/) { }

		template<std::size_t I = 0, typename... Tp>
		inline typename std::enable_if<(I < sizeof...(Tp)), void>::type
		notify(std::tuple<Tp...> &t);

		void notify_sum();

		template<std::size_t I = 0, typename... Tp>
		inline typename std::enable_if<(I == sizeof...(Tp)), uint32_t >::type
		get_sum(std::tuple<Tp...> &/*t*/) { return 0; }

		template<std::size_t I = 0, typename... Tp>
		inline typename std::enable_if<(I < sizeof...(Tp)), uint32_t>::type
		get_sum(std::tuple<Tp...> &t)
		{
			std::shared_ptr<typename std::tuple_element<I, std::tuple<Tp...>>::type::element_type> notifiable = std::get<I>(t).lock();

			if (!notifiable)
				return get_sum<I + 1, Tp...>(t);

			return notifiable->total() + get_sum<I + 1, Tp...>(t);
		}

		void register_notifiables(NOTIFIABLES ... notifs) { _notifiables = std::make_tuple(notifs...); }

		virtual void notify() { notify(_notifiables); }

		status_point_type get_status_point_type() { return NOTIFIABLE_TYPE; }

	private:
		std::weak_ptr<Entity> _entity;
		std::tuple<NOTIFIABLES...> _notifiables;
	};

	template <status_point_type NOTIFIABLE_TYPE, class NOTIFIABLE>
	class ExperienceNotifier // LONG_PAR_CHANGE
	{
	public:
		ExperienceNotifier(std::weak_ptr<Entity> entity)
		: _entity(entity)
		{ }
		~ExperienceNotifier() { }

		std::shared_ptr<Entity> get_entity() { return _entity.lock(); }
		void set_notifiable(NOTIFIABLE n) { _notifiable = n; }
		void notify();

	private:
		std::weak_ptr<Entity> _entity;
		NOTIFIABLE _notifiable;
	};

	template <status_point_type NOTIFIABLE_TYPE, class NOTIFIABLE>
	class StatusPointRequirementNotifier // STATUS_CHANGE
	{
	public:
		StatusPointRequirementNotifier(std::weak_ptr<Entity> entity)
		: _entity(entity)
		{ }
		~StatusPointRequirementNotifier() { }

		std::shared_ptr<Entity> get_entity() { return _entity.lock(); }
		void set_notifiable(NOTIFIABLE n) { _notifiable = n; }
		void notify();

	private:
		std::weak_ptr<Entity> _entity;
		NOTIFIABLE _notifiable;
	};

	template <status_point_type NOTIFIABLE_TYPE, class NOTIFIABLE>
	class StatusPointNotifier // STATUS_CHANGE
	{
	public:
		StatusPointNotifier(std::weak_ptr<Entity> entity)
		: _entity(entity)
		{ }
		~StatusPointNotifier() { }

		std::shared_ptr<Entity> get_entity() { return _entity.lock(); }
		void set_notifiable(NOTIFIABLE n) { _notifiable = n; }
		void notify();

	private:
		std::weak_ptr<Entity> _entity;
		NOTIFIABLE _notifiable;
	};

	template <status_point_type NOTIFIABLE_TYPE, class NOTIFIABLE>
	class AttackRangeNotifier // ATTACK_RANGE
	{
	public:
		AttackRangeNotifier(std::weak_ptr<Entity> entity)
		: _entity(entity)
		{ }
		~AttackRangeNotifier() { }

		std::shared_ptr<Entity> get_entity() { return _entity.lock(); }
		void set_notifiable(NOTIFIABLE n) { _notifiable = n; }
		void notify();

	private:
		std::weak_ptr<Entity> _entity;
		NOTIFIABLE _notifiable;
	};

	template <class T, class NOTIFIER_TYPE>
	class Attribute
	{
	public:
		Attribute(std::weak_ptr<Entity> entity, uint32_t base = 0, uint32_t equip = 0, uint32_t status = 0)
		: _base_val(base), _equip_val(equip), _status_val(status), _notifier(entity), _entity(entity)
		{
		}
		virtual ~Attribute() { }

		std::shared_ptr<Entity> get_entity() { return _entity.lock(); }
		void set_entity(std::shared_ptr<Entity> e) { _entity = e; }

		virtual void set_base(uint32_t val, bool notify = true)
		{
			_base_val = val;

			if (notify)
				notify_update();
		}

		virtual void add_base(uint32_t val, bool notify = true) { set_base(_base_val + val, notify); }
		virtual void sub_base(uint32_t val, bool notify = true) { set_base(_base_val - std::min(_base_val, val), notify); }
		virtual uint32_t get_base() const { return _base_val; }

		virtual void set_equip(uint32_t val, bool notify = true)
		{
			_equip_val = val;

			if (notify)
				notify_update();
		}
		virtual void add_equip(uint32_t val, bool notify = true) { set_equip(_equip_val + val, notify); }
		virtual void sub_equip(uint32_t val, bool notify = true) { set_equip(_equip_val - std::min(_base_val, val), notify); }
		virtual uint32_t get_equip() const { return _equip_val; }

		virtual void set_status(uint32_t str, bool notify = true)
		{
			_status_val = str;

			if (notify)
				notify_update();
		}
		virtual void add_status(uint32_t val, bool notify = true) { set_status(_status_val + val, notify); }
		virtual void sub_status(uint32_t val, bool notify = true) { set_status(_status_val - std::min(_base_val, val), notify); }
		virtual uint32_t get_status() const { return _status_val; }

		virtual uint32_t total() const { return _base_val + _equip_val + _status_val; }

		virtual void set_notifier(NOTIFIER_TYPE notifier) { _notifier = notifier; }
		NOTIFIER_TYPE &get_notifier() { return _notifier; }

		virtual void notify_update() { _notifier.notify(); }

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
			set_base(right.get_base(), false);
			set_equip(right.get_equip(), false);
			set_status(right.get_status(), false);
			set_notifier(right._notifier);

			return *this;
		}

	protected:
		uint32_t _base_val{0};
		uint32_t _equip_val{0};
		uint32_t _status_val{0};
		NOTIFIER_TYPE _notifier;
	private:
		std::weak_ptr<Entity> _entity;
	};

	class BaseLevel
	: public Attribute<BaseLevel, BasicAttributeNotifier<STATUS_BASELEVEL, std::weak_ptr<BaseLevel>>>,
	  public ObservableStatus<std::weak_ptr<BaseLevel>, std::weak_ptr<StatusPoint>, std::weak_ptr<NextBaseExperience>, std::weak_ptr<StatusATK>, std::weak_ptr<StatusMATK>, std::weak_ptr<SoftMDEF>, std::weak_ptr<HIT>, std::weak_ptr<FLEE>>
	{
	public:
		BaseLevel(std::weak_ptr<Entity> entity,  uint32_t base = 0)
		: Attribute(entity, base, 0, 0),
		  ObservableStatus(std::weak_ptr<StatusPoint>(), std::weak_ptr<NextBaseExperience>(), std::weak_ptr<StatusATK>(), std::weak_ptr<StatusMATK>(), std::weak_ptr<SoftMDEF>(), std::weak_ptr<HIT>(), std::weak_ptr<FLEE>())
		{ }
		~BaseLevel() { };

		void set_base(uint32_t val, bool notify = true) override
		{
			Attribute::set_base(val, notify);
			this->notify_observers();
		}

		void on_observable_changed(std::weak_ptr<BaseExperience> wbexp);
	};

	class JobLevel
	: public Attribute<JobLevel, BasicAttributeNotifier<STATUS_JOBLEVEL, std::weak_ptr<JobLevel>>>,
	  public ObservableStatus<std::weak_ptr<JobLevel>, std::weak_ptr<SkillPoint>, std::weak_ptr<NextJobExperience>>
	{
	public:
		JobLevel(std::weak_ptr<Entity> entity, uint32_t base = 0)
		: Attribute(entity, base, 0, 0),
		  ObservableStatus(std::weak_ptr<SkillPoint>(), std::weak_ptr<NextJobExperience>())
		{ }
		~JobLevel() { };

		void set_base(uint32_t val, bool notify = true) override
		{
			Attribute::set_base(val, notify);
			this->notify_observers();
		}

		void on_observable_changed(std::weak_ptr<JobExperience> wjexp);
	};

	class MaxHP
	: public Attribute<MaxHP, BasicAttributeNotifier<STATUS_MAXHP, std::weak_ptr<MaxHP>>>
	{
	public:
		MaxHP(std::weak_ptr<Entity> entity, uint32_t base = 0, uint32_t equip = 0, uint32_t status = 0)
		: Attribute(entity, base, equip, status)
		{ }
		~MaxHP() { };
	};

	class MaxSP
	: public Attribute<MaxSP, BasicAttributeNotifier<STATUS_MAXSP, std::weak_ptr<MaxSP>>>
	{
	public:
		MaxSP(std::weak_ptr<Entity> entity, uint32_t base = 0, uint32_t equip = 0, uint32_t status = 0)
		: Attribute(entity, base, equip, status)
		{ }
		~MaxSP() { };
	};

	class CurrentHP
	: public Attribute<CurrentHP, BasicAttributeNotifier<STATUS_CURRENTHP, std::weak_ptr<CurrentHP>>>
	{
	public:
		CurrentHP(std::weak_ptr<Entity> entity, uint32_t base = 0, uint32_t equip = 0, uint32_t status = 0)
		: Attribute(entity, base, equip, status)
		{ }
		~CurrentHP() { };
	};

	class CurrentSP
	: public Attribute<CurrentSP, BasicAttributeNotifier<STATUS_CURRENTSP, std::weak_ptr<CurrentSP>>>
	{
	public:
		CurrentSP(std::weak_ptr<Entity> entity, uint32_t base = 0, uint32_t equip = 0, uint32_t status = 0)
		: Attribute(entity, base, equip, status)
		{ }
		~CurrentSP() { };
	};

	class MovementSpeed
	: public Attribute<MovementSpeed, BasicAttributeNotifier<STATUS_MOVEMENT_SPEED, std::weak_ptr<MovementSpeed>>>
	{
	public:
		MovementSpeed(std::weak_ptr<Entity> entity, uint32_t base = 0, uint32_t equip = 0, uint32_t status = 0)
		: Attribute(entity, base, equip, status)
		{ }
		~MovementSpeed() { }

		uint32_t get_with_cost(int cost) { return total() * cost / 10; };
	};

	class StatusPoint
	: public Attribute<StatusPoint, BasicAttributeNotifier<STATUS_STATUSPOINT, std::weak_ptr<StatusPoint>>>
	{
	public:
		StatusPoint(std::weak_ptr<Entity> entity, uint32_t base = 0)
		: Attribute(entity, base, 0, 0)
		{ }
		~StatusPoint() { };

		void on_observable_changed(std::weak_ptr<BaseLevel> wblvl);
	};

	class SkillPoint
	: public Attribute<SkillPoint, BasicAttributeNotifier<STATUS_SKILLPOINT, std::weak_ptr<SkillPoint>>>
	{
	public:
		SkillPoint(std::weak_ptr<Entity> entity, uint32_t base = 0)
		: Attribute(entity, base, 0, 0)
		{ }
		~SkillPoint() { };

		void on_observable_changed(std::weak_ptr<JobLevel> wjlvl);
	};

	class Strength
	: public Attribute<Strength, StatusPointNotifier<STATUS_STRENGTH, std::weak_ptr<Strength>>>,
	  public ObservableStatus<std::weak_ptr<Strength>, std::weak_ptr<StrengthPointCost>, std::weak_ptr<MaxWeight>, std::weak_ptr<StatusATK>, std::weak_ptr<WeaponATK>>
	{
	public:
		Strength(std::weak_ptr<Entity> entity, uint32_t base = 0, uint32_t equip = 0, uint32_t status = 0)
		: Attribute(entity, base, equip, status),
		  ObservableStatus(std::weak_ptr<StrengthPointCost>(), std::weak_ptr<MaxWeight>(), std::weak_ptr<StatusATK>(), std::weak_ptr<WeaponATK>())
		{ }
		~Strength() { };

		void set_base(uint32_t val, bool notify = true) override
		{
			Attribute::set_base(val, notify);
			this->notify_observers();
		}
	};

	class Agility
	: public Attribute<Agility, StatusPointNotifier<STATUS_AGILITY, std::weak_ptr<Agility>>>,
	  public ObservableStatus<std::weak_ptr<Agility>, std::weak_ptr<AgilityPointCost>, std::weak_ptr<FLEE>>
	{
	public:
		Agility(std::weak_ptr<Entity> entity, uint32_t base = 0, uint32_t equip = 0, uint32_t status = 0)
		: Attribute(entity, base, equip, status),
		  ObservableStatus(std::weak_ptr<AgilityPointCost>(), std::weak_ptr<FLEE>())
		{ }
		~Agility() { };

		void set_base(uint32_t val, bool notify = true) override
		{
			Attribute::set_base(val, notify);
			this->notify_observers();
		}
	};

	class Vitality
	: public Attribute<Vitality, StatusPointNotifier<STATUS_VITALITY, std::weak_ptr<Vitality>>>,
	  public ObservableStatus<std::weak_ptr<Vitality>, std::weak_ptr<VitalityPointCost>, std::weak_ptr<SoftDEF>, std::weak_ptr<SoftMDEF>>
	{
	public:
		Vitality(std::weak_ptr<Entity> entity, uint32_t base = 0, uint32_t equip = 0, uint32_t status = 0)
		: Attribute(entity, base, equip, status),
		  ObservableStatus(std::weak_ptr<VitalityPointCost>(), std::weak_ptr<SoftDEF>(), std::weak_ptr<SoftMDEF>())
		{ }
		~Vitality() { };

		void set_base(uint32_t val, bool notify = true) override
		{
			Attribute::set_base(val, notify);
			this->notify_observers();
		}
	};

	class Intelligence
	: public Attribute<Intelligence, StatusPointNotifier<STATUS_INTELLIGENCE, std::weak_ptr<Intelligence>>>,
	  public ObservableStatus<std::weak_ptr<Intelligence>, std::weak_ptr<IntelligencePointCost>, std::weak_ptr<StatusMATK>, std::weak_ptr<SoftMDEF>>
	{
	public:
		Intelligence(std::weak_ptr<Entity> entity, uint32_t base = 0, uint32_t equip = 0, uint32_t status = 0)
		: Attribute(entity, base, equip, status),
		  ObservableStatus(std::weak_ptr<IntelligencePointCost>(), std::weak_ptr<StatusMATK>(), std::weak_ptr<SoftMDEF>())
		{ }
		~Intelligence() { };

		void set_base(uint32_t val, bool notify = true) override
		{
			Attribute::set_base(val, notify);
			this->notify_observers();
		}
	};

	class Dexterity
	: public Attribute<Dexterity, StatusPointNotifier<STATUS_DEXTERITY, std::weak_ptr<Dexterity>>>,
	  public ObservableStatus<std::weak_ptr<Dexterity>, std::weak_ptr<DexterityPointCost>, std::weak_ptr<StatusATK>, std::weak_ptr<WeaponATK>, std::weak_ptr<StatusMATK>, std::weak_ptr<SoftMDEF>, std::weak_ptr<HIT>>
	{
	public:
		Dexterity(std::weak_ptr<Entity> entity, uint32_t base = 0, uint32_t equip = 0, uint32_t status = 0)
		: Attribute(entity, base, equip, status),
		  ObservableStatus(std::weak_ptr<DexterityPointCost>(), std::weak_ptr<StatusATK>(), std::weak_ptr<WeaponATK>(), std::weak_ptr<StatusMATK>(), std::weak_ptr<SoftMDEF>(), std::weak_ptr<HIT>())
		{ }
		~Dexterity() { };

		void set_base(uint32_t val, bool notify = true) override
		{
			Attribute::set_base(val, notify);
			this->notify_observers();
		}
	};

	class Luck
	: public Attribute<Luck, StatusPointNotifier<STATUS_LUCK, std::weak_ptr<Luck>>>,
	  public ObservableStatus<std::weak_ptr<Luck>, std::weak_ptr<LuckPointCost>, std::weak_ptr<StatusATK>, std::weak_ptr<StatusMATK>, std::weak_ptr<HIT>, std::weak_ptr<CRIT>, std::weak_ptr<FLEE>>
	{
	public:
		Luck(std::weak_ptr<Entity> entity, uint32_t base = 0, uint32_t equip = 0, uint32_t status = 0)
		: Attribute(entity, base, equip, status),
		  ObservableStatus(std::weak_ptr<LuckPointCost>(), std::weak_ptr<StatusATK>(), std::weak_ptr<StatusMATK>(), std::weak_ptr<HIT>(), std::weak_ptr<CRIT>(), std::weak_ptr<FLEE>())
		{ }
		~Luck() { };

		void set_base(uint32_t val, bool notify = true) override
		{
			Attribute::set_base(val, notify);
			this->notify_observers();
		}
	};

	class StrengthPointCost
	: public Attribute<StrengthPointCost, StatusPointRequirementNotifier<STATUS_STRENGTH_COST, std::weak_ptr<StrengthPointCost>>>
	{
	public:
		StrengthPointCost(std::weak_ptr<Entity> entity, uint32_t base = 0)
		: Attribute(entity, base, 0, 0)
		{ }
		~StrengthPointCost() { };

		void on_observable_changed(std::weak_ptr<Strength>);
	};

	class AgilityPointCost
	: public Attribute<AgilityPointCost, StatusPointRequirementNotifier<STATUS_AGILITY_COST, std::weak_ptr<AgilityPointCost>>>
	{
	public:
		AgilityPointCost(std::weak_ptr<Entity> entity, uint32_t base = 0)
		: Attribute(entity, base, 0, 0)
		{ }
		~AgilityPointCost() { };

		void on_observable_changed(std::weak_ptr<Agility>);
	};

	class VitalityPointCost
	: public Attribute<VitalityPointCost, StatusPointRequirementNotifier<STATUS_VITALITY_COST, std::weak_ptr<VitalityPointCost>>>
	{
	public:
		VitalityPointCost(std::weak_ptr<Entity> entity, uint32_t base = 0)
		: Attribute(entity, base, 0, 0)
		{ }
		~VitalityPointCost() { };

		void on_observable_changed(std::weak_ptr<Vitality>);
	};

	class IntelligencePointCost
	: public Attribute<IntelligencePointCost, StatusPointRequirementNotifier<STATUS_INTELLIGENCE_COST, std::weak_ptr<IntelligencePointCost>>>
	{
	public:
		IntelligencePointCost(std::weak_ptr<Entity> entity, uint32_t base = 0)
		: Attribute(entity, base, 0, 0)
		{ }
		~IntelligencePointCost() { };

		void on_observable_changed(std::weak_ptr<Intelligence>);
	};

	class DexterityPointCost
	: public Attribute<DexterityPointCost, StatusPointRequirementNotifier<STATUS_DEXTERITY_COST, std::weak_ptr<DexterityPointCost>>>
	{
	public:
		DexterityPointCost(std::weak_ptr<Entity> entity, uint32_t base = 0)
		: Attribute(entity, base, 0, 0)
		{ }
		~DexterityPointCost() { };

		void on_observable_changed(std::weak_ptr<Dexterity>);
	};

	class LuckPointCost
	: public Attribute<LuckPointCost, StatusPointRequirementNotifier<STATUS_LUCK_COST, std::weak_ptr<LuckPointCost>>>
	{
	public:
		LuckPointCost(std::weak_ptr<Entity> entity, uint32_t base = 0)
		: Attribute(entity, base, 0, 0)
		{ }
		~LuckPointCost() { };

		void on_observable_changed(std::weak_ptr<Luck>);
	};

	class BaseExperience
	: public Attribute<BaseExperience, ExperienceNotifier<STATUS_BASEEXP, std::weak_ptr<BaseExperience>>>,
	  public ObservableStatus<std::weak_ptr<BaseExperience>, std::weak_ptr<BaseLevel>>
	{
	public:
		BaseExperience(std::weak_ptr<Entity> entity,  uint32_t base = 0)
		: Attribute(entity, base, 0, 0),
		  ObservableStatus(std::weak_ptr<BaseLevel>())
		{ }
		~BaseExperience() { };

		void set_base(uint32_t val, bool notify = true) override
		{
			Attribute::set_base(val, notify);
			this->notify_observers();
		}
	};

	class JobExperience
	: public Attribute<JobExperience, ExperienceNotifier<STATUS_JOBEXP, std::weak_ptr<JobExperience>>>,
	  public ObservableStatus<std::weak_ptr<JobExperience>, std::weak_ptr<JobLevel>>
	{
	public:
		JobExperience(std::weak_ptr<Entity> entity,  uint32_t base = 0)
		: Attribute(entity, base, 0, 0),
		ObservableStatus(std::weak_ptr<JobLevel>())
		{ }
		~JobExperience() { };

		void set_base(uint32_t val, bool notify = true) override
		{
			Attribute::set_base(val, notify);
			this->notify_observers();
		}
	};

	class NextBaseExperience
	: public Attribute<NextBaseExperience, ExperienceNotifier<STATUS_NEXTBASEEXP, std::weak_ptr<NextBaseExperience>>>
	{
	public:
		NextBaseExperience(std::weak_ptr<Entity> entity,  uint32_t base = 0)
		: Attribute(entity, base, 0, 0)
		{ }
		~NextBaseExperience() { };

		void on_observable_changed(std::weak_ptr<BaseLevel> blvl);
	};

	class NextJobExperience
	: public Attribute<NextJobExperience, ExperienceNotifier<STATUS_NEXTJOBEXP, std::weak_ptr<NextJobExperience>>>
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
