#pragma once

#include "../Headers/Turn.h"



void Turn::Execute()
{
	for (Die d : _dice)
		d.Set(Die::Default);
	_rerollCount = Rules::REROLLS;

	// First Throw
	while (true)
	{
		_renderer.RenderRound();
		_renderer.RenderFirstThrow();

		const Command com = Input::GetDefault();
		if (com == Input::THROW)
		{
			Roll();
			break;
		}

		if (com == Input::EXIT)
			ExitGame();

		if (_isExited)
			return;
	}

	// Main Loop
	while (IsCompleted() == false)
	{
		_renderer.RenderRound();
		_renderer.RenderRoundInputs();
		Evaluate(Input::GetDefault());
		
		if (_isExited)
			return;
	}	

	// Scoring
	Score();
}

bool Turn::IsCompleted()
{
	return _rerollCount <= 0
		|| std::all_of(_dice.begin(), _dice.end(), [](const Die& d) { return d.Is(Die::Locked); });
}

bool Turn::IsExited()
{
	return _isExited;
}




void Turn::Evaluate(const Command command)
{
	if (command == Input::THROW)
	{
		Roll();
	}
	else if (command == Input::EXIT)
	{
		ExitGame();
	}
	else if (command == Input::LOCK)
	{
		LockDice();
	}
	else if (command == Input::SCORE)
	{
		// Naturally progress to scoring
		_rerollCount = 0;
	}
}

void Turn::Roll()
{
	for (Die& d : _dice)
	{
		if (!d.Is(Die::Locked))
			d.Roll();
	}
	--_rerollCount;
	_renderer.UpdateDice(_rerollCount);
}

void Turn::ExitGame()
{
	_renderer.RenderExitConfirmation();
	if (false == Input::IsExitConfirmed())
		return;
	
	_isExited = true;
	Utils::Log("\nExiting...\n\n");
}



void Turn::LockDice()
{
	const Command* com;
	while (true)
	{
		_renderer.RenderRound();
		_renderer.RenderLockInputs();

		std::string subCommands = "";
		com = Input::GetLock(subCommands);
		if (com != nullptr)
			break;

		for (const char c : subCommands)
		{
			std::uint32_t id = c - '0'; // Char to digit conversion
			Die& d = *std::find_if(_dice.begin(), _dice.end(), [&](const Die& d) { return d.GetId() == id; });

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



void Turn::Score()
{
	_renderer.RenderRound();
	_rerollCount = Rules::REROLLS;

	Utils::Log("TODO//");
	Utils::Log("Ending turn...");
	Utils::WaitFor(2.0f);
}