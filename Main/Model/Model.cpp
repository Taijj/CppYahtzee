#include "Model.h"

void Model::Wake()
{		
	_dice.clear();
	for (std::uint32_t i = 0; i < Die::SIDES; ++i)
		_dice.push_back(std::make_unique<Die>(i));
}

Model::Dice& Model::GetDice() { return _dice; }