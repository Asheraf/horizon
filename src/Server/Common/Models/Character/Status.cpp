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

#include "Status.hpp"
#include "Server/Common/Server.hpp"

#include <mysqlx/xdevapi.h>

using namespace Horizon::Models::Character;

/**
 * Load all fields from the database into this instance.
 * @param server
 * @param char_id
 * @return
 */
bool Status::load(Server *server, uint32_t char_id)
{
	std::string query = "SELECT `job_id`, `base_level`, `job_level`, `base_experience`, `job_experience`, `zeny`, "
						"`strength`, `agility`, `vitality`, `intelligence`, `dexterity`, `luck`, "
						"`maximum_hp`, `maximum_sp`, `hp`, `sp`, `status_points`, `skill_points`, "
						"`body_state`, `virtue`, `honor`, `manner`, "
						"`hair_style_id`, `hair_color_id`, `cloth_color_id`, "
						"`body_id`, `weapon_id`, `shield_id`, `head_top_view_id`, `head_mid_view_id`, `head_bottom_view_id`, `robe_view_id`"
						"FROM `character_status_data` WHERE `id` = ?";

	try {
		auto s = server->get_mysql_client()->getSession();
		auto record = s.sql(query).bind(char_id).execute().fetchOne();

		if (record) {
			set_character_id(char_id);
			set_job_id((uint16_t) record[0].get<int>());
			set_base_level((uint16_t) record[1].get<int>());
			set_job_level((uint16_t) record[2].get<int>());
			set_base_exp(record[3]);
			set_job_exp(record[4]);
			set_zeny(record[5]);
			set_strength((uint16_t) record[6].get<int>());
			set_agility((uint16_t) record[7].get<int>());
			set_vitality((uint16_t)record[8].get<int>());
			set_intelligence((uint16_t) record[9].get<int>());
			set_dexterity((uint16_t) record[10].get<int>());
			set_luck((uint16_t) record[11].get<int>());
			set_max_hp(record[12]);
			set_max_sp(record[13]);
			set_hp(record[14]);
			set_sp(record[15]);
			set_status_points(record[16]);
			set_skill_points(record[17]);
			set_body_state(record[18]);
			set_virtue((uint16_t) record[19].get<int>());
			set_honor((uint16_t) record[20].get<int>());
			set_manner((uint16_t) record[21].get<int>());
			set_hair_style_id((uint8_t) record[22].get<int>());
			set_hair_color_id((uint16_t) record[23].get<int>());
			set_cloth_color_id((uint16_t) record[24].get<int>());
			set_body_id((uint16_t) record[25].get<int>());
			set_weapon_id((uint16_t) record[26].get<int>());
			set_shield_id((uint16_t) record[27].get<int>());
			set_head_top_view_id((uint16_t) record[28].get<int>());
			set_head_mid_view_id((uint16_t) record[29].get<int>());
			set_head_bottom_view_id((uint16_t) record[30].get<int>());
			set_robe_view_id((uint16_t) record[31].get<int>());
			s.close();
			return true;
		}
		s.close();
	} catch (const mysqlx::Error &e) {
		CoreLog->warn("Status::load: {}", e.what());
	}

	return false;
}

/**
 * @brief Save this model to the database in its current state.
 * @param[in|out] server   instance of the server object used to borrow mysql connections.
 */
bool Status::save(Server *server)
{
	std::string query = "REPLACE INTO `character_status_data` "
		"(`id`, `job_id`, `base_level`, `job_level`, "
		"`base_experience`, `job_experience`, `zeny`, "
		"`strength`, `agility`, `vitality`, `intelligence`, `dexterity`, `luck`, "
		"`maximum_hp`, `maximum_sp`, `hp`, `sp`, `status_points`, `skill_points`, "
		"`body_state`, `virtue`, `honor`, `manner`, "
		"`hair_style_id`, `hair_color_id`, `cloth_color_id`, `body_id`, "
		"`weapon_id`, `shield_id`, `head_top_view_id`, `head_mid_view_id`, `robe_view_id`) "
		"VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?);";

	try {
		auto s = server->get_mysql_client()->getSession();
		s.sql(query)
				.bind(get_character_id(),
					  get_job_id(),
					  get_base_level(),
					  get_job_level(),
					  get_base_exp(),
					  get_job_exp(),
					  get_zeny(),
					  get_strength(),
					  get_agility(),
					  get_vitality(),
					  get_intelligence(),
					  get_dexterity(),
					  get_luck(),
					  get_max_hp(),
					  get_max_sp(),
					  get_hp(),
					  get_sp(),
					  get_status_points(),
					  get_skill_points(),
					  get_body_state(),
					  get_virtue(),
					  get_honor(),
					  get_manner(),
					  get_hair_style_id(),
					  get_hair_color_id(),
					  get_cloth_color_id(),
					  get_body_id(),
					  get_weapon_id(),
					  get_shield_id(),
					  get_head_top_view_id(),
					  get_head_mid_view_id(),
					  get_robe_view_id())
				.execute();
		s.close();
		return true;
	} catch (const mysqlx::Error &e) {
		CoreLog->warn("Status::save: {}", e.what());
	}

	return false;
}
