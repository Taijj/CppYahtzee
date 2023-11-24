#pragma once
#include <cstdint>
#include <random>
#include <exception>

#include "Utils.h"

class Die
{
public:

	enum State
	{
		Default = 0,
		Selected,
		Locked
	};


	Die() = default;
	~Die() = default;

	void Initialize(std::uint32_t id)
	{
		_id = id;
		_currentValue = 0;
		_state = Default;
	}



	void Roll()
	{			
		_state = Default;
		_currentValue = _distribution(_generator);
	}

	void Set(State state) { _state = state; }
	bool Is(State state) const { return _state == state; }



	std::uint32_t GetValue() const
	{
		if (_currentValue == 0)
			throw std::exception("Die was not rolled! Make sure to call Roll() before attempting to get a value!");

		return _currentValue;
	}

	std::uint32_t GetId() const
	{
		return _id;
	}



private:	
	static constexpr std::uint32_t SIDES = 6;

	inline static std::random_device _seed;
	inline static std::mt19937 _generator{ _seed() };
	inline static std::uniform_int_distribution<std::int32_t> _distribution{ 1,6 };

	std::uint32_t _id;
	std::uint32_t _currentValue;
		
	State _state;
};