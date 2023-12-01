#pragma once

#include <vector>
#include <memory>
#include "Die.h"
	

class Model
{	

public:

	using Dice = std::vector<std::unique_ptr<Die>>;

	Model() = delete;	

	static void Wake();

	static Dice& GetDice();

private:
	inline static Dice _dice = Dice{ Die::SIDES };
};