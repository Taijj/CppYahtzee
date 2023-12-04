#include "Turn.h"

#include "../Model/Model.h"
#include "../Global/Rules.h"


void Turn::Start(std::uint32_t playerId)
{	
	_rerollsLeft = Rules::REROLL_COUNT;
	for (const auto& d : Model::GetDice())
		d->Reset();
	_state = Turn::Initial;
}

void Turn::Run()
{
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


void Turn::RunInitial()
{
	//_renderer.UpdatePlayer(*_player);

	//_renderer.RenderRound();
	//_renderer.RenderTable();
	//_renderer.RenderFirstThrow();

	//Execute(Input::GetInitial());	
}

void Turn::RunPlaying()
{
	//_renderer.RenderRound();
	//_renderer.RenderTable();
	//_renderer.RenderRoundInputs();

	//Execute(Input::GetPlaying());
}

void Turn::RunLocking()
{
	//_renderer.RenderRound();
	//_renderer.RenderTable();
	//_renderer.RenderLockInputs();

	//std::string sub = "";
	//const Command* com = Input::GetLocking(sub);
	//if (com != nullptr)
	//{
		//Execute(*com);
		//return;
	//}

	//for (const char c : sub)
	//{
	//	std::uint32_t id = c - '0'; // Char to digit conversion
	//	Die& d = *std::find_if(_dice.begin(), _dice.end(), [&](const Die& d) { return d.GetId() == id; });

	//	if (d.Is(Die::Locked))
	//	{
	//		// TODO
	//		// Utils::Log("Cannot modify Die #" + std::to_string(d.GetId()) + "! It is locked for this turn.");
	//		continue;
	//	}

	//	d.Set(d.Is(Die::Selected) ? Die::Default : Die::Selected);
	//}

	//_renderer.UpdatePlayer(*_player);
}

void Turn::RunScoring()
{	
	//_renderer.RenderRound();
	//_renderer.RenderTable();
	//_renderer.RenderScoreInputs();
	//	
	//Score::Kind kind;
	//const Command* com = Input::GetScoring(kind, *_player);
	//if (com != nullptr)
	//{
	//	Execute(*com);
	//	return;
	//}

	//if (_player->HasScore(kind))
	//{
	//	// TODO
	//	// Utils::Log("Cannot score as {kind} since you already scored there.");
	//	return;
	//}
	//
	//for (const Combo* c : COMBOS)
	//{
	//	if (c->Kind() == kind)
	//	{
	//		std::uint32_t score = c->Score(_dice);
	//		_player->SetScore(kind, score);
	//		break;
	//	}
	//}

	//_state = Turn::Completed;
	//_renderer.UpdatePlayer(*_player);
	//_renderer.RenderRound();
	//_renderer.RenderTable();
	//
	//if(false == Input::isAutomatic)
	//	Input::WaitForAnyKey();
}



//void Turn::Execute(const Command command)
//{
//	if (command == Input::THROW)
//	{
//		RollDice();
//	}
//	else if (command == Input::EXIT)
//	{
//		ExitGame();
//	}
//	else if (command == Input::LOCK)
//	{
//		_state = Turn::Locking;
//	}
//	else if (command == Input::SCORE)
//	{
//		_state = Turn::Scoring;
//	}
//}

void Turn::ThrowDice()
{
	for (const auto& d : Model::GetDice())	
	{
		if (d->IsIn(Die::ToBeLocked))
			d->Set(Die::Locked);

		if (!d->IsIn(Die::Locked))
			d->Throw();
	}
	
	--_rerollsLeft;
	_state = _rerollsLeft > 0 ? Turn::Playing : Turn::Scoring;

	//_renderer.UpdateRerollsLeft(_rerollsLeft);
	//_renderer.UpdatePlayer(*_player);
}

void Turn::ExitGame()
{
	/*_renderer.RenderExitConfirmation();
	if (Input::IsExitConfirmed())
		_state = Turn::Canceled;*/
}