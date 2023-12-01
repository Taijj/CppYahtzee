#pragma once
#include <cstdint>

namespace Rules
{
	static constexpr std::uint32_t MAX_PLAYER_COUNT = 4;

	static constexpr std::uint32_t DIE_COUNT = 5;
	static constexpr std::uint32_t DIE_SIDES = 6;

	static constexpr std::uint32_t ROUND_COUNT = 13;
	static constexpr std::uint32_t REROLL_COUNT = 3;

	static constexpr std::uint32_t BONUS_THRESHOLD = 63;
	static constexpr std::uint32_t BONUS_SCORE = 35;

	static constexpr std::int32_t UNDEFINED = -1;		
};