#pragma once

#include <string>
#include <iostream>
#include <vector>

#include "Utils.h"

using Tutorial = std::vector<std::string>;

class Command
{
public: 
	const char character;
	const std::string description;
	const std::vector<std::string> subCommands;	

	std::string subData;
	bool isAvailable;

	bool operator==(const Command& other)
	{
		return other.character == character;
	}
};

class Input
{
public:
	inline static Command ROLL = { 'r', "Roll (remaining) dice.", {} };
	inline static Command EXIT = { 'x', "Cancel and exit game.", {} };

	inline static Command LOCK = { 'l', "Select dice for later scoring and re-roll remaining dice.",
	{ "1", "2", "3", "4", "5"} };
	inline static Command SCORE = { 'e', "End turn and score.",
	{ "ac", "tw", "th", "fo", "fi", "si", "3p", "4p", "fu", "ss", "sl", "ya", "ch"} };

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



	Input() = delete;

	static const Command& Get()
	{
		std::string input;
		const Command* com = nullptr;
		while (true)
		{
			std::cin >> input;
			std::cout << CLEAR_LINE;

			com = TryGetCommand(input);
			if (com != nullptr)
				return *com;
		}
	}

private:

	static const Command* TryGetCommand(const std::string& input)
	{
		if (input.size() == 0)
			return nullptr;

		char first = input[0];

		if (first == ROLL.character)
			return &ROLL;

		if (first == EXIT.character)
			return &EXIT;

		if (input.size() < 1)
			return nullptr;

		if (first == LOCK.character)
		{
			LOCK.subData.clear();
			bool subCommandWasFound = false;
			for(std::string c : LOCK.subCommands)
			{	
				if (input.find(c) != -1 && LOCK.subData.find(c) == -1)
				{
					LOCK.subData.append(c);
					subCommandWasFound = true;
				}
			}

			return subCommandWasFound ? &LOCK : nullptr;
		}

		if (first == SCORE.character)
		{			
			SCORE.subData.clear();
			for (std::string c : SCORE.subCommands)
			{
				if (input.find(c) != -1)
				{
					SCORE.subData = c;
					return &SCORE;
				}
			}
		}

		return nullptr;
	}
};