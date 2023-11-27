#include "../Headers/Turn.h"



void Turn::Execute(Player &player)
{
	_player = &player;
	_rerollsLeft = Rules::REROLLS;
	for (Die d : _dice)
		d.Set(Die::Default);

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
		_renderer.RenderTable();
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
	return _rerollsLeft <= 0
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
		_rerollsLeft = 0;
	}
}

void Turn::Roll()
{
	for (Die& d : _dice)
	{
		if (!d.Is(Die::Locked))
			d.Roll();
	}
	--_rerollsLeft;
	_renderer.UpdateRerollsLeft(_rerollsLeft);
	_renderer.UpdatePlayer(*_player);
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
		_renderer.RenderTable();
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

		_renderer.UpdatePlayer(*_player);
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
	_renderer.UpdatePlayer(*_player);
	_renderer.RenderRound();
	_renderer.RenderTable();
		
	//for (Combo* c : COMBOS)
		//_player->Score(c->Kind(), c->Score(_dice));

	Utils::Log("TODO//");
	Utils::Log("Ending turn...");
	Utils::WaitFor(2.0f);
}