#ifndef HORIZON_ZONE_GAME_ENTITIES_UNIT_HPP
#define HORIZON_ZONE_GAME_ENTITIES_UNIT_HPP

#include "Server/Zone/Game/Entities/Entity.hpp"
#include "Server/Zone/Game/Map/Path/AStar.hpp"


namespace Horizon
{
namespace Zone
{
namespace Game
{
namespace Entities
{
class Unit : public Entity
{
public:
	Unit(uint32_t guid, entity_type type);
	Unit(uint32_t guid, entity_type type, MapCoords mcoords);
	Unit(uint32_t guid, entity_type type, MapCoords mcoords, GridCoords gcoords);
	~Unit();

	virtual void initialize() override;
	virtual bool move_to_pos(uint16_t x, uint16_t y);
	bool schedule_movement(MapCoords mcoords);
	void move();
	virtual void update(uint32_t diff) override;
	virtual void update_status() = 0;
	virtual void update_position(uint16_t /*x*/, uint16_t /*y*/) { }
	virtual void stop_movement() = 0;
	virtual void update_viewport() = 0;

	/**
	 * Unit Data
	 */
	uint16_t get_job_id() const { return _job_id; }
	void set_job_id(uint16_t job_id) { _job_id = job_id; }

	uint16_t get_hair_color_id() const { return _hair_color_id; }
	void set_hair_color_id(uint16_t id) { _hair_color_id = id; }

	uint16_t get_cloth_color_id() const { return _cloth_color_id; }
	void set_cloth_color_id(uint16_t id) { _cloth_color_id = id; }

	uint32_t get_weapon_id() const { return _weapon_id; }
	void set_weapon_id(uint32_t id) { _weapon_id = id; }

	uint32_t get_shield_id() const { return _shield_id; }
	void set_shield_id(uint32_t id) { _shield_id = id; }

	uint32_t get_robe_id() const { return _robe_id; }
	void set_robe_id(uint32_t id) { _robe_id = id; }

	uint32_t get_head_top_id() const { return _head_top_id; }
	void set_head_top_id(uint32_t id) { _head_top_id = id; }

	uint32_t get_head_mid_id() const { return _head_mid_id; }
	void set_head_mid_id(uint32_t id) { _head_mid_id = id; }

	uint32_t get_head_bottom_id() const { return _head_bottom_id; }
	void set_head_bottom_id(uint32_t id) { _head_bottom_id = id; }

	uint32_t get_hair_style_id() const { return _hair_style_id; }
	void set_hair_style_id(uint32_t id) { _hair_style_id = id; }

	uint32_t get_body_style_id() const { return _body_style_id; }
	void set_body_style_id(uint32_t id) { _body_style_id = id; }

	uint8_t get_gender() const { return _gender; }
	void set_gender(uint8_t id) { _gender = id; }

	uint8_t get_posture() const { return _posture; }
	void set_posture(uint8_t id) { _posture = id; }

	uint16_t get_base_level() const { return _base_level; }
	void set_base_level(uint16_t lvl) { _base_level = lvl; }

	uint16_t get_job_level() const { return _job_level; }
	void set_job_level(uint16_t lvl) { _job_level = lvl; }

	uint32_t get_max_hp() const { return _max_hp; }
	void set_max_hp(uint32_t hp) { _max_hp = hp; }

	uint32_t get_max_sp() const { return _max_sp; }
	void set_max_sp(uint32_t sp) { _max_sp = sp; }

	uint32_t get_hp() const { return _hp; }
	void set_hp(uint32_t hp) { _hp = hp; }

	uint32_t get_sp() const { return _sp; }
	void set_sp(uint32_t sp) { _sp = sp; }

	const std::string &get_name() const { return _name; }
	void set_name(std::string &name) { _name = name; }

	const uint8_t get_direction() const { return _facing_dir; }
	void set_direction(uint8_t dir) { _facing_dir = dir; }

private:
	MapCoords _changed_dest_pos{0, 0}, _dest_pos{0, 0};
	AStar::CoordinateList _walk_path;

	// Unit Data
	std::string _name{""};
	uint32_t _max_hp{0}, _max_sp{0}, _hp{0}, _sp{0};
	uint16_t _base_level{0}, _job_level{0};
	uint16_t _job_id{0}, _hair_color_id{0}, _cloth_color_id{0};
	uint32_t _weapon_id{0}, _shield_id{0}, _robe_id{0}, _head_top_id{0}, _head_mid_id{0}, _head_bottom_id{0};
	uint32_t _hair_style_id{0}, _body_style_id{0};
	uint8_t _gender{0}, _posture{0}, _facing_dir{DIR_NORTH};
};
}
}
}
}

#endif /* HORIZON_ZONE_GAME_ENTITIES_UNIT_HPP */
