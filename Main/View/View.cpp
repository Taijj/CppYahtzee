
#include <iostream>
#include <iomanip>

#include "View.h"



void View::Wake()
{
	_sprites = std::make_unique<SpritesLoader>();
	_sprites->LoadSprites();
}


void View::RenderCell(uInt width, string message)
{
	std::cout << std::setw(width)
		<< std::left
		<< message;
}


void View::RenderWelcome()
{
	std::cout << "\n\n"
		<< "\t--- Welcome to Yahtzee! ---\n"
		<< "\n\n"
		<< INDENT << "Please enter the number of players! (1-4)\n"
		<< '\n'
		<< INDENT << YOUR_INPUT;
	std::cout.flush();
}

void View::RenderGoodBye()
{
	std::cout << "\n"
		<< INDENT
		<< "Thanks for playing!\n\n"
		<< INDENT
		<< "Press Enter to finish..."
		<< std::endl;
}

void View::RenderRoundHeader(std::uint32_t roundIndex, std::uint32_t playerId)
{
	std::cout << '\n' << INDENT
		<< ">>> Round " << roundIndex+1 << " - "
		<< "Player " << playerId+1
		<< " _______________________________________________\n"
		<< std::endl;
}





void View::RenderPressEnterToThrow()
{
	std::cout
		<< INDENT
		<< "# Press Enter to throw the dice!\n"
		<< INDENT;
	std::cout.flush();
}

void View::RenderPressEnterToComplete()
{
	std::cout
		<< INDENT
		<< "# Press Enter to continue!\n"
		<< INDENT;
	std::cout.flush();
}

void View::RenderInvalidInput()
{
	std::cout << CLEAR_LINE
		<< INDENT << INVALID_INPUT;
	std::cout.flush();
}

void View::RenderExitConfirmation()
{
	std::cout << "\n\n\n" << INDENT
		<< "Do you really want to exit?\n"
		<< std::endl;
}

void View::Clear()
{
	std::cout << CLEAR_ALL;
	std::cout.flush();
}




void View::RenderCommands(const CommandDatas& commands, const HintKind hint)
{	
	RenderHint(hint);

	// Commands
	uInt count = 0;
	for (const auto& c : commands)
	{
		string out = std::format("({}) - {}", c.character, c.description);
		std::cout << INDENT
			<< std::setw(COMMAND_ENTRY_WIDTH)
			<< std::left
			<< out;

		count++;
		if (count >= MAX_COMMANDS_PER_LINE)
		{
			count = 0;
			std::cout << '\n';
		}
	}

	if (commands.size() % 2 == 1)
		std::cout << '\n';

	// Input field
	std::cout << '\n'
		<< INDENT
		<< YOUR_INPUT;
	std::cout.flush();
}

void View::RenderHint(const HintKind kind)
{
	if (kind == None)
		return;

	if (kind == Default)
	{
		std::cout
			<< INDENT
			<< DEFAULT_COMMAND_HEADLINE
			<< "\n\n";
		return;
	}

	const Tutorial tut = kind == Locking ? LOCK_TUTORIAL : SCORE_TUTORIAL;
	for (const auto& l : tut)
	{
		std::cout
			<< INDENT
			<< l
			<< '\n';
	}
	std::cout << '\n';
}



void View::RenderScoreBoard(const std::vector<Player>& players)
{
	std::cout << "\n"
		<< "\t\t\t--- The Game is over! ---\n"
		<< "\n\n";
	
	// 13 for each achievable Combo
	// 2 Extra for a column label
	// 2 Extra for a total score at the bottom
	std::uint32_t rows = 2 + 13 + 2;
	const std::uint32_t totalScoreGapRow = 15;
	for (std::uint32_t row = 0; row < rows; ++row)
	{
		bool isGap = row == 1 || row == totalScoreGapRow;
		if (isGap)
		{
			std::cout << '\n';
			continue;
		}

		std::cout << INDENT;
		for (std::uint32_t i = 0; i < players.size(); i++)
		{
			if (row == 0)
			{
				RenderCell(SCORE_BOARD_COLUMN_WIDTH, std::format("# Player {}:", i+1));			
				continue;
			}

			if (row > totalScoreGapRow)
			{
				RenderCell(SCORE_BOARD_COLUMN_WIDTH, std::format("Total: {}", players[i].totalScore));
				continue;
			}

			ComboData data = players[i].combos[row-2];
			RenderCell(SCORE_BOARD_COMBO_NAME_WIDTH, std::format("{}:", data.name));
			RenderCell(SCORE_BOARD_COMBO_SCORE_WIDTH, std::to_string(data.score));
		}
		std::cout << '\n';
	}
	std::cout << "\n";



	string text = "";
	if (players.size() == 1)
	{
		text = players[0].totalScore >= Rules::SINGLE_PLAYER_WIN_SCORE
			? std::format("# Congratulations! You got more than {} points! You won!\n", Rules::SINGLE_PLAYER_WIN_SCORE)
			: std::format("# Oh no! You need at least {} points! You lost!\n", Rules::SINGLE_PLAYER_WIN_SCORE);
	}
	else
	{		
		for (std::uint32_t i = 0; i < players.size(); ++i)
		{
			if (false == players[i].isWinner)
				continue;

			text = std::format("# Player {} has won the game!\n", i+1);
			break;			
		}
	}	

	std::cout << INDENT
		<< text
		<< std::endl;
}