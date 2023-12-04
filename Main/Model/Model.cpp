#include "Model.h"

void Model::Wake(std::uint32_t playerCount)
{		
	_dice.clear();
	for (std::uint32_t i = 0; i < Rules::DIE_COUNT; ++i)
		_dice.push_back(std::make_unique<Die>(i));

	_players.clear();
	for (std::uint32_t i = 0; i < playerCount; i++)
		_players.push_back(std::make_unique<Player>(i));
}

Model::Dice& Model::GetDice() { return _dice; }
Model::Players& Model::GetPlayers() { return _players; }