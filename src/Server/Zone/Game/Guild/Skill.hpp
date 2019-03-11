/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
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

#ifndef HORIZON_MODELS_GUILD_SKILLS_HPP
#define HORIZON_MODELS_GUILD_SKILLS_HPP

namespace Horizon
{
namespace Models
{
namespace Guild
{
class Skill
{
public:
	Skill() { }
	~Skill() { }

	/* Guild ID */
	uint32_t get_guild_id() { return _guild_id; }
	void set_guild_id(uint32_t guild_id) { _guild_id = guild_id; }

	/* Skill ID */
	uint32_t getSkillID() { return _skill_id; }
	void setSkillID(uint32_t skill_id) { _skill_id = skill_id; }

	/* Skill Level */
	uint8_t getSkillLevel() { return _skill_level; }
	void setSkillLevel(uint8_t level) { _skill_level = level; }

private:
	uint32_t _guild_id;
	uint32_t _skill_id;
	uint8_t _skill_level;
}
}
}
}

#endif /* HORIZON_MODELS_GUILD_SKILLS_HPP */
