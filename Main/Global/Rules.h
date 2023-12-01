#pragma once
#include <cstdint>

/// <summary>
/// Central place for global constant definition.
/// </summary>
namespace Rules
{
	constexpr std::uint32_t MAX_PLAYER_COUNT = 4;

	constexpr std::uint32_t DIE_COUNT = 5;
	constexpr std::uint32_t DIE_SIDES = 6;

	constexpr std::uint32_t ROUND_COUNT = 13;
	constexpr std::uint32_t REROLL_COUNT = 3;

	constexpr std::uint32_t BONUS_THRESHOLD = 63;
	constexpr std::uint32_t BONUS_SCORE = 35;

	constexpr std::int32_t UNDEFINED = -1;
};