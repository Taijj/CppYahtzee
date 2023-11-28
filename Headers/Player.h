#pragma once

#include <map>
#include "Config.h"
#include "Combos.h"



using ScoresByKind = std::map<Score::Kind, std::uint32_t>;

class Player
{
public:
	Player(std::uint32_t id) : _id(id), _scoresByKind(ScoresByKind{}),
		_scoreTotal(0), _scorePotential(0)
	{}

	~Player() = default;

	void Reset();
	std::uint32_t GetId() const;
	bool HasScore(Score::Kind kind) const;

	void SetScore(const Score::Kind kind, const std::uint32_t value);
	std::uint32_t GetScore(const Score::Kind kind);
	std::uint32_t GetTotal() const;
	std::uint32_t GetPotential() const;
	bool HasReachedBonus() const;

private:
	std::uint32_t _id;
	ScoresByKind _scoresByKind;
		
	std::uint32_t _scoreTotal;
	std::uint32_t _scorePotential;
	bool _hasReachedBonus;

	void CalculateTotalScores();
	void SumUp(const std::uint32_t from, const std::uint32_t to);
};