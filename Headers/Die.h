#pragma once
#include <cstdint>
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

	Die() = default;
	~Die() = default;

	void Initialize(std::uint32_t id);



	void Roll();
	void Set(State state);
	bool Is(State state) const;

	std::uint32_t GetValue() const;
	std::uint32_t GetId() const;



private:	
	static constexpr std::uint32_t SIDES = 6;

	inline static std::random_device _seed;
	inline static std::mt19937 _generator{ _seed() };
	inline static std::uniform_int_distribution<std::int32_t> _distribution{ 1,6 };

	std::uint32_t _id;
	std::uint32_t _currentValue;
		
	State _state;
};