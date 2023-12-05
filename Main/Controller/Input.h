#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "../Global/ScoreKinds.h"

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

class Input
{

public:	
	using ScoreCommands = std::vector<std::pair<std::string, Score::Kind>>;

	inline static Command THROW = { 't', "Throw dice"};
	inline static Command EXIT = { 'x', "Cancel and exit game"};
	inline static Command LOCK = { 'l', "Select dice for later scoring" };
	inline static Command SCORE = { 's', "End turn and start scoring" };

	inline static Command YES = { 'y', "Yes!" };
	inline static Command NO = { 'n', "No!" };

	inline static const std::string LOCK_COMMANDS = "12345";
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

	static const std::uint32_t ForPlayerCount();
	static const Command* ForGame();
	static const Command* ForLocking(std::vector<std::uint32_t>& dieIds);
	static const Command* ForScoring(Score::Kind& scoreKind);
	static const Command* ForConfirmation();

	static void WaitForAnyKey();	

	inline static const bool isAutomatic = false;

private:

	static const Command* ParseForGameCommand(const std::string& input);
};