#pragma once

#include "Utils.h"
#include "Config.h"
#include "Renderer.h"

class Turn
{

public:
	Turn(GameDice& dice, Renderer& renderer)
		: _renderer(renderer), _dice(dice), _rerollCount(0), _isExited(false)
	{}

	~Turn() = default;



	void Execute();
	bool IsCompleted();
	bool IsExited();



private:	
	Renderer& _renderer;
	GameDice& _dice;

	std::uint32_t _rerollCount;
	bool _isExited;
	


	void Evaluate(const Command command);
	void Roll();
	void ExitGame();
	void LockDice();
	void Score();	
};