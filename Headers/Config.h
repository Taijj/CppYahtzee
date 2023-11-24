#pragma once
#include <cstdint>
#include <array>

#include "Die.h"

enum Score
{
	Undefined = 0,

	Aces,
	Twos,
	Threes,
	Fours,
	Fives,
	Sixes,

	OfKind3,
	OfKind4,
	FullHouse,
	StraightSmall,
	StraightLarge,
	Yahtzee,

	Chance
};

namespace Rules
{
	static constexpr std::uint32_t ROUNDS = 3;
	static constexpr std::uint32_t DICE = 5;
	static constexpr std::uint32_t REROLLS = 3;

	static constexpr std::int32_t UNDEFINED = -1;
};

using GameDice = std::array<Die, Rules::DICE>;