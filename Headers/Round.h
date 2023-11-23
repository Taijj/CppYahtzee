#pragma once

#include <array>
#include <vector>
#include <sstream>
#include <exception>
#include "Utils.h"
#include "Renderer.h"

class Round
{
public:
	Round(GameDice& dice, Renderer& renderer) : _renderer(renderer), _dice(dice)
	{}

	~Round() = default;

	bool Execute()
	{		
		for (Die d : _dice)
			d.Unlock();			
		
		bool isCanceled;
		isCanceled = ExecuteRollingPhase();
		isCanceled = ExecuteScoringPhase();
		return false;
	}

private:	
	Renderer& _renderer;
	GameDice& _dice;


	

	bool ExecuteRollingPhase()
	{
		for (std::uint32_t i = 0; i < Rules::REROLLS; ++i)
		{
			Roll();
			
			_renderer.Render();
			continue;

			std::string input = Input::Get("r - reroll; l### - lock; c - count; x - exit");
			char command = input[0];

			switch (command)
			{
				case Input::LOCK: LockDice(input); break;
				case Input::COUNT: i = Rules::REROLLS; break;
				case Input::EXIT: return true;
				case Input::REROLL: break;

				default: throw std::invalid_argument("Unknown Command detected!");
			}
		}

		return false;
	}		
	
	void Roll()
	{
		for(Die& d : _dice)
		{
			if (!d.IsLocked())
				d.Roll();
		}
		_renderer.UpdateDice();
	}	

	void LockDice(std::string &input)
	{
		Utils::Log("TODO: Locking!");
	}


	bool ExecuteScoringPhase()
	{
		Utils::Log("TODO: Scoring!");
		return false;
	}
};