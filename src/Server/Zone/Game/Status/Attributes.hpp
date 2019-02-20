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
 * Base Author - Sagun Khosla. (sagunxp@gmail.com)
 *
 * Under a proprietary license this file is not for use
 * or viewing without permission.
 **************************************************/

#ifndef HORIZON_ZONE_GAME_STATUS_ATTRIBUTES_HPP
#define HORIZON_ZONE_GAME_STATUS_ATTRIBUTES_HPP

#include <stdio.h>
#include <cstdint>
#include <type_traits>
#include <memory>
#include <cmath>

namespace Horizon
{
namespace Zone
{
namespace Game
{
namespace Status
{
	template <class T>
	class Attribute
	{
	public:
		Attribute(uint32_t base = 0, uint32_t equip = 0, uint32_t status = 0)
		: _base_total(base), _equip_total(equip), _status_total(status)
		{ }
		~Attribute() { }

		void set_base_total(uint32_t str) { _base_total = str; }
		uint32_t get_base_total() const { return _base_total; }

		void set_equip_total(uint32_t str) { _equip_total = str; }
		uint32_t get_equip_total() const { return _equip_total; }

		void set_status_total(uint32_t str) { _status_total = str; }
		uint32_t get_status_total() const { return _status_total; }

		uint32_t total() const { return _base_total + _equip_total + _status_total; }

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

		Attribute<T> operator = (Attribute<T> const &right)
		{
			set_base_total(right.get_base_total());
			set_equip_total(right.get_equip_total());
			set_status_total(right.get_status_total());

			return *this;
		}

	private:
		uint32_t _base_total{0};
		uint32_t _equip_total{0};
		uint32_t _status_total{0};
	};

	class Strength : public Attribute<Strength>
	{
	public:
		Strength(uint32_t base = 0, uint32_t equip = 0, uint32_t status = 0)
		: Attribute(base, equip, status)
		{ }
		~Strength() { }
	};

	class Agility : public Attribute<Agility>
	{
	public:
		Agility(uint32_t base = 0, uint32_t equip = 0, uint32_t status = 0)
		: Attribute(base, equip, status)
		{ }
		~Agility() { }
	};

	class Vitality : public Attribute<Vitality>
	{
	public:
		Vitality(uint32_t base = 0, uint32_t equip = 0, uint32_t status = 0)
		: Attribute(base, equip, status)
		{ }
		~Vitality() { }
	};

	class Intelligence : public Attribute<Intelligence>
	{
	public:
		Intelligence(uint32_t base = 0, uint32_t equip = 0, uint32_t status = 0)
		: Attribute(base, equip, status)
		{ }
		~Intelligence() { }
	};

	class Dexterity : public Attribute<Dexterity>
	{
	public:
		Dexterity(uint32_t base = 0, uint32_t equip = 0, uint32_t status = 0)
		: Attribute(base, equip, status)
		{ }
		~Dexterity() { }
	};

	class Luck : public Attribute<Luck>
	{
	public:
		Luck(uint32_t base = 0, uint32_t equip = 0, uint32_t status = 0)
		: Attribute(base, equip, status)
		{ }
		~Luck() { }
	};

	class StatusATK
	{
	public:
		StatusATK(uint32_t blevel, std::weak_ptr<Strength> str, std::weak_ptr<Dexterity> dex, std::weak_ptr<Luck> luk)
		: _base_level(blevel), _str(str), _dex(dex), _luk(luk)
		{ }
		~StatusATK() { }

		uint32_t get()
		{
			std::shared_ptr<Strength> str = _str.lock();
			std::shared_ptr<Dexterity> dex = _dex.lock();
			std::shared_ptr<Luck> luk = _luk.lock();

			if (str && dex && luk)
				return std::floor(*str + (_base_level / 4) + (*dex / 5) + (*luk / 3));

			return _base_level / 4 + 1 + (1 / 5) + (1 / 3);
		}

		uint32_t _base_level{1};
		std::weak_ptr<Strength> _str;
		std::weak_ptr<Dexterity> _dex;
		std::weak_ptr<Luck> _luk;
	};
}
}
}
}
#endif /* HORIZON_ZONE_GAME_STATUS_ATTRIBUTES_HPP */
