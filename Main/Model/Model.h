#pragma once

#include <vector>
#include <array>
#include <memory>

#include "../Global/Rules.h"
#include "../Global/ScoreKinds.h"
#include "Die.h"
#include "Combos.h"	



/// <summary>
/// Model part of the MVC pattern. Holds and processes the game's data.
/// </summary>
class Model
{	

public:
		
	using Dice = std::vector<std::unique_ptr<Die>>;
	using Combos = std::array<std::unique_ptr<Combo>, Rules::ROUND_COUNT>;

	
	
	Model() = delete;	

	static void Wake();

	/// <summary>
	/// Returns an array containing unique pointers to all needed Dies (the class)
	/// for one game.
	/// </summary>
	static Dice& GetDice();


	/// <summary>
	/// Holds unique pointers to all the Game's achieveable
	/// Combos.
	/// </summary>
	inline static const Combos COMBOS =
	{
		std::make_unique<ComboFace>("Aces", 1),
		std::make_unique<ComboFace>("Twos", 2),
		std::make_unique<ComboFace>("Threes", 3),
		std::make_unique<ComboFace>("Fours", 4),
		std::make_unique<ComboFace>("Fives", 5),
		std::make_unique<ComboFace>("Sixes", 6),

		std::make_unique<ComboOfKind>("3 of a Kind", Score::OfKind3, 3),
		std::make_unique<ComboOfKind>("4 of a Kind", Score::OfKind4, 4),
		std::make_unique<ComboFullHouse>("Full House"),
		std::make_unique<ComboStraight>("Small Straight", Score::StraightSmall, 4, 30),
		std::make_unique<ComboStraight>("Large Straight", Score::StraightLarge, 5, 40),
		std::make_unique<ComboOfKind>("Yahtzee", Score::Yahtzee, 5, 50),

		std::make_unique<ComboChance>("Chance")
	};

private:
	inline static Dice _dice = Dice{ Die::SIDES };	
};