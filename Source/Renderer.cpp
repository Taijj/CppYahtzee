#pragma once

#include "../Headers/Renderer.h"
#include <iomanip>



void Renderer::UpdateRound(std::uint32_t value, std::uint32_t playerId)
{
	_roundText = std::format("========= Round {} - Player {} =========", value+1, playerId);
}

void Renderer::UpdateRerollsLeft(std::uint32_t value)
{
	_rerollsText = std::format("RerollsLeft: {}", value);
}

void Renderer::UpdatePlayer(Player& player)
{		
	_playerTable[0][0] = "Hand:";
	for (std::size_t y = 1; y < TABLE_HEIGHT; ++y)
	{
		std::size_t dieIndex = y-1;
		std::string* entry = &_playerTable[y][0];

		if (dieIndex < Rules::DICE)
		{
			const Die& d = _dice[dieIndex];
			std::string valueText = d.GetValue() != 0
				? std::to_string(d.GetValue())
				: "--";

			*entry = d.Is(Die::State::Default)
				? std::format("#{} - {}", d.GetId(), valueText)
				: "";
		}
		else
		{
			*entry = "";
		}
	}

	_playerTable[0][1] = "Locked:";
	for (std::size_t y = 1; y < TABLE_HEIGHT; ++y)
	{
		std::size_t dieIndex = y - 1;
		std::string* entry = &_playerTable[y][1];

		if (dieIndex < Rules::DICE)
		{
			const Die& d = _dice[dieIndex];
			std::string valueText = d.GetValue() != 0
				? std::to_string(d.GetValue())
				: "--";

			*entry = d.Is(Die::State::Locked) || d.Is(Die::State::Selected)
				? std::format("#{} - {}", d.GetId(), valueText)
				: "";
		}
		else
		{
			*entry = "";
		}
	}

	_playerTable[0][2] = "Combos:";
	for (std::size_t y = 1; y < TABLE_HEIGHT-1; ++y) // Only the first 6
	{
		std::size_t comboIndex = y - 1;
		std::string* entry = &_playerTable[y][2];
	
		const Combo& c = *COMBOS[comboIndex];
		std::string score = player.HasScore(c.Kind())
			? std::to_string(player.GetScore(c.Kind()))
			: "--";
		
		_playerTable[y][2] = std::format("{}: {}", c.Name(), score);
	}

	std::string bonus = player.HasReachedBonus() ? std::format("(+{}", Rules::BONUS_SCORE) : "";
	_playerTable[0][3] = std::format("Score: {} {}", player.GetTotal(), bonus);
	for (std::size_t y = 1; y < TABLE_HEIGHT; ++y)
	{
		std::size_t comboIndex = y + 5; // after the first 6
		std::string* entry = &_playerTable[y][3];

		const Combo& c = *COMBOS[comboIndex];
		std::string score = player.HasScore(c.Kind())
			? std::to_string(player.GetScore(c.Kind()))
			: "--";

		_playerTable[y][3] = std::format("{}: {}", c.Name(), score);
	}
}




void Renderer::RenderPlayers() const
{
	std::cout << "== Welcome to Yahtzee! ==" << std::endl;
	std::cout << std::endl;
	std::cout << "How many players will play? Enter a number from 1 to 6." << std::endl;
	std::cout << std::endl;
	std::cout << YOUR_INPUT;
}

void Renderer::RenderRound() const
{
	std::cout << CLEAR;

	std::cout << _roundText << std::endl;
	std::cout << std::endl;
}

void Renderer::RenderTable() const
{
	for (std::size_t y = 0; y < TABLE_HEIGHT; ++y)
	{
		std::cout << INDENT;
		for (std::size_t x = 0; x < TABLE_WIDTH; ++x)
		{
			std::cout << std::setw(ENTRY_WIDTH)
				<< std::left				
				<< _playerTable[y][x];
		}

		if(y == 0)
			std::cout << std::endl;
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Renderer::RenderFirstThrow() const
{	
	std::cout << "# Start your round or exit the game, by typing in the following commands:" << std::endl;
	std::cout << INDENT << Input::THROW.character << " - " << Input::THROW.description << std::endl;
	std::cout << INDENT << Input::EXIT.character << " - " << Input::EXIT.description << std::endl;

	std::cout << std::endl;
	std::cout << YOUR_INPUT;
}



void Renderer::RenderRoundInputs() const
{
	std::cout << "# Use the following commands to play:" << std::endl;
	std::cout << INDENT << Input::THROW.character << " - " << Input::THROW.description << "\t\t\t";
	std::cout << INDENT << Input::LOCK.character << " - " << Input::LOCK.description << std::endl;
	std::cout << INDENT << Input::EXIT.character << " - " << Input::EXIT.description << "\t\t";
	std::cout << INDENT << Input::SCORE.character << " - " << Input::SCORE.description << std::endl;

	std::cout << std::endl;
	std::cout << _rerollsText << std::endl;
	std::cout << YOUR_INPUT;
}

void Renderer::RenderLockInputs() const
{	
	for (auto s : Input::LOCK_TUTORIAL)
		std::cout << s << std::endl;

	std::cout << Input::THROW.character << " - " << Input::THROW.description << "\t";
	std::cout << Input::EXIT.character << " - " << Input::EXIT.description << "\t";
	std::cout << Input::SCORE.character << " - " << Input::SCORE.description << std::endl;

	std::cout << std::endl;
	std::cout << _rerollsText << std::endl;
	std::cout << YOUR_INPUT;
}

void Renderer::RenderScoreInputs() const
{	
	for (auto s : Input::SCORE_TUTORIAL)
		std::cout << s << std::endl;
		
	std::cout << std::endl << Input::EXIT.character << " - " << Input::EXIT.description << std::endl;
	std::cout << std::endl;
	std::cout << YOUR_INPUT;
}

void Renderer::RenderExitConfirmation() const
{
	std::cout << CLEAR;

	std::cout << "\n\n";
	std::cout << "Really Exit? (y/n)" << std::endl;
	std::cout << std::endl;
	std::cout << YOUR_INPUT;
}

void Renderer::RenderInvalid()
{
	std::cout << CLEAR_LINE;
	std::cout << INVALID_INPUT;
}

void Renderer::RenderAlreadyScored()
{
	std::cout << CLEAR_LINE;
	std::cout << INVALID_INPUT;
}