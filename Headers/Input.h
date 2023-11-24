#pragma once

#include <string>
#include <iostream>
#include <vector>

#include "Utils.h"

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
	inline static Command THROW = { 't', "Throw (remaining) dice."};
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



	inline static const std::string CLEAR_LINE = "\x1B[1A\x1B[2K";
		
	inline static const auto LOCK_TUTORIAL = Tutorial {
		"# When selecting dice add numbers after the command to select the dice by id!",
		"Example: 'l125' will select the dices 1, 2, and 5."
	};
		
	inline static const auto SCORE_TUTORIAL = Tutorial{
		"# When scoring, select how you want to score by adding one of the following after the command:",		
		" ac - Aces\t\t tw - Twos\t\t th - Threes\t",
		" fo - Fours\t\t fi - Fives\t\t si - Sixes\t",
		" 3p - 3 of a Kind\t 4p - 4 of a Kind\t fu - Full House\t",
		" ss - Small Straight\t sl - Large Straight\t ya - Yahtzee\t",
		" ch - Chance"
	};

	inline static const std::string INVALID_INPUT = "# INVALID INPUT! Please try again: ";



	Input() = delete;

	static const Command& GetRound()
	{
		std::string input;
		const Command* com = nullptr;
		while (true)
		{
			std::cin >> input;
			com = TryGetCommand(input);
			
			if (com == nullptr)
			{
				std::cout << CLEAR_LINE;
				std::cout << INVALID_INPUT;
			}
			else
			{
				return *com;
			}
		}
	}

	static const std::string GetLock()
	{
		return "TODO";
	}

private:

	static const Command* TryGetCommand(const std::string& input)
	{
		if (input.size() == 0)
			return nullptr;

		char first = input[0];		
		if (first == THROW.character)
			return &THROW;
		else if (first == EXIT.character)
			return &EXIT;
		else if (first == LOCK.character)
			return &LOCK;
		else if (first == SCORE.character)
			return &SCORE;		
		else
			return nullptr;
	}
};