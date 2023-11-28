
#include "../Headers/Die.h"

void Die::Initialize(std::uint32_t id)
{
	_id = id;
	Reset();
}

void Die::Reset()
{	
	_currentValue = 0;
	_state = Default;
}



void Die::Roll()
{
	_state = Default;
	_currentValue = _distribution(_generator);
}

void Die::Set(State state) { _state = state; }
bool Die::Is(State state) const { return _state == state; }



std::uint32_t Die::GetValue() const
{
	return _currentValue;
}

std::uint32_t Die::GetId() const
{
	return _id;
}