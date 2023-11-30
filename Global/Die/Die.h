#pragma once
#include<cstdint>
#include <random>

class Die
{
public:

	enum State
	{
		Default = 0,
		Selected,
		Locked
	};

	Die(std::uint32_t id) : 
		_id(id), _currentValue(0), _state(Default)
	{}

	~Die() = default;

	void Reset();
	void Throw();

	std::uint32_t Id() const;
	std::uint32_t Value() const;

	void Set(State state);
	bool Is(State state) const;

private:

	inline static constexpr std::uint32_t SIDES = 6;
	inline static const std::mt19937 GENERATOR { std::random_device{}() };
	inline static std::uniform_int_distribution<std::int32_t> DISTRIBUTION { 1, SIDES };
	static std::uint32_t GetRandomValue() { return DISTRIBUTION(GENERATOR); }

	std::uint32_t _id;

	std::uint32_t _currentValue;
	State _state;
};