#include <iostream>
#include <iomanip>

#include "View.h"

// This file was separated from View.cpp for readability reasons.

void View::RenderTable(const Table& table)
{
	_table = table;
	std::cout << '\n';

	// The following logic renders a Table containing the "Hand" and "Locked" Labels,
	// the respective dice, rendered as character sprites, combos, the player's total
	// score and more.
	// 
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
	ComboData data = _table.combos[row];

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
		RenderCell(TABLE_SCORE_WIDTH,
			std::format("{}Total: {}", INDENT, _table.totalScore));
	}
	else if (row == 2 && _table.bonus > 0)
	{
		RenderCell(TABLE_SCORE_WIDTH,
			std::format("{}Bonus: {}", INDENT, _table.bonus));
	}
}

void View::RenderCell(uInt width, string message)
{
	std::cout << std::setw(width)
		<< std::left
		<< message;
}