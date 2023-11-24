#pragma once
#include <string>
#include <format>
#include <iostream>
#include <vector>
#include <map>

#include "Config.h"
#include "Input.h"

using DieColumn = std::vector<std::string>;

class Renderer
{


public:
	Renderer(GameDice& dice) :
		_dice{dice},
		_diceHand(DieColumn(COLUMN_LENGTH)),
		_diceLocked(DieColumn(COLUMN_LENGTH)),
		_roundText(""),
		_rerollsLeft(0)
	{}	
		
	~Renderer() = default;



	void UpdateRound(std::uint32_t value);
	void UpdateDice(const std::uint32_t rerollsLeft);



	void RenderHead() const;
	void RenderDice() const;
	void RenderFirstThrow() const;

	void RenderRoundInputs() const;
	void RenderLockInputs() const;
	static void RenderInvalid();



private:

	inline static const char* INDENT = "  ";
	inline static const std::string YOUR_INPUT = "# Your Input: ";
	inline static const std::string INVALID_INPUT = "# INVALID INPUT! Please try again: ";
	inline static const char* CLEAR = "\033[2J\033[1;1H";	
	inline static const std::string CLEAR_LINE = "\x1B[1A\x1B[2K";
	inline static const char* ROLL_HEADLINE = "Player threw the dice...";
	inline static constexpr std::uint32_t COLUMN_LENGTH = Rules::DICE + 1; // All Dice + a Headline

	const GameDice& _dice;
	DieColumn _diceHand;
	DieColumn _diceLocked;

	std::string _roundText;
	std::uint32_t _rerollsLeft;
};