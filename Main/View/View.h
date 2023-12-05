#pragma once

#include <cstdint>
#include <string>
#include <format>
#include <vector>
#include <memory>

#include "SpritesLoader.h"

class View
{
public:

	struct DieEntry
	{
		std::uint32_t id;
		std::uint32_t value;
		bool isLocked;

		std::string Out() { return std::format("#{} - {}", id, value); }
	};

	struct ComboEntry
	{
		std::string name;
		std::int32_t score;

		std::string Out()
		{ 
			std::string s = score >= 0
				? std::to_string(score)
				: EMPTY;
			return std::format("{} - {}", name, s);
		}
	};



	View() = delete;
	

	static void Wake();


	static void RenderWelcome();
	static void RenderInitialPhase();
	static void RenderRoundHeader(std::uint32_t roundIndex, std::uint32_t playerId);
	static void RenderTable(std::vector<DieEntry> dice, std::vector<ComboEntry> combos);

	static void Clear();
	static void RenderInvalidInput();

private: 
	inline static const std::string INDENT = "  ";	
	
	inline static const std::string CLEAR_ALL = "\x1B[2J\x1B[1;1H";
	inline static const std::string CLEAR_LINE = "\x1B[1A\x1B[2K";

	inline static constexpr std::uint32_t ENTRY_WIDTH = 15U;
	inline static const std::string EMPTY = "--";
	


	inline static const std::string YOUR_INPUT = "# Your Input: ";
	inline static const std::string INVALID_INPUT = "# INVALID INPUT! Please try again: ";
	inline static const std::string ALREADY_SCORED = "# You already scored this Combo! Try another: ";



	inline static std::unique_ptr<SpritesLoader> _sprites;
};