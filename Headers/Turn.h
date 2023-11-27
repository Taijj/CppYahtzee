#pragma once

#include "Utils.h"
#include "Config.h"
#include "Renderer.h"
#include "Player.h"
#include "Combos.h"



class Turn
{

public:
	Turn(GameDice& dice, Renderer& renderer)
		: _renderer(renderer), _dice(dice), _player(nullptr),
		_rerollsLeft(0), _isExited(false)
	{}

	~Turn() = default;



	void Execute(Player &player);
	bool IsCompleted();
	bool IsExited();



private:	
	Renderer& _renderer;
	GameDice& _dice;
	Player* _player;

	std::uint32_t _rerollsLeft;
	bool _isExited;
	


	void Evaluate(const Command command);
	void Roll();
	void ExitGame();
	void LockDice();
	void Score();
};