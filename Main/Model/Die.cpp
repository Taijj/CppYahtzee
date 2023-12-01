#include "Die.h"

void Die::Reset()
{	
	_face = 0;
	_state = Unused;
}

void Die::Throw()
{
	_state = Unused;
	_face = GetRandomValue();
}

void Die::Set(State state) { _state = state; }
bool Die::IsIn(State state) const { return _state == state; }

std::uint32_t Die::Id() const { return _id; }
std::uint32_t Die::Face() const { return _face; }