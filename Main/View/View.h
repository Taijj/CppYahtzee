#pragma once

#include <cstdint>
#include <string>

class View
{
public:

	struct Die
	{
		std::uint32_t id;
		std::uint32_t value;
	};

	View() = delete;
	


	static void RenderWelcome();
	static void RenderRoundHeader(std::uint32_t roundIndex, std::uint32_t playerId);

	static void RenderInitialPhase();

	static void Clear();
	static void RenderInvalidInput();

private: 
	inline static const std::string INDENT = "  ";	
	
	inline static const std::string CLEAR_ALL = "\x1B[2J\x1B[1;1H";
	inline static const std::string CLEAR_LINE = "\x1B[1A\x1B[2K";
	


	inline static const std::string YOUR_INPUT = "# Your Input: ";
	inline static const std::string INVALID_INPUT = "# INVALID INPUT! Please try again: ";
	inline static const std::string ALREADY_SCORED = "# You already scored this Combo! Try another: ";
};