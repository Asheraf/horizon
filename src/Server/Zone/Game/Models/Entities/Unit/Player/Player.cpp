
#include "Player.hpp"
#include "Server/Common/Models/Character/Character.hpp"

Horizon::Zone::Game::Entities::Player::Player(uint32_t guid, std::shared_ptr<Character> c)
: Horizon::Zone::Game::Entities::Unit(guid), _character(c)
{
	//
}


Horizon::Zone::Game::Entities::Player::~Player()
{
	//
}
