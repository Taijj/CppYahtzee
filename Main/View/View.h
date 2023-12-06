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

	inline static const string DEFAULT_COMMAND_HEADLINE =
		"# Enter one of the following commands to play:";

	inline static const auto LOCK_TUTORIAL = Tutorial{
		"# LOCKING: Select one or multiple dice by entering one or more numbers from 1-5.",
		"# Example: '125' will select the dice 1, 2, and 5.\n",
		"# Or continue by entering one of the following commands:"
	};

	inline static const auto SCORE_TUTORIAL = Tutorial{
		"# Select how you want to score by entering a combo's command.",
		"# (See: List above)\n",
		"# Or exit the game with:"
	};

	enum HintKind
	{
		Default = 0,
		
		Locking,
		Scoring,
		None
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
		string command;
		std::int32_t score;
	};

	struct CommandData
	{
		char character;
		string description;
	};

	using CommandDatas = std::vector<CommandData>;



	struct Player
	{
		std::vector<ComboData> combos;
		uInt totalScore;
		uInt bonus;

		bool isWinner;
	};

	struct Table
	{
		std::vector<DieData> dice;		
		Player player;
	};
#pragma endregion



#pragma region Main
	View() = delete;
	static void Wake();

	static void RenderWelcome();

	static void RenderPressEnterToThrow();
	static void RenderRoundHeader(uInt roundIndex, uInt playerId);	
	static void RenderTable(const Table& table);
	static void RenderCommands(const CommandDatas& commands, const HintKind hint = Default);
	static void RenderPressEnterToComplete();
	
	static void RenderScoreBoard(const std::vector<Player>& players);
	static void RenderGoodBye();

	static void Clear();
	static void RenderInvalidInput();
	static void RenderExitConfirmation();
#pragma endregion



private: 

	inline static const string CLEAR_ALL = "\x1B[2J\x1B[1;1H";
	inline static const string CLEAR_LINE = "\x1B[1A\x1B[2K";

	inline static const string INDENT = "  ";	
	inline static const string EMPTY = "--";
	
	inline static const string YOUR_INPUT = "=> Your Input: ";
	inline static const string INVALID_INPUT = "=> INVALID! Please try again: ";



	inline static std::unique_ptr<SpritesLoader> _sprites;
	inline static Table _table;


	inline static constexpr uInt MAX_COMMANDS_PER_LINE = 2U;
	inline static constexpr uInt COMMAND_ENTRY_WIDTH = 30U;

	static void RenderHint(const HintKind kind);


	// Helpers for tabular rendering
	inline static constexpr uInt TABLE_LABEL_WIDTH = 10U;
	inline static constexpr uInt TABLE_COMBO_NAME_WIDTH = 12U;
	inline static constexpr uInt TABLE_COMBO_SCORE_WIDTH = 4U;
	inline static constexpr uInt TABLE_DIE_WIDTH = 7U;	
	inline static constexpr uInt TABLE_SCORE_WIDTH = 10U;

	inline static constexpr uInt SCORE_BOARD_COLUMN_WIDTH = 20U;
	inline static constexpr uInt SCORE_BOARD_COMBO_NAME_WIDTH = 14U;
	inline static constexpr uInt SCORE_BOARD_COMBO_SCORE_WIDTH = 6U;

	static void RenderLabelCell(uInt row);
	static void RenderComboCell(uInt row);
	static void RenderDieCell(uInt row, uInt column);
	static void RenderScoreCell(uInt row);
	static void RenderCell(uInt width, string message = "");
};