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
