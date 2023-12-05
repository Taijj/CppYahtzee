#pragma once

#include <cstdint>
#include <string>
#include <format>
#include <vector>
#include <memory>

#include "SpritesLoader.h"

class View
{
public:

#pragma region Aliasses and Sub Structures
	using uInt = std::uint32_t;
	using string = std::string;
	using Tutorial = std::vector<std::string>;

	inline static const auto LOCK_TUTORIAL = Tutorial{
		"# LOCKING: Select one or multiple dice by typing in one or more numbers from 1-5.",
		"# Example: '125' will select the dice 1, 2, and 5."
	};

	inline static const auto SCORE_TUTORIAL = Tutorial{
		"# When scoring, select how you want to score by adding one of the following after the command:",
		"1 - Aces\t\t 2 - Twos\t\t 3 - Threes\t",
		"4 - Fours\t\t 5 - Fives\t\t 6 - Sixes\t",
		"3k - 3 of a Kind\t 4k - 4 of a Kind\t fh - Full House\t",
		"ss - Small Straight\t sl - Large Straight\t y - Yahtzee\t",
		"c - Chance"
	};

	struct DieData
	{
		uInt id;
		uInt face;
		bool isLocked;
	};

	struct ComboData
	{
		string name;
		std::int32_t score;
	};

	struct CommandData
	{
		char character;
		string description;
	};

	using DieDatas = std::vector<DieData>;
	using ComboDatas = std::vector<ComboData>;	
	using CommandDatas = std::vector<CommandData>;
#pragma endregion


#pragma region Main
	View() = delete;
	static void Wake();

	static void RenderWelcome();
	static void RenderInitialPhase();
	static void RenderRoundHeader(uInt roundIndex, uInt playerId);	
	static void RenderTable(const DieDatas& dice, const ComboDatas& combos);
	static void RenderCommands(const CommandDatas& commands, Tutorial tutorial = {});

	static void Clear();
	static void RenderInvalidInput();
#pragma endregion



private: 

	inline static const string CLEAR_ALL = "\x1B[2J\x1B[1;1H";
	inline static const string CLEAR_LINE = "\x1B[1A\x1B[2K";

	inline static const string INDENT = "  ";	
	inline static const string EMPTY = "--";
	
	inline static const string YOUR_INPUT = "=> Your Input: ";
	inline static const string INVALID_INPUT = "=> INVALID! Please try again: ";



	inline static std::unique_ptr<SpritesLoader> _sprites;
	inline static DieDatas _dice;
	inline static ComboDatas _combos;


	inline static constexpr uInt MAX_COMMANDS_PER_LINE = 2U;
	inline static constexpr uInt COMMAND_ENTRY_WIDTH = 30U;


	// Helpers for tabular rendering
	inline static constexpr uInt TABLE_LABEL_WIDTH = 10U;
	inline static constexpr uInt TABLE_COMBO_NAME_WIDTH = 12U;
	inline static constexpr uInt TABLE_COMBO_SCORE_WIDTH = 3U;
	inline static constexpr uInt TABLE_DIE_WIDTH = 7U;	

	static void RenderLabelCell(uInt row);
	static void RenderComboCell(uInt row);
	static void RenderDieCell(uInt row, uInt column);
	static void RenderCell(uInt width, string message = "");
};