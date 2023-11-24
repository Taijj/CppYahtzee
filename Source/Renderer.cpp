#pragma once

#include "../Headers/Renderer.h"



void Renderer::UpdateRound(std::uint32_t value)
{
	_roundText = std::format("========= Round {} =========", value);
}

void Renderer::UpdateDice(const std::uint32_t rerollsLeft)
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



void Renderer::RenderHead() const
{
	std::cout << CLEAR;

	std::cout << _roundText << std::endl;
	std::cout << std::endl;
}

void Renderer::RenderDice() const
{
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

void Renderer::RenderFirstThrow() const
{
	std::cout << "# Use the following command to start your turn:" << std::endl;
	std::cout << INDENT << Input::THROW.character << " - " << Input::THROW.description << std::endl;

	std::cout << YOUR_INPUT;
}



void Renderer::RenderRoundInputs() const
{
	std::cout << "# Use the following commands to play:" << std::endl;
	std::cout << INDENT << Input::THROW.character << " - " << Input::THROW.description << "\t\t";
	std::cout << INDENT << Input::LOCK.character << " - " << Input::LOCK.description << std::endl;
	std::cout << INDENT << Input::EXIT.character << " - " << Input::EXIT.description << "\t\t";
	std::cout << INDENT << Input::SCORE.character << " - " << Input::SCORE.description << std::endl;

	std::cout << std::endl;
	std::cout << "Rerolls left: " << _rerollsLeft << std::endl;
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

void Renderer::RenderInvalid()
{
	std::cout << CLEAR_LINE;
	std::cout << INVALID_INPUT;
}