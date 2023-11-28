#pragma once
#include <string>
#include <format>
#include <iostream>
#include <array>
#include <map>

#include "Config.h"
#include "Input.h"
#include "Player.h"
#include "Combos.h"



constexpr std::size_t TABLE_WIDTH = 4; // 2 Columns for Dice, 2 Columns for scored combos
constexpr std::size_t TABLE_HEIGHT = 8; // The 13 combos divided by 2, ceild + a row for headlines
using Table = std::array<std::array<std::string, TABLE_WIDTH>, TABLE_HEIGHT>;

class Renderer
{

public:
	Renderer(GameDice& dice) :
		_dice{dice},
		_playerTable(Table{}),
		_roundText(""),
		_rerollsText("")
	{}	
		
	~Renderer() = default;



	void UpdateRound(std::uint32_t value, std::uint32_t playerId);
	void UpdateRerollsLeft(std::uint32_t value);
	void UpdatePlayer(Player& value);



	void RenderRound() const;
	void RenderTable() const;
	void RenderFirstThrow() const;

	void RenderRoundInputs() const;
	void RenderLockInputs() const;
	void RenderScoreInputs() const;
	void RenderExitConfirmation() const;
	
	static void RenderInvalid();
	static void RenderAlreadyScored();



private:

	inline static const char* INDENT = "  ";
	inline static const std::string YOUR_INPUT = "# Your Input: ";
	inline static const std::string INVALID_INPUT = "# INVALID INPUT! Please try again: ";
	inline static const std::string ALREADY_SCORED = "# You already scored this Combo! Try another: ";
	inline static const char* CLEAR = "\033[2J\033[1;1H";	
	inline static const std::string CLEAR_LINE = "\x1B[1A\x1B[2K";
	inline static const char* ROLL_HEADLINE = "Player threw the dice...";
		
	inline static constexpr std::uint32_t ENTRY_WIDTH = 15U;
	
	

	const GameDice& _dice;
	Table _playerTable;

	std::string _roundText;
	std::string _rerollsText;
};