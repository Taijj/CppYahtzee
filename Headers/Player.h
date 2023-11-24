#pragma once

#include <map>
#include "Config.h"



using ScoresByKind = std::map<Score::Kind, std::uint32_t>;

class Player
{
public:
	Player(std::uint32_t id) : _id(id), _scoresByKind(ScoresByKind{})
	{}

	~Player() = default;

	void Reset();
	void Score(Score::Kind kind, std::uint32_t value);
	bool HasScore(Score::Kind kind);

private:
	std::uint32_t _id;
	ScoresByKind _scoresByKind;
	std::uint32_t _scoreTotal;
};