#pragma once
#include <cstdint>
#include <random>

#include "../Global/Rules.h"

/// <summary>
/// Representation of one game die.
/// </summary>
class Die
{
public:

	enum State
	{
		Unused = 0,	// Not thrown, yet

		Thrown,		// Thrown
		ToBeLocked,	// Selected during the locking phase
		Locked		// Locked in for scoring
	};	



	Die() = default;

	Die(std::uint32_t id) : 
		_id(id), _face(0), _state(Unused)
	{}

	~Die() = default;



	void Reset();
	void Throw();

	std::uint32_t Id() const;

	/// <summary>
	/// Returns the value of the side facing up
	/// </summary>	
	std::uint32_t Face() const;

	void Set(State state);
	bool IsIn(State state) const;



private:
		
	inline static std::mt19937 GENERATOR{ std::random_device{}() };
	inline static std::uniform_int_distribution<std::int32_t> DISTRIBUTION{ 1, Rules::DIE_SIDES };
	static std::uint32_t GetRandomValue() { return DISTRIBUTION(GENERATOR); }

	std::uint32_t _id;

	std::uint32_t _face;
	State _state;
};