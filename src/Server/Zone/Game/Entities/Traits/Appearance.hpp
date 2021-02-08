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

#ifndef HORIZON_ZONE_GAME_TRAITS_APPEARANCE_HPP
#define HORIZON_ZONE_GAME_TRAITS_APPEARANCE_HPP

#include "Server/Common/Definitions/EntityDefinitions.hpp"

#include <cstdint>
#include <memory>

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
	class Appearance
	{
	public:
		Appearance(std::weak_ptr<Entity> entity, entity_appearance_type type, uint32_t id = 0)
		: _entity(entity), _type(type), _id(id)
		{ }
		virtual ~Appearance() { }

		void set(uint32_t id) { _id = id; }
		uint32_t get() { return _id; }

		virtual void notify_update();

	protected:
		std::shared_ptr<Entity> get_entity() { return _entity.lock(); }

	private:
		std::weak_ptr<Entity> _entity;
		entity_appearance_type _type;
		uint32_t _id{0};
	};

	class BaseAppearance : public Appearance
	{
	public:
		BaseAppearance(std::weak_ptr<Entity> entity, uint32_t id = 0)
		: Appearance(entity, EAT_BASE, id)
		{ }
		~BaseAppearance() { }
	};

	class HairColor : public Appearance
	{
	public:
		HairColor(std::weak_ptr<Entity> entity, uint32_t id = 0)
		: Appearance(entity, EAT_HAIR_COLOR, id)
		{ }
		~HairColor() { }
	};

	class ClothColor : public Appearance
	{
	public:
		ClothColor(std::weak_ptr<Entity> entity, uint32_t id = 0)
		: Appearance(entity, EAT_CLOTH_COLOR, id)
		{ }
		~ClothColor() { }
	};

	class WeaponSprite : public Appearance
	{
	public:
		WeaponSprite(std::weak_ptr<Entity> entity, uint32_t id = 0)
		: Appearance(entity, EAT_WEAPON_SPRITE, id)
		{ }
		~WeaponSprite() { }
	};

	class ShieldSprite : public Appearance
	{
	public:
		ShieldSprite(std::weak_ptr<Entity> entity, uint32_t id = 0)
		: Appearance(entity, EAT_SHIELD_SPRITE, id)
		{ }
		~ShieldSprite() { }
	};

	class RobeSprite : public Appearance
	{
	public:
		RobeSprite(std::weak_ptr<Entity> entity, uint32_t id = 0)
		: Appearance(entity, EAT_ROBE_SPRITE, id)
		{ }
		~RobeSprite() { }
	};

	class HeadTopSprite : public Appearance
	{
	public:
		HeadTopSprite(std::weak_ptr<Entity> entity, uint32_t id = 0)
		: Appearance(entity, EAT_HEAD_TOP_SPRITE, id)
		{ }
		~HeadTopSprite() { }
	};

	class HeadMidSprite : public Appearance
	{
	public:
		HeadMidSprite(std::weak_ptr<Entity> entity, uint32_t id = 0)
		: Appearance(entity, EAT_HEAD_MID_SPRITE, id)
		{ }
		~HeadMidSprite() { }
	};

	class HeadBottomSprite : public Appearance
	{
	public:
		HeadBottomSprite(std::weak_ptr<Entity> entity, uint32_t id = 0)
		: Appearance(entity, EAT_HEAD_BOTTOM_SPRITE, id)
		{ }
		~HeadBottomSprite() { }
	};

	class HairStyle : public Appearance
	{
	public:
		HairStyle(std::weak_ptr<Entity> entity, uint32_t id = 0)
		: Appearance(entity, EAT_HAIR_STYLE, id)
		{ }
		~HairStyle() { }
	};

	class BodyStyle : public Appearance
	{
	public:
		BodyStyle(std::weak_ptr<Entity> entity, uint32_t id = 0)
		: Appearance(entity, EAT_BODY_STYLE, id)
		{ }
		~BodyStyle() { }
	};
}
}
}
}

#include "AppearanceImpl.hpp"
#endif /* HORIZON_ZONE_GAME_STATUS_APPEARANCE_HPP */
