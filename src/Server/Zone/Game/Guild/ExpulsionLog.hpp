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

#ifndef HORIZON_MODELS_GUILD_EXPULSIONLOG_HPP
#define HORIZON_MODELS_GUILD_EXPULSIONLOG_HPP

namespace Horizon
{
namespace Models
{
namespace Guild
{
class ExpulsionLog
{
public:
	ExpulsionLog() { }
	~ExpulsionLog() { }

	/* Guild ID */
	uint32_t get_guild_id() { return _guild_id; }
	void set_guild_id(uint32_t guild_id) { _guild_id = guild_id; }
	/* Expellee Name */
	std::string &getExpelleeName() { return _expellee_name; }
	void setExpelleeName(std::string const &name) { _expelle_name = name; }
	/* Reason */
	std::string &getReason() { return _reason; }
	void setReason(std::string const &reason) { _reason = reason; }

private:
	uint32_t _guild_id;
	std::string _expellee_name;
	std::string _reason;
}
}
}
}

#endif /* HORIZON_MODELS_GUILD_EXPULSIONLOG_HPP */
