#pragma once

#include <vector>
#include <array>
#include <memory>

#include "../Global/Rules.h"
#include "../Global/ScoreKinds.h"
#include "Die.h"
#include "Combos.h"	
#include "Player.h"



/// <summary>
/// Model part of the MVC pattern. Holds and processes the game's data.
/// </summary>
class Model
{	

public:
		
	using Dice = std::vector<std::unique_ptr<Die>>;
	using Combos = std::array<std::unique_ptr<Combo>, Rules::ROUND_COUNT>;
	using Players = std::vector<std::unique_ptr<Player>>;

	
	
	Model() = delete;	

	static void Wake(std::uint32_t playerCount);



	/// <summary>
	/// Returns an array containing unique pointers to all needed Dies (the class)
	/// for one game.
	/// </summary>
	static Dice& GetDice();

	/// <summary>
	/// Returns an array containing unique pointers to all needed Players (the class)
	/// for one game.
	/// </summary>
	static Players& GetPlayers();

	/// <summary>
	/// Returns a reference to the player with the current highest score.
	/// </summary>
	static Player& GetCurrentLeader();


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
		std::make_unique<ComboStraight>("S. Straight", Score::StraightSmall, 4, 30),
		std::make_unique<ComboStraight>("L. Straight", Score::StraightLarge, 5, 40),
		std::make_unique<ComboOfKind>("Yahtzee", Score::Yahtzee, 5, 50),

		std::make_unique<ComboChance>("Chance")
	};

private:

	inline static Dice _dice = Dice{ Rules::DIE_SIDES };
	inline static Players _players = Players{ Rules::MAX_PLAYER_COUNT };
};