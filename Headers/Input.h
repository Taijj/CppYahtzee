#pragma once

#include <string>
#include <iostream>
#include <vector>

#include "Utils.h"

class Command
{
public: 
	const char character;
	const std::string description;
	const std::vector<std::string> subCommands;

	std::string subData;
	bool isAvailable;
};

class Input
{
public:
	inline static Command ROLL = { 'r', "Roll all unlocked dice.", {} };
	inline static Command EXIT = { 'x', "Cancel and exit game.", {} };

	inline static Command LOCK = { 'l', "Lock selected dice for later scoring.",
	{ "1", "2", "3", "4", "5"} };
	inline static Command SCORE = { 'e', "End turn and score.",
	{ "ac", "tw", "th", "fo", "fi", "si", "3p", "4p", "fu", "ss", "sl", "ya", "ch"} };

	inline static std::string CLEAR_LINE = "\x1B[1A\x1B[2K";



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