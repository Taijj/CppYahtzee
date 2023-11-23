#pragma once

#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

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

	static void WaitFor(const float seconds)
	{
		std::this_thread::sleep_for(std::chrono::duration<float>(seconds));
	}
};

using GameDice = std::array<Die, Rules::DICE>;