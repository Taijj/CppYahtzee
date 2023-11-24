#pragma once

#include <array>
#include <vector>
#include <sstream>
#include <exception>
#include <algorithm>
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
			d.Set(Die::Default);

		_rerollCount = 0;
		while (IsCompleted() == false)
		{
			Roll();
			_renderer.RenderHead();
			
			_renderer.RenderRoundInputs();
			Evaluate(Input::GetRound());
			
			Utils::WaitFor(1.0f);
			if (_isExited)
				return;
		}
	}

	bool IsCompleted()
	{
		return _rerollCount >= Rules::REROLLS
			|| std::all_of(_dice.begin(), _dice.end(), [](const Die& d) { return d.Is(Die::Locked); });
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
			if (!d.Is(Die::Locked))
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
		const Command* com;
		while (true)
		{
			_renderer.RenderHead();
			_renderer.RenderLockInputs();
						
			std::string subCommands = "";
			com = Input::GetLock(subCommands);
			if (com != nullptr)				
				break;

			for (const char c : subCommands)
			{				
				std::uint32_t id = c - '0'; // Char to digit conversion
				Die &d = *std::find_if(_dice.begin(), _dice.end(), [&](const Die &d) { return d.GetId() == id; });

				if (d.Is(Die::Locked))
				{
					Utils::Log("Cannot modify Die #" + std::to_string(d.GetId()) + "! It is locked for this turn.");
					continue;
				}

				d.Set(d.Is(Die::Selected) ? Die::Default : Die::Selected);
			}

			_renderer.UpdateDice(_rerollCount - Rules::REROLLS);
		}		

		for (Die& d : _dice)
		{
			if (d.Is(Die::Selected))
				d.Set(Die::Locked);
		}
		Evaluate(*com);
	}

	void Score()
	{
		_renderer.RenderHead();
		_rerollCount = Rules::REROLLS;

		Utils::Log("TODO//");
		Utils::Log("Ending turn...");
	}	
};