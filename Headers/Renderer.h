#pragma once
#include <string>
#include <format>
#include <iostream>
#include <vector>
#include <map>

#include "Utils.h"
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



	void UpdateRound(std::uint32_t value)
	{			
		_roundText = std::format("========= Round {} =========", value);
	}

	void UpdateDice(const std::uint32_t rerollsLeft)
	{		
		_rerollsLeft = rerollsLeft;

		_diceHand.clear();
		_diceLocked.clear();

		_diceHand.push_back("Hand:");
		_diceLocked.push_back("Locked:");

		for (Die d : _dice)
		{
			std::string entry = std::format("#{}: {}", d.GetId(), d.GetValue());
			if (d.Is(Die::Locked) || d.Is(Die::Selected))
				_diceLocked.push_back(entry);
			else
				_diceHand.push_back(entry);
		}
	}	



	void RenderHead() const
	{
		std::cout << CLEAR;

		std::cout << _roundText << std::endl;
		std::cout << std::endl;

		std::cout << ROLL_HEADLINE << std::endl;
		std::cout << std::endl;
		for (std::uint32_t i = 0; i < COLUMN_LENGTH; ++i)
		{
			const std::string hand = i < _diceHand.size() ? _diceHand[i] : "";
			const std::string lock = i < _diceLocked.size() ? _diceLocked[i] : "";
			std::cout << INDENT << hand << "\t  " << lock << std::endl;
		}
		std::cout << std::endl;
	}

	void RenderRoundInputs() const
	{
		std::cout << "# Use the following commands to play:" << std::endl;
		std::cout << INDENT << Input::THROW.character << " - " << Input::THROW.description << "\t\t";
		std::cout << INDENT << Input::LOCK.character << " - " << Input::LOCK.description << std::endl;
		std::cout << INDENT << Input::EXIT.character << " - " << Input::EXIT.description << "\t\t";
		std::cout << INDENT << Input::SCORE.character << " - " << Input::SCORE.description << std::endl;

		std::cout << std::endl;
		std::cout << "Rerolls left: " << _rerollsLeft << std::endl;
		std::cout << Input::YOUR_INPUT;
	}

	void RenderLockInputs() const
	{
		std::cout << std::endl;
		for (auto s : Input::LOCK_TUTORIAL)
			std::cout << s << std::endl;

		std::cout << Input::THROW.character << " - " << Input::THROW.description << "\t";		
		std::cout << Input::EXIT.character << " - " << Input::EXIT.description << "\t";
		std::cout << Input::SCORE.character << " - " << Input::SCORE.description << std::endl;

		std::cout << std::endl;
		std::cout << Input::YOUR_INPUT;
	}



private:
	inline static const char* INDENT = "  ";
	inline static const char* CLEAR = "\033[2J\033[1;1H";	
	inline static const char* ROLL_HEADLINE = "Player threw the dice...";
	inline static constexpr std::uint32_t COLUMN_LENGTH = Rules::DICE + 1; // All Dice + a Headline

	const GameDice& _dice;
	DieColumn _diceHand;
	DieColumn _diceLocked;

	std::string _roundText;
	std::uint32_t _rerollsLeft;
		

	/*std::cout << std::endl;
	for (auto s : Input::SCORE_TUTORIAL)
		std::cout << s << std::endl;*/
};