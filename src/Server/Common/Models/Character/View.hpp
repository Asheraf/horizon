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

#ifndef HORIZON_MODELS_CHARACTERS_VIEW_HPP
#define HORIZON_MODELS_CHARACTERS_VIEW_HPP

#include "Server/Common/Horizon.hpp"
#include "Server/Common/Server.hpp"

namespace Horizon
{
namespace Models
{
namespace Character
{
class View
{
public:
	View(uint32_t char_id) : _character_id(char_id) {}

	~View() {}

	/**
	 * Load all fields from the database into this instance.
	 * @param server    Pointer to the invoking to borrow an sql connection from.
	 * @param char_id   Id of the character to load the view of.
	 * @return true on success, false on failure.
	 */
	bool load(Server *server, uint32_t char_id)
	{
		std::string query = "SELECT `hair_style_id`, `hair_color_id`, `cloth_color_id`, `body_id`, `weapon_id`, `shield_id`, `head_top_view_id`, `head_mid_view_id`, `head_bottom_view_id`, `robe_view_id` FROM `character_view_data` WHERE `id` = ?";

		try {
			auto s = server->get_mysql_client()->getSession();
			auto record = s.sql(query).bind(char_id).execute().fetchOne();

			if (record) {
				set_character_id(char_id);
				set_hair_style_id((uint8_t) record[0].get<int>());
				set_hair_color_id((uint16_t) record[1].get<int>());
				set_cloth_color_id((uint16_t) record[2].get<int>());
				set_body_id((uint16_t) record[3].get<int>());
				set_weapon_id((uint16_t) record[4].get<int>());
				set_shield_id((uint16_t) record[5].get<int>());
				set_head_top_view_id((uint16_t) record[6].get<int>());
				set_head_mid_view_id((uint16_t) record[7].get<int>());
				set_head_bottom_view_id((uint16_t) record[8].get<int>());
				set_robe_view_id((uint16_t) record[9].get<int>());
				return true;
			}
		} catch (const mysqlx::Error &e) {
			CoreLog->warn("View::load: {}", e.what());
		}

		return false;
	}

	/**
	 * @brief Save this model to the database in its current state.
	 * @param[in|out] server   instance of the server object used to borrow mysql connections.
	 */
	void save(Server *server)
	{
		std::string query = "REPLACE INTO `character_view_data` "
			"(`id`, `hair_style_id`, `hair_color_id`, `cloth_color_id`, `body_id`, "
			"`weapon_id`, `shield_id`, `head_top_view_id`, `head_mid_view_id`, `robe_view_id`) "
			"VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";

		try {
			auto s = server->get_mysql_client()->getSession();
			s.sql(query)
					.bind(get_character_id(),
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
		} catch (const mysqlx::Error &e) {
			CoreLog->warn("View::load: {}", e.what());
		}
	}

	/* Character Id */
	uint32_t get_character_id() const { return _character_id; }
	void set_character_id(uint32_t character_id) { _character_id = character_id; }
	/* Hair Style ID */
	uint8_t get_hair_style_id() const { return _hair_style_id; }
	void set_hair_style_id(uint8_t hair_style_id) { _hair_style_id = hair_style_id; }
	/* Hair Color ID */
	uint16_t get_hair_color_id() const { return _hair_color_id; }
	void set_hair_color_id(uint16_t hair_color_id) { _hair_color_id = hair_color_id; }
	/* Cloth Color ID */
	uint16_t get_cloth_color_id() const { return _cloth_color_id; }
	void set_cloth_color_id(uint16_t cloth_color_id) { _cloth_color_id = cloth_color_id; }
	/* Body ID */
	uint16_t get_body_id() const { return _body_id; }
	void set_body_id(uint16_t body_id) { _body_id = body_id; }
	/* Weapon ID */
	uint16_t get_weapon_id() const { return _weapon_id; }
	void set_weapon_id(uint16_t weapon_id) { _weapon_id = weapon_id; }
	/* Shield ID */
	uint16_t get_shield_id() const { return _shield_id; }
	void set_shield_id(uint16_t shield_id) { _shield_id = shield_id; }
	/* Head Top View ID */
	uint16_t get_head_top_view_id() const { return _head_top_view_id; }
	void set_head_top_view_id(uint16_t head_top_view_id) { _head_top_view_id = head_top_view_id; }
	/* Head Mid View ID */
	uint16_t get_head_mid_view_id() const { return _head_mid_view_id; }
	void set_head_mid_view_id(uint16_t head_mid_view_id) { _head_mid_view_id = head_mid_view_id; }
	/* Head Bottom View ID */
	uint16_t get_head_bottom_view_id() const { return _head_bottom_view_id; }
	void set_head_bottom_view_id(uint16_t head_bottom_view_id) { _head_bottom_view_id = head_bottom_view_id; }
	/* Robe View ID */
	uint16_t get_robe_view_id() const { return _robe_view_id; }
	void set_robe_view_id(uint16_t robe_view_id) { _robe_view_id = robe_view_id; }

private:
	uint32_t _character_id{0};
	uint8_t _hair_style_id{0};
	uint16_t _hair_color_id{0};
	uint16_t _cloth_color_id{0};
	uint16_t _body_id{0};
	uint16_t _weapon_id{0};
	uint16_t _shield_id{0};
	uint16_t _head_top_view_id{0};
	uint16_t _head_mid_view_id{0};
	uint16_t _head_bottom_view_id{0};
	uint16_t _robe_view_id{0};
};
}
}
}
#endif //HORIZON_VIEWDATA_HPP
