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

			const Command com = Input::Get();
			Utils::Log("Command identified: " + std::string(1, com.character) + " - " + com.description);
			Utils::Log("SubData: " + com.subData);
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