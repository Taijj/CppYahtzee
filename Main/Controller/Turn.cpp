#include "Turn.h"

#include <vector>

#include "../Model/Model.h"
#include "../View/View.h"



#pragma region Main
void Turn::Start(std::uint32_t round, std::uint32_t playerId)
{	
	for (const auto& d : Model::GetDice())
		d->Reset();
	
	_currentRound = round;
	_currentPlayerId = playerId;
	_rerollsLeft = Rules::REROLL_COUNT;
	_state = Turn::Initial;
}

void Turn::Run()
{	
	View::Clear();
	switch (_state)
	{
		case Turn::Initial: RunInitial(); break;
		case Turn::Playing: RunPlaying(); break;
		case Turn::Locking: RunLocking(); break;
		case Turn::Scoring: RunScoring(); break;
	}
}

bool Turn::IsRunning() { return _state != Completed && _state != Canceled; }
bool Turn::WasCanceled() { return _state == Canceled; }
#pragma endregion



#pragma region Phases
void Turn::RunInitial()
{
	View::RenderRoundHeader(_currentRound, _currentPlayerId);
	View::RenderInitialPhase();

	Input::WaitForAnyKey();	
	ThrowDice();
}

void Turn::RunPlaying()
{
	View::RenderRoundHeader(_currentRound, _currentPlayerId);
	RenderTable();
	RenderCommands({Input::THROW, Input::LOCK, Input::EXIT, Input::SCORE});

	const Command* com = nullptr;
	while (com == nullptr)
	{
		com = Input::ForGame();
		if (com == nullptr)
			View::RenderInvalidInput();
	}

	Execute(*com);
}

void Turn::RunLocking()
{
	//_renderer.RenderRound();
	//_renderer.RenderTable();
	//_renderer.RenderLockInputs();
		


	std::vector<std::uint32_t> ids;
	while(true) // until a valid input was made
	{	
		ids.clear();
		const Command* com = Input::ForLocking(ids);

		// Default game command was put in
		if (com != nullptr)
		{
			Execute(*com);
			break;
		}
		
		// 1 or more dice were selected
		if (ids.size() > 0)
			break;

		// TODO: Invalid
	}	
	


	for (const std::uint32_t id : ids)
	{
		const auto& d = Model::GetDice().at(id - 1);

		if (d->IsIn(Die::Locked))
		{
			// TODO: Warning
			continue;
		}

		Die::State state = d->IsIn(Die::Thrown) ? Die::ToBeLocked : Die::Thrown;
		d->Set(state);
	}

	//_renderer.UpdatePlayer(*_player);
}

void Turn::RunScoring()
{	
	//_renderer.RenderRound();
	//_renderer.RenderTable();
	//_renderer.RenderScoreInputs();

	const auto& player = Model::GetPlayers().at(_currentPlayerId);
		
	Score::Kind kind;
	while (true) // Until a valid input was made
	{
		const Command* com = Input::ForScoring(kind);
		
		// Default game command was put in
		if (com != nullptr)
		{
			Execute(*com);
			break;
		}
		
		// A kind was selected that the player did not score, yet
		if (kind != Score::Undefined)
		{
			std::int32_t _;
			if (!player->TryGetScore(kind, _))
				break;

			// TODO: Warnings
		}

		// TODO: Invalid
	}
		


	for(const auto& c : Model::COMBOS)
	{
		if (c->Kind() != kind)
			continue;
		
		player->SetScore(kind, c->Score(_currentRoll));		
		break;
	}

	_state = Turn::Completed;
	//_renderer.UpdatePlayer(*_player);
	//_renderer.RenderRound();
	//_renderer.RenderTable();
	
	if(false == Input::isAutomatic)
		Input::WaitForAnyKey();
}
#pragma endregion



#pragma region Rendering
void Turn::RenderTable() const
{
	std::vector<View::DieData> dice;
	for (const auto& d : Model::GetDice())
		dice.push_back({ d->Id(), d->Face() });

	std::vector<View::ComboData> combos;
	for (const auto& c : Model::COMBOS)
	{
		const auto& player = Model::GetPlayers().at(_currentPlayerId);
		std::int32_t score;
		player->TryGetScore(c->Kind(), score);

		combos.push_back({ c->Name(), score });
	}

	View::RenderTable(dice, combos);	
}

void Turn::RenderCommands(const std::vector<Command> availableCommands) const
{
	std::vector<View::CommandData> commands;
	for (const Command& c : availableCommands)
		commands.push_back({ c.character, c.description });

	View::RenderCommands(commands);
}
#pragma endregion



#pragma region Helpers
void Turn::Execute(const Command& command)
{
	if (command == Input::THROW)
	{
		ThrowDice();
	}
	else if (command == Input::EXIT)
	{
		ExitGame();
	}
	else if (command == Input::LOCK)
	{
		_state = Turn::Locking;
	}
	else if (command == Input::SCORE)
	{
		_state = Turn::Scoring;
	}
}

void Turn::ThrowDice()
{
	for (const auto& d : Model::GetDice())	
	{
		if (d->IsIn(Die::ToBeLocked))
			d->Set(Die::Locked);

		if (!d->IsIn(Die::Locked))
			d->Throw();

		std::uint32_t index = d->Id();
		_currentRoll[index] = d->Face();
	}
	
	--_rerollsLeft;
	_state = _rerollsLeft > 0 ? Turn::Playing : Turn::Scoring;

	//_renderer.UpdateRerollsLeft(_rerollsLeft);
	//_renderer.UpdatePlayer(*_player);
}

void Turn::ExitGame()
{
	//_renderer.RenderExitConfirmation();	

	const Command* com = nullptr;
	while (com == nullptr)
	{
		com = Input::ForConfirmation();
	}
	
	if(*com == Input::YES)
		_state = Turn::Canceled;
}
#pragma endregion