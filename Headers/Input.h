#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

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

	inline static const std::string YOUR_INPUT = "# Your Input: ";
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
				LogInvalid();
			else
				return *com;
		}
	}

	static const Command* GetLock(std::string& result)
	{
		std::string input = "";
		const Command* command = nullptr;
		while (true)
		{
			result.clear();
			std::cin >> input;
						
			int length = static_cast<int>(input.size());
			if (length == 0)
			{
				LogInvalid();
				continue;
			}

			// Return early, if one of the default commands was put in
			command = TryGetCommand(input);
			if (command != nullptr && *command != LOCK)
				return command;

			// The user may input millions of characters.To counter that
			// we're only considering the first 10 characters.
			std::uint32_t min = std::min(10, length);
			for (std::uint32_t i = 0; i < min; ++i)
			{
				char c = input[i];
				if (LOCK_COMMANDS.contains(c) && !result.contains(c))
					result += c;
			}

			if (result.size() == 0)
				LogInvalid();
			else
				return nullptr;
		}
	}

	static void LogInvalid()
	{
		std::cout << CLEAR_LINE;
		std::cout << INVALID_INPUT;
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