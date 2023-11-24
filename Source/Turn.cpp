#pragma once

#include "../Headers/Turn.h"



void Turn::Execute()
{
	for (Die d : _dice)
		d.Set(Die::Default);

	while (_rerollCount == 0)
	{
		_renderer.RenderHead();
		_renderer.RenderFirstThrow();

		const Command com = Input::GetDefault();
	}

	_rerollCount = 0;
	while (IsCompleted() == false)
	{
		_renderer.RenderHead();
		_renderer.RenderRoundInputs();
		Evaluate(Input::GetDefault());

		Utils::WaitFor(1.0f);
		if (_isExited)
			return;
	}
}

bool Turn::IsCompleted()
{
	return _rerollCount >= Rules::REROLLS
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
		// Rerolls happen automatically in Execute()
		Utils::Log("Throwing dice...");
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
		Score();
	}
}

void Turn::Roll()
{
	++_rerollCount;
	for (Die& d : _dice)
	{
		if (!d.Is(Die::Locked))
			d.Roll();
	}
	_renderer.UpdateDice(Rules::REROLLS - _rerollCount);
}

void Turn::ExitGame()
{
	// TODO: Really Exit? y/n
	Utils::Log("Exiting...");
	_isExited = true;
}



void Turn::LockDice()
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
	_renderer.RenderHead();
	_rerollCount = Rules::REROLLS;

	Utils::Log("TODO//");
	Utils::Log("Ending turn...");
}