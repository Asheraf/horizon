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

#ifndef HORIZON_MODELS_GUILD_GUILD_HPP
#define HORIZON_MODELS_GUILD_GUILD_HPP

#include "Core/Multithreading/LockedUnorderedMap.hpp"

namespace Horizon
{
namespace Models
{
namespace Guild
{
class Guild
{
public:
	Guild() { }
	~Guild() { }

	/* ID */
	uint32_t get_id() { return _id; }
	void set_id(uint32_t id) { _id = id; }
	/* Name */
	const std::string &getGuildName() { return _name; }
	void setGuildName(std::string const &name) { _name = name; }
	/* Leader ID */
	uint32_t getLeaderID() { return _leader_id; }
	void setLeaderID(uint32_t id) { _leader_id = id; }
	/* Guild Level */
	uint8_t getGuildLevel() { return _guild_lv; }
	void setGuildLevel(uint8_t level) { _guild_level = level; }
	/* Member Limit */
	uint8_t getMemberLimit() { return _member_limit; }
	void setMemberLimit(uint8_t limit) { _member_limit = limit; }
	/* Member Level Average */
	uint16_t getMemberLevelAverage() { return _member_level_average; }
	void setMemberLevelAverage(uint16_t average) { _member_level_average = average; }
	/* Total Experience */
	uint64_t getTotalExperience() { return _total_experience; }
	void setTotalExperience(uint64_t exp) { _total_experience = exp; }
	/* Required Experience to the next level */
	uint64_t getNextRequiredExperience() { return _required_experience; }
	void setNextRequiredExperience(uint64_t exp) { _required_experience = exp; }
	/* Skill Points */
	uint16_t get_skill_points() { return _skill_points; }
	void set_skill_points(uint16_t skill_points) { _skill_points = skill_points; }
	/* Notice Title */
	std::string &getNoticeTitle() { return _notice_title; }
	void setNoticeTitle(std::string const &title) { _notice_title = title; }
	/* Notice Content */
	std::string &getNoticeContent() { return _notice_content; }
	void setNoticeContent(std::string const &content) { _notice_content = content; }
	/* Emblem Data Size */
	uint32_t getEmblemDataSize() { return _emblem_data_size; }
	void setEmblemDataSize(uint32_t size) { return _emblem_data_size; }
	/* Emblem Version */
	uint32_t getEmblemVersion() { return _emblem_version; }
	void setEmblemVersion(uint32_t version) { _emblem_version = version; }

private:
	uint32_t _id;
	std::string _name;
	uint32_t _leader_id;
	uint8_t _guild_level;
	uint8_t _member_limit;
	uint16_t _member_level_average;
	uint64_t _total_experience;
	uint64_t _required_experience;
	uint16_t _skill_points;
	std::string _notice_title;
	std::string _notice_content;
	uint32_t _emblem_data_size;
	uint32_t _emblem_version;
	
	/* Relations */
	std::unordered_map<uint32_t, Affiliation> _affiliations;
	std::unordered_map<std::string, ExpulsionLog> _expulsion_log;
	std::unordered_map<uint32_t, Member> _members;
	std::unordered_map<uint8_t, Position> _positions;
	std::unordered_map<uint32_t, Skill> _skills;
}
}
}
}

#endif /* HORIZON_MODELS_GUILD_GUILD_HPP */
