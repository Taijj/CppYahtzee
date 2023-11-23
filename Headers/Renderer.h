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
		_diceLocked(DieColumn(COLUMN_LENGTH))
	{}

	void Render() const
	{
		std::cout << CLEAR;
		RenderRound();
		RenderDice();
		RenderInput();
	}
		
	~Renderer() = default;



	void UpdateRound(std::uint32_t value)
	{			
		_roundText = std::format("========= Round {} =========", value);
	}

	void UpdateDice()
	{		
		_diceHand.clear();
		_diceLocked.clear();

		_diceHand.push_back("Hand___");
		_diceLocked.push_back("Locked___");

		for (Die d : _dice)
		{
			std::string entry = std::format("#{}: {}", d.GetId(), d.GetValue());
			if (d.IsLocked())
				_diceLocked.push_back(entry);
			else
				_diceHand.push_back(entry);
		}
	}	


private:
	inline static const char* CLEAR = "\033[2J\033[1;1H";	
	inline static const char* ROLL_HEADLINE = "Player threw the dice...";
	inline static constexpr std::uint32_t COLUMN_LENGTH = Rules::DICE + 1; // All Dice + a Headline

	std::string _roundText;

	const GameDice& _dice;
	DieColumn _diceHand;
	DieColumn _diceLocked;



	void RenderRound() const
	{
		std::cout << _roundText << std::endl;
		std::cout << std::endl;
	}

	void RenderDice() const
	{
		std::cout << ROLL_HEADLINE << std::endl;
		std::cout << std::endl;
		for (std::uint32_t i = 0; i < COLUMN_LENGTH; ++i)
		{
			const std::string hand = i < _diceHand.size() ? _diceHand[i] : "";
			const std::string lock = i < _diceLocked.size() ? _diceLocked[i] : "";
			std::cout << hand << '\t' << lock << std::endl;
		}
		std::cout << std::endl;
	}

	void RenderInput() const
	{
		std::cout << "# Use the following commands to play:" << std::endl;
		std::cout << Input::ROLL.character << " - " << Input::ROLL.description << "\t\t";
		std::cout << Input::LOCK.character << " - " << Input::LOCK.description << std::endl;
		std::cout << Input::EXIT.character << " - " << Input::EXIT.description << "\t\t";
		std::cout << Input::SCORE.character << " - " << Input::SCORE.description << std::endl;		
		
		std::cout << std::endl;
		for(auto s : Input::LOCK_TUTORIAL)
			std::cout << s << std::endl;

		std::cout << std::endl;
		for (auto s : Input::SCORE_TUTORIAL)
			std::cout << s << std::endl;
		
		std::cout << std::endl;
		std::cout << "# Your Input: ";
	}
};