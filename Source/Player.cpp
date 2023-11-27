#include "../Headers/Player.h"



void Player::Reset()
{
	_scoreTotal = 0;
	_scoresByKind.clear();
}

void Player::SetScore(Score::Kind kind, std::uint32_t value)
{
	_scoresByKind[kind] = value;
	_scoreTotal += value;
}

std::uint32_t Player::GetScore(Score::Kind kind)
{
	if (false == HasScore(kind))
		throw std::exception("Cannot get score, because player has not scored that kind, yet!");

	return _scoresByKind[kind];
}

bool Player::HasScore(Score::Kind kind) const
{
	return _scoresByKind.contains(kind);
}