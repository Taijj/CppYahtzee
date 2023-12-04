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
	using Tutorial = std::vector<std::string>;
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
	
		

	inline static const auto LOCK_TUTORIAL = Tutorial {
		"# Select one or multiple dice by typing in one or more numbers from 1-5.",
		"# Example: '125' will select the dice 1, 2, and 5.\n",
		"# Use the default command to continue or end your turn:"
	};
		
	inline static const auto SCORE_TUTORIAL = Tutorial{
		"# When scoring, select how you want to score by adding one of the following after the command:",		
		"1 - Aces\t\t 2 - Twos\t\t 3 - Threes\t",
		"4 - Fours\t\t 5 - Fives\t\t 6 - Sixes\t",
		"3k - 3 of a Kind\t 4k - 4 of a Kind\t fh - Full House\t",
		"ss - Small Straight\t sl - Large Straight\t y - Yahtzee\t",
		"c - Chance"
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