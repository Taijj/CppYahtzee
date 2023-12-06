#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "../Global/ScoreKinds.h"

/// <summary>
/// Helper class for defining possible user input
/// </summary>
class Command
{
public:
	const char character;
	const std::string description;
	
	bool operator==(const Command& other)
	{		
		return other.character == character;
	}
};

/// <summary>
/// Static class that takes care of user input validation and
/// sanitization.
/// </summary>
class Input
{

public:	

	inline static Command THROW = { 't', "Throw dice"};
	inline static Command EXIT = { 'x', "Cancel and exit game"};
	inline static Command LOCK = { 'l', "Select dice for later scoring" };
	inline static Command SCORE = { 's', "End turn and start scoring" };

	inline static Command YES = { 'y', "Yes!" };
	inline static Command NO = { 'n', "No!" };

	inline static const std::string LOCK_COMMANDS = "12345";

	using ScoreCommands = std::vector<std::pair<std::string, Score::Kind>>;
	inline static const ScoreCommands SCORE_COMMANDS =
	{
		{"1", Score::Kind::Aces },
		{"2", Score::Kind::Twos },
		{"3", Score::Kind::Threes },
		{"4", Score::Kind::Fours },
		{"5", Score::Kind::Fives },
		{"6", Score::Kind::Sixes },
		{"3k", Score::Kind::OfKind3 },
		{"4k", Score::Kind::OfKind4 },
		{"fh", Score::Kind::FullHouse },
		{"ss", Score::Kind::StraightSmall },
		{"sl", Score::Kind::StraightLarge },
		{"y", Score::Kind::Yahtzee },
		{"c", Score::Kind::Chance }
	};



	Input() = delete;

	/// <summary>
	/// Prompt the user to enter the number of players.
	/// </summary>
	/// <returns>The player count.</returns>
	static const std::uint32_t ForPlayerCount();

	/// <summary>
	/// Prompt the user to enter one of the game's commands.
	/// </summary>
	/// <returns>A pointer to the selected game command.</returns>
	static const Command* ForGame();

	/// <summary>
	/// Prompt the user to enter a command for the locking phase of the game.
	/// </summary>
	/// <param name="dieIds">If the user entered any die indeces they are stored in this vector.</param>
	/// <returns>Returns a selected game command, if the user entered a valid one for this game phase,
	/// a null pointer otherwise.</returns>
	static const Command* ForLocking(std::vector<std::uint32_t>& dieIds);

	/// <summary>
	/// Prompt the user to enter a command for the scoring phase of the game.
	/// </summary>
	/// <param name="scoreKind">If the user entered any scoring command,
	/// this will contain its corresponding score kind.</param>
	/// <returns>Returns a selected game command, if the user entered a valid one for this game phase,
	/// a null pointer otherwise.</returns>
	static const Command* ForScoring(Score::Kind& scoreKind);

	/// <summary>
	/// Prompt the user to confirm, if they really want to exit the game.
	/// </summary>
	/// <returns>YES or NO, if the user entered a sensible command, nullptr if not.</returns>
	static const Command* ForConfirmation();

	/// <summary>
	/// Prompt the user to press the "Enter" (return) key.
	/// </summary>
	static void WaitForEnter();	

	/// <summary>
	/// Set this to true, to automatically let the game run
	/// with maximum number of players.
	/// </summary>
	inline static const bool isAutomatic = false;

private:

	static const Command* ParseForGameCommand(const std::string& input);
};