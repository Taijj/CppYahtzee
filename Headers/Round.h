#pragma once

#include <array>
#include <vector>
#include <sstream>
#include <exception>
#include "Utils.h"
#include "Renderer.h"
#include "Input.h"

class Round
{
public:
	Round(GameDice& dice, Renderer& renderer) : _renderer(renderer), _dice(dice), _isRunning(true)
	{}

	~Round() = default;

	void Execute()
	{		
		for (Die d : _dice)
			d.Unlock();			

		while (true)
		{
			Roll();
			_renderer.Render();

			Evaluate(Input::Get());
			
			Utils::WaitFor(1.0f);
			if (!_isRunning)
				break;
		}
	}

	bool IsRunning()
	{
		return _isRunning;
	}

private:	
	Renderer& _renderer;
	GameDice& _dice;
	bool _isRunning;
	
	void Evaluate(const Command command)
	{
		if (command == Input::EXIT)
			ExitGame();
		if (command == Input::ROLL)
			Roll();
		if (command == Input::LOCK)
			LockDice(command.subData);
		if (command == Input::SCORE)
			Score(command.subData);
	}	

	void Roll()
	{
		Utils::Log("Rolling dice...");

		for(Die& d : _dice)
		{
			if (!d.IsLocked())
				d.Roll();
		}
		_renderer.UpdateDice();
	}	

	void LockDice(const std::string &input)
	{
		Utils::Log("TODO//");
		Utils::Log("Separating Dice...");
	}

	void Score(const std::string &input)
	{
		Utils::Log("TODO//");
		Utils::Log("Ending turn...");
	}

	void ExitGame()
	{
		Utils::Log("Exiting...");
		_isRunning = false;
	}
};