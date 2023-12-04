#pragma once

#include <cstdint>
#include <array>

#include "../Global/Rules.h"
#include "Input.h"

class Turn
{

public:
	enum State
	{
		None = 0,

		Initial,
		Playing,
		Locking,
		Scoring,
		Completed,

		Canceled
	};



	Turn() : _currentPlayerId(0), _currentRound(0),
		_rerollsLeft(0), _state(None), _currentRoll({})
	{}

	~Turn() = default;



	void Start(std::uint32_t round, std::uint32_t playerId);
	void Run();

	bool IsRunning();
	bool WasCanceled();



private:		
	std::uint32_t _currentPlayerId;
	std::uint32_t _currentRound;

	std::uint32_t _rerollsLeft;
	State _state;

	std::array<std::uint32_t, Rules::DIE_COUNT> _currentRoll;
	
	void RunInitial();
	void RunPlaying();
	void RunLocking();
	void RunScoring();

	void Execute(const Command& command);
	void ThrowDice();
	void ExitGame();
};