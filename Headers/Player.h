#pragma once

#include <map>
#include "Config.h"



using ScoresByKind = std::map<Score::Kind, std::uint32_t>;

class Player
{
public:
	Player(std::uint32_t id) : _id(id), _scoresByKind(ScoresByKind{}), _scoreTotal(0)
	{}

	~Player() = default;

	void Reset();
	std::uint32_t GetId() const;
	bool HasScore(Score::Kind kind) const;

	void SetScore(Score::Kind kind, std::uint32_t value);	
	std::uint32_t GetScore(Score::Kind kind);	
	std::uint32_t GetTotal() const;

private:
	std::uint32_t _id;
	ScoresByKind _scoresByKind;
	std::uint32_t _scoreTotal;
};