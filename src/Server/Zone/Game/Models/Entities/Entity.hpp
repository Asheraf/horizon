
#ifndef HORIZON_ZONE_GAME_ENTITIES_ENTITY_HPP
#define HORIZON_ZONE_GAME_ENTITIES_ENTITY_HPP

#include "Server/Common/Horizon.hpp"
#include "Server/Zone/Game/Models/Entities/GridObject.hpp"

#include <stdlib.h>
#include <memory>

enum entity_type
{
	ENTITY_OBJECT     = 0,
	ENTITY_PLAYER     = 1,
	ENTITY_CREATURE   = 2,
	ENTITY_PET        = 3,
	ENTITY_HOMUNCULUS = 4,
	ENTITY_MERCENARY  = 5,
	ENTITY_ITEM       = 6,
	ENTITY_NPC        = 7,
	ENTITY_CHATROOM   = 8,
	ENTITY_ELEMENTAL  = 9
};

enum entity_type_mask
{
	ENTITY_MASK_OBJECT     = 0x000,
	ENTITY_MASK_PLAYER     = 0x001,
	ENTITY_MASK_CREATURE   = 0x002,
	ENTITY_MASK_PET        = 0x004,
	ENTITY_MASK_HOMUNCULUS = 0x008,
	ENTITY_MASK_MERCENARY  = 0x010,
	ENTITY_MASK_ITEM       = 0x020,
	ENTITY_MASK_SKILL      = 0x040,
	ENTITY_MASK_NPC        = 0x080,
	ENTITY_MASK_CHATROOM   = 0x100,
	ENTITY_MASK_ELEMENTAL  = 0x200,
	ENTITY_MASK_ALL        = 0xFFF
};

namespace Horizon
{
namespace Zone
{
namespace Game
{
class Entity : public std::enable_shared_from_this<Horizon::Zone::Game::Entity>
{
public:
	Entity(uint32_t guid);
	~Entity();

	uint32_t getGUID() { return _guid; }
	bool isInZone() { return _in_zone; }
	void setInZone() { _in_zone = true; }

	entity_type getEntityType() { return _type; }
	void setEntityType(entity_type type) { _type = type; }

private:
	uint32_t _guid{0};
	entity_type _type{ENTITY_OBJECT};
	bool _in_zone{false};
};
}
}
}

#endif /* HORIZON_ZONE_GAME_ENTITIES_ENTITY_HPP */
