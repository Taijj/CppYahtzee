#pragma once

#include <iostream>
#include <vector>

#include "Die.h"

class Rules
{
public:
	Rules() = delete;
	
	static constexpr std::uint32_t ROUNDS = 1;
	static constexpr std::uint32_t DICE = 5;
	static constexpr std::uint32_t REROLLS = 3;

	static constexpr std::int32_t UNDEFINED = -1;
};

class Utils
{
public: 
	Utils() = delete;

	template <typename T>
	static void Log(const T &message)
	{
		std::cout << message << std::endl;
	}

	template <typename T>
	static T GetUserInput()
	{
		T input;
		std::cin >> input;
		return input;
	}
};

class Input
{
public:
	Input() = delete;

	static constexpr char REROLL = 'r';
	static constexpr char LOCK = 'l';
	static constexpr char COUNT = 'c';
	static constexpr char EXIT = 'x';

	static std::string Get(std::string legend = {})
	{
		auto input = std::string{};		
		while (input.size() == 0)
		{	
			if(legend.size() != 0)
				Utils::Log(legend);

			input = Utils::GetUserInput<std::string>();			
			if (IsValid(input) == false)
			{
				Utils::Log("Invalid Input! Please select form the following options:");
				input.clear();
			}
		}
		
		return input;
	}

private :
	static bool IsValid(const std::string &input)
	{
		const char first = input[0];
		if (first == LOCK)
		{
			// LOCK is the command for selecting the dice and is expected to be followed by a bunch of numbers
			return input.size() > 1;
		}

		if(input.size() != 1)
			return false;
				
		switch (first)
		{
			case REROLL:
			case COUNT:
			case EXIT: return true;
			default: return false;
		};
	}
};

using GameDice = std::array<Die, Rules::DICE>;