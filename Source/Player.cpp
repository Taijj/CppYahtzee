#include "../Headers/Player.h"



void Player::Reset()
{
	_scoreTotal = 0;
	_scoresByKind.clear();
}

void Player::Score(Score::Kind kind, std::uint32_t value)
{
	_scoresByKind[kind] = value;
	_scoreTotal += value;
}

bool Player::HasScore(Score::Kind kind)
{
	return _scoresByKind.contains(kind);
}