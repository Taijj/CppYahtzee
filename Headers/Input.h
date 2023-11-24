#pragma once

#include "Renderer.h"

using Tutorial = std::vector<std::string>;
using ScoreCommands = std::vector<std::pair<std::string, Score>>;

class Command
{
public: 
	const char character;
	const std::string description;
	
	bool operator==(const Command& other)
	{
		return other.character == character;
	}
};

class Input
{

public:
	inline static Command THROW = { 't', "Throw dice."};
	inline static Command EXIT = { 'x', "Cancel and exit game."};
	inline static Command LOCK = { 'l', "Select dice for later scoring." };
	inline static Command SCORE = { 's', "End turn and start scoring." };	

	inline static const std::string LOCK_COMMANDS = "12345";
	inline static const ScoreCommands SCORE_COMMANDS =
	{
		{"1", Score::Aces },
		{"2", Score::Twos },
		{"3", Score::Threes },
		{"4", Score::Fours },
		{"5", Score::Fives },
		{"6", Score::Sixes },
		{"ac", Score::OfKind3 },
		{"ac", Score::OfKind4 },
		{"ac", Score::FullHouse },
		{"ac", Score::StraightSmall },
		{"ac", Score::StraightLarge },
		{"ac", Score::Yahtzee },
		{"ac", Score::Chance }
	};	

	
		
	inline static const auto LOCK_TUTORIAL = Tutorial {
		"# Select one or multiple dice by typing in one or more numbers from 1-5.",
		"# Example: '125' will select the dice 1, 2, and 5.\n",		
		"# Use the default command to continue or end your turn:"
	};
		
	inline static const auto SCORE_TUTORIAL = Tutorial{
		"# When scoring, select how you want to score by adding one of the following after the command:",		
		" ac - Aces\t\t tw - Twos\t\t th - Threes\t",
		" fo - Fours\t\t fi - Fives\t\t si - Sixes\t",
		" 3p - 3 of a Kind\t 4p - 4 of a Kind\t fu - Full House\t",
		" ss - Small Straight\t sl - Large Straight\t ya - Yahtzee\t",
		" ch - Chance"
	};	



	Input() = delete;

	static const Command GetDefault();
	static const Command* GetLock(std::string& result);

	static bool IsExitConfirmed();

private:

	static const Command* TryGetCommand(const std::string& input);
};