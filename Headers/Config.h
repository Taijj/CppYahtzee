#pragma once
#include <cstdint>
#include <array>

#include "Die.h"

namespace Score
{
	enum Kind
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
}

namespace Rules
{
	static constexpr std::uint32_t MAX_PLAYERS = 6;
	static constexpr std::uint32_t DIE_SIDES = 6;
	static constexpr std::uint32_t ROUNDS = 13;
	static constexpr std::uint32_t DICE = 5;
	static constexpr std::uint32_t REROLLS = 3;

	static constexpr std::uint32_t BONUS_THRESHOLD = 63;
	static constexpr std::uint32_t BONUS_SCORE = 35;

	static constexpr std::int32_t UNDEFINED = -1;
};

using GameDice = std::array<Die, Rules::DICE>;