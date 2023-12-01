//#include "../Headers/Player.h"
//
//
//
//void Player::Reset()
//{
//	_scoreTotal = 0;
//	_scoresByKind.clear();
//	CalculateTotalScores();
//}
//
//std::uint32_t Player::GetId() const
//{
//	return _id;
//}
//
//void Player::SetScore(const Score::Kind kind, const std::uint32_t value)
//{
//	_scoresByKind[kind] = value;
//	CalculateTotalScores();
//}
//
//std::uint32_t Player::GetScore(const Score::Kind kind)
//{
//	return HasScore(kind) ? _scoresByKind[kind] : 0;
//}
//
//bool Player::HasScore(const Score::Kind kind) const
//{
//	return _scoresByKind.contains(kind);
//}
//
//std::uint32_t Player::GetTotal() const { return _scoreTotal; }
//std::uint32_t Player::GetPotential() const { return _scorePotential; }
//bool Player::HasReachedBonus() const { return _hasReachedBonus; }
//
//
//
//void Player::CalculateTotalScores()
//{	
//	_scoreTotal = 0;
//	_scorePotential = 0;
//	SumUp(0, Score::OfKind3);
//
//	_hasReachedBonus = _scoreTotal >= Rules::BONUS_THRESHOLD;
//	if (_hasReachedBonus)
//		_scoreTotal += Rules::BONUS_SCORE;
//
//	if (_scorePotential >= Rules::BONUS_THRESHOLD)
//		_scorePotential += Rules::BONUS_SCORE;
//
//	SumUp(Score::OfKind3, Score::Chance);
//}
//
//void Player::SumUp(const std::uint32_t from, const std::uint32_t to)
//{
//	for (std::uint32_t i = from; i < to; ++i)
//	{
//		std::uint32_t score = GetScore(static_cast<Score::Kind>(i));
//		_scoreTotal += score;
//
//		_scorePotential += false == HasScore(static_cast<Score::Kind>(i))
//			? COMBOS[i]->MaxPossibleScore()
//			: score;
//	}
//}