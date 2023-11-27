#pragma once

#include "../Headers/Renderer.h"
#include <iomanip>



void Renderer::UpdateRound(std::uint32_t value)
{
	_roundText = std::format("========= Round {} =========", value+1);
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
			*entry = d.Is(Die::State::Default)
				? std::format("#{} - {}", d.GetId(), d.GetValue())
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
			*entry = d.Is(Die::State::Locked) || d.Is(Die::State::Selected)
				? std::format("#{} - {}", d.GetId(), d.GetValue())
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

	// Combos column 2
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





void Renderer::RenderRound() const
{
	std::cout << CLEAR;

	std::cout << _roundText << std::endl;
	std::cout << std::endl;
}

void Renderer::RenderTable() const
{
	std::cout << ROLL_HEADLINE << std::endl;
	std::cout << std::endl;

	for (std::size_t y = 0; y < TABLE_HEIGHT; ++y)
	{
		std::cout << INDENT;
		for (std::size_t x = 0; x < TABLE_WIDTH; ++x)
		{
			std::cout << std::setw(ENTRY_WIDTH)
				<< std::left				
				<< _playerTable[y][x];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Renderer::RenderFirstThrow() const
{	
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
	std::cout << std::endl;
	for (auto s : Input::LOCK_TUTORIAL)
		std::cout << s << std::endl;

	std::cout << Input::THROW.character << " - " << Input::THROW.description << "\t";
	std::cout << Input::EXIT.character << " - " << Input::EXIT.description << "\t";
	std::cout << Input::SCORE.character << " - " << Input::SCORE.description << std::endl;

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