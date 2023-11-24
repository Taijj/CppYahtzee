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
	Round(GameDice& dice, Renderer& renderer)
		: _renderer(renderer), _dice(dice), _rerollCount(0), _isExited(false)
	{}

	~Round() = default;



	void Execute()
	{		
		for (Die d : _dice)
			d.Unlock();			

		_rerollCount = 0;
		while (IsCompleted() == false)
		{
			Roll();
			_renderer.Render();

			Evaluate(Input::GetRound());
			
			Utils::WaitFor(1.0f);
			if (_isExited)
				return;
		}
	}

	bool IsCompleted()
	{
		return _rerollCount >= Rules::REROLLS
			|| std::all_of(_dice.begin(), _dice.end(), [](const Die& d) { return d.IsLocked(); });
	}

	bool IsExited()
	{
		return _isExited;
	}



private:	
	Renderer& _renderer;
	GameDice& _dice;

	std::uint32_t _rerollCount;
	bool _isExited;
	


	void Evaluate(const Command command)
	{
		if (command == Input::THROW)
		{
			// Rerolls happen automatically in Execute()
			Utils::Log("Throwing dice...");
		}
		else if(command == Input::EXIT)
		{
			ExitGame();			
		}
		else if (command == Input::LOCK)
		{
			LockDice();
		}
		else if (command == Input::SCORE)
		{
			Score();
		}
	}	

	void Roll()
	{
		++_rerollCount;
		for(Die& d : _dice)
		{
			if (!d.IsLocked())
				d.Roll();
		}
		_renderer.UpdateDice(Rules::REROLLS - _rerollCount);
	}		

	void ExitGame()
	{
		Utils::Log("Exiting...");
		_isExited = true;
	}



	void LockDice()
	{		
		Utils::Log("TODO//");
		Utils::Log("Locking...");
	}

	void Score()
	{
		Utils::Log("TODO//");
		Utils::Log("Ending turn...");
	}	
};