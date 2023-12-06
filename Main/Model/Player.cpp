#include "Player.h"
#include "../Global/Rules.h"
#include "../Model/Model.h"



std::uint32_t Player::Id() const { return _id; }

std::uint32_t Player::TotalScore() const { return _totalScore; }
std::uint32_t Player::PotentialScore() const { return _potentialScore; }
bool Player::HasBonus() const { return _hasBonus; }



void Player::Reset()
{
	_totalScore = 0;
	_scoresByKind.clear();
	CalculateScores();
}



void Player::SetScore(const Score::Kind kind, const std::uint32_t value)
{
	_scoresByKind[kind] = value;
	CalculateScores();
}

bool Player::TryGetScore(const Score::Kind kind, std::int32_t& score) const
{
	score = Rules::UNDEFINED;
	if (false == _scoresByKind.contains(kind))
		return false;	

	score = _scoresByKind.at(kind);
	return true;
}



void Player::CalculateScores()
{	
	_totalScore = 0;
	_potentialScore = 0;
	SumUp(Score::Aces, Score::Sixes);

	_hasBonus = _totalScore >= Rules::BONUS_THRESHOLD;
	if (_hasBonus)
		_totalScore += Rules::BONUS_SCORE;

	if (_potentialScore >= Rules::BONUS_THRESHOLD)
		_potentialScore += Rules::BONUS_SCORE;

	SumUp(Score::OfKind3, Score::Chance);
}

void Player::SumUp(const Score::Kind from, const Score::Kind to)
{
	for (std::uint32_t i = from; i < to+1U; ++i)
	{
		std::int32_t score;
		bool hasScore = TryGetScore(static_cast<Score::Kind>(i), score);

		_totalScore += hasScore ? score : 0;
		_potentialScore = !hasScore
			? Model::COMBOS.at(i-1)->MaxPossibleScore()
			: score;
	}
}