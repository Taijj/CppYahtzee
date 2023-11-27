#pragma once

#include "Utils.h"
#include "Config.h"
#include "Renderer.h"
#include "Player.h"
#include "Combos.h"



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



	Turn(GameDice& dice, Renderer& renderer)
		: _renderer(renderer), _dice(dice), _player(nullptr),
		_rerollsLeft(0), _state(None)
	{}

	~Turn() = default;


	void Start(Player& player);
	State Run();



private:	
	Renderer& _renderer;
	GameDice& _dice;
	Player* _player;

	std::uint32_t _rerollsLeft;
	State _state;
	
	void RunInitial();
	void RunPlaying();
	void RunLocking();
	void RunScoring();

	void Execute(const Command command);
	void RollDice();
	void ExitGame();
};