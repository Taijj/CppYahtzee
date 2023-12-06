#include <iostream>
#include <iomanip>

#include "View.h"

// This file contains the more tabularic output functions of View.

void View::RenderCell(uInt width, string message)
{
	std::cout << std::setw(width)
		<< std::left
		<< message;
}

void View::RenderTable(const Table& table)
{
	_table = table;
	std::cout << '\n';

	// The following logic renders a Table containing the "Hand" and "Locked" Labels,
	// the respective dice, rendered as character sprites, combos, the player's total
	// score and more.
	// 
	// The table has 8 Columns (0:Labels - 1-5:Dice - 6:Combos - 7:Score & Bonus) and
	// The table has 8 Columns (0:Labels - 1-5:Dice - 6:Combos - 7:Score & Bonus) and
	// 13 Rows (1 for each Combo, the remaining data centered in the vertical middle)
	for (std::uint32_t row = 0; row < 13; ++row)
	{
		std::cout << INDENT;

		for (std::uint32_t column = 0; column < 8; ++column)
		{
			if (column == 0)
			{
				RenderLabelCell(row);
				continue;
			}
			
			if (column == 6)
			{
				RenderComboCell(row);
				continue;
			}

			if (column == 7)
			{
				RenderScoreCell(row);
				continue;
			}

			RenderDieCell(row, column);
		}

		std::cout << '\n';
	}

	std::cout << std::endl;
}

void View::RenderLabelCell(uInt row)
{
	switch (row)
	{
		case 3: RenderCell(TABLE_LABEL_WIDTH, "HAND:"); break;
		case 9: RenderCell(TABLE_LABEL_WIDTH, "LOCKED:"); break;
		default: RenderCell(TABLE_LABEL_WIDTH); break;
	}	
}

void View::RenderComboCell(uInt row)
{
	ComboData data = _table.player.combos[row];

	std::cout << INDENT
		<< std::setw(TABLE_COMBO_NAME_WIDTH) << std::right
		<< data.name << ": "
		<< std::setw(TABLE_COMBO_SCORE_WIDTH) << std::right;
	
	string cell = data.score < 0
		? std::format("({})", data.command)
		: std::to_string(data.score);
	std::cout << cell;
}

void View::RenderDieCell(uInt row, uInt column)
{
	const uInt middleGap = 6;
	const bool isGap = row == middleGap || row == 12;
	if (isGap)
	{
		RenderCell(TABLE_DIE_WIDTH);
		return;
	}

	DieData die = _table.dice[column-1];
	const bool isHeadline = row == 0;
	if (isHeadline)
	{
		RenderCell(TABLE_DIE_WIDTH, std::format("- {} -", die.id+1));
		return;
	}

	if (die.isLocked)
	{
		RenderCell(TABLE_DIE_WIDTH, row > middleGap
			? _sprites->GetBy(die.face).at(row - middleGap-1)
			: ""
		);
	}
	else
	{
		RenderCell(TABLE_DIE_WIDTH, row < middleGap
			? _sprites->GetBy(die.face).at(row-1)
			: ""
		);
	}
}

void View::RenderScoreCell(uInt row)
{
	if (row == 0)
	{
		uInt score = _table.player.totalScore;
		RenderCell(TABLE_SCORE_WIDTH,
			std::format("{}Total: {}", INDENT, _table.player.totalScore));
	}
	else if (row == 2)
	{
		uInt bonus = _table.player.bonus;
		if (bonus < 0)
			return;

		RenderCell(TABLE_SCORE_WIDTH,
			std::format("{}Bonus: {}", INDENT, bonus));
	}
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
				RenderCell(SCORE_BOARD_COLUMN_WIDTH, std::format("# Player {}:", i + 1));
				continue;
			}

			if (row > totalScoreGapRow)
			{
				RenderCell(SCORE_BOARD_COLUMN_WIDTH, std::format("Total: {}", players[i].totalScore));
				continue;
			}

			ComboData data = players[i].combos[row - 2];
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

			text = std::format("# Player {} has won the game!\n", i + 1);
			break;
		}
	}

	std::cout << INDENT
		<< text
		<< std::endl;
}