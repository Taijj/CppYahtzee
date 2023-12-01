#pragma once

#include <vector>
#include <array>
#include <memory>

#include "Rules.h"
#include "Die.h"
#include "Combos.h"	



class Model
{	

public:

	using Dice = std::vector<std::unique_ptr<Die>>;
	using Combos = std::array<std::unique_ptr<Combo>, Rules::ROUND_COUNT>;

	
	
	Model() = delete;	

	static void Wake();

	static Dice& GetDice();



	inline static const Combos COMBOS =
	{
		std::make_unique<ComboFace>("Aces", 1),
		std::make_unique<ComboFace>("Twos", 2),
		std::make_unique<ComboFace>("Threes", 3),
		std::make_unique<ComboFace>("Fours", 4),
		std::make_unique<ComboFace>("Fives", 5),
		std::make_unique<ComboFace>("Sixes", 6),

		std::make_unique<ComboOfKind>("3 of a Kind", Combo::OfKind3, 3),
		std::make_unique<ComboOfKind>("4 of a Kind", Combo::OfKind4, 4),
		std::make_unique<ComboFullHouse>("Full House"),
		std::make_unique<ComboStraight>("Small Straight", Combo::StraightSmall, 4, 30),
		std::make_unique<ComboStraight>("Large Straight", Combo::StraightLarge, 5, 40),
		std::make_unique<ComboOfKind>("Yahtzee", Combo::Yahtzee, 5, 50),

		std::make_unique<ComboChance>("Chance")
	};

private:
	inline static Dice _dice = Dice{ Die::SIDES };	
};