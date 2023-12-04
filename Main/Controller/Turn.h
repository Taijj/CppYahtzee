#pragma once

#include <cstdint>

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



	Turn() : _rerollsLeft(0), _state(None)
	{}

	~Turn() = default;


	void Start(std::uint32_t playerId);
	void Run();

	bool IsRunning();
	bool WasCanceled();



private:		
	std::uint32_t _rerollsLeft;
	State _state;
	
	void RunInitial();
	void RunPlaying();
	void RunLocking();
	void RunScoring();

	//void Execute(const Command command);
	void ThrowDice();
	void ExitGame();
};