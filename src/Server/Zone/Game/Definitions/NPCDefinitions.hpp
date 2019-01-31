//
//  NPCDefinitions.hpp
//  Horizon
//
//  Created by SagunKho on 26/01/2019.
//

#ifndef HORIZON_ZONE_GAME_NPC_DEFINITIONS_HPP
#define HORIZON_ZONE_GAME_NPC_DEFINITIONS_HPP

#include <string>

#define NPC_START_GUID 500000000

enum actor_classes {
	FAKE_NPC = -1,
	WARP_CLASS = 45,
	HIDDEN_WARP_CLASS = 139,
	MOB_TOMB = 565,
	WARP_DEBUG_CLASS = 722,
	FLAG_CLASS = 722,
	INVISIBLE_CLASS = 32767,
};

struct npc_data
{
	std::string npc_key{};
	std::string npc_name{};
	std::string map_name{};
	std::string parent{};
	uint16_t x{0}, y{0};
	uint8_t direction{0};
	int sprite_id{0};
};


#endif /* HORIZON_ZONE_GAME_NPC_DEFINITIONS_HPP */
