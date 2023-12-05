#pragma once

#include <map>

#include "../Global/ScoreKinds.h"

/// <summary>
/// Representation of one player playing the game.
/// </summary>
class Player
{
public:
	using uInt = std::uint32_t;
	using ScoresByKind = std::map<Score::Kind, uInt>;

	Player(uInt id) : _id(id), _scoresByKind(ScoresByKind{}),
		_totalScore(0), _potentialScore(0), _hasBonus(false)
	{}

	~Player() = default;

	uInt Id() const;

	/// <summary>
	/// Resets all scores to 0.
	/// </summary>
	void Reset();
		
	void SetScore(const Score::Kind kind, const uInt value);

	/// <summary>
	/// Used to retrieve a score value from a certain Combo.
	/// </summary>
	/// <param name="kind">The ScoreKind of the target Combo.</param>
	/// <param name="score">If the player has scored a Combo with the given kind, this
	/// will be set to that score, -1 otherwise.</param>
	/// <returns>True, if the player has scored the Combo, false otherwise</returns>
	bool TryGetScore(const Score::Kind kind, std::int32_t& score) const;
	
	/// <summary>
	/// Returns the total score this Player has achieved so far.
	/// </summary>
	uInt TotalScore() const;

	/// <summary>
	/// Returns the score this Player could still achieve, if they
	/// score the remaining Combos perfectly.
	/// </summary>
	uInt PotentialScore() const;

	/// <summary>
	/// Did this player achieve enough points to be awarded the "Part1" bonus?
	/// </summary>
	bool HasBonus() const;

private:
	uInt _id;
	ScoresByKind _scoresByKind;
		
	uInt _totalScore;
	uInt _potentialScore;
	bool _hasBonus;

	/// <summary>
	/// Calculates the total and potential scores for this player, and
	/// determines, if they achieved the "Part1" bonus
	/// </summary>
	void CalculateScores();

	/// <summary>
	/// Helper method, to sum up the face values of scored Combos in the
	/// given range set by from and to.
	/// </summary>
	void SumUp(const Score::Kind from, const Score::Kind to);
};