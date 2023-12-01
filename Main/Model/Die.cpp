#include "Die.h"

void Die::Reset()
{	
	_currentValue = 0;
	_state = Default;
}

void Die::Throw()
{
	_state = Default;
	_currentValue = GetRandomValue();
}

void Die::Set(State state) { _state = state; }
bool Die::IsIn(State state) const { return _state == state; }

std::uint32_t Die::Id() const { return _id; }
std::uint32_t Die::Value() const { return _currentValue; }