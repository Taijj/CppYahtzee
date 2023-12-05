#include <iostream>
#include <iomanip>

#include "View.h"

// This file was separated from View.cpp for readability reasons.

void View::RenderTable(const DieDatas& dice, const ComboDatas& combos)
{
	_dice = dice;
	_combos = combos;

	std::cout << '\n';

	// The following logic renders a Table containing the "Hand" and "Locked" Labels,
	// the respective dice, rendered as character sprites, and the 13 possible game
	// Combos, displayed as a name with a score value.
	// 
	// The table has 7 Columns (0:Labels - 1-5:Dice - 6:Combos) and
	// 13 Rows (1 for each Combo, the remaining data centered in the vertical middle)
	for (std::uint32_t row = 0; row < 13; ++row)
	{
		std::cout << INDENT;

		for (std::uint32_t column = 0; column < 7; ++column)
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
	std::cout << INDENT
		<< std::setw(TABLE_COMBO_NAME_WIDTH) << std::right
		<< _combos[row].name << ": "
		<< std::setw(TABLE_COMBO_SCORE_WIDTH) << std::right;

	std::int32_t score = _combos[row].score;
	if (score >= 0)
		std::cout << score;
	else
		std::cout << EMPTY;
}

void View::RenderDieCell(uInt row, uInt column)
{
	const uInt middleGap = 6;
	const bool isGap = row == 0 || row == middleGap || row == 12;
	if (isGap)
	{
		RenderCell(TABLE_DIE_WIDTH);
		return;
	}

	DieData entry = _dice[column-1];
	if (entry.isLocked)
	{
		RenderCell(TABLE_DIE_WIDTH, row > middleGap
			? _sprites->GetBy(entry.face).at(row - middleGap-1)
			: ""
		);
	}
	else
	{
		RenderCell(TABLE_DIE_WIDTH, row < middleGap
			? _sprites->GetBy(entry.face).at(row-1)
			: ""
		);
	}
}

void View::RenderCell(uInt width, string message)
{
	std::cout << std::setw(width)
		<< std::left
		<< message;
}