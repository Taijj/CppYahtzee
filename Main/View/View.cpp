
#include <iostream>
#include <iomanip>
#include <functional>

#include <fstream>
#include <sstream>
#include <array>
#include <vector>

#include "View.h"
#include "../Global/Rules.h"


bool CheckGap(std::ifstream& file, std::string& line)
{
	if (!std::getline(file, line))
	{
		std::cout << "Expected a Gap, but encountered EOF instead!";
		return false;
	}
	
	// TODO: std::isspace

	if (!line.empty())
	{
		std::cout << "Expected a Gap, but encountered non-empty line instead!";
		return false;
	}

	return true;
}


void View::Wake()
{
	std::ifstream file("Resources/Sprites.txt");

	if (!file.is_open())
	{
		// File does not exist
		return;
	}
	std::string line;

	// Dimensions
	std::uint32_t width = 0;
	std::uint32_t height = 0;

	if (std::getline(file, line))
	{
		std::istringstream stream(line);
		
		if (stream >> width >> height)
		{
			std::cout << "Width: " << width << std::endl;
			std::cout << "Height: " << height << std::endl;
		}
		else
		{
			// Wrong Format of Width/Height in file!
		}
	}
	else
	{
		// Empty file
		return;
	}

	if (false == CheckGap(file, line))
		return;	

	using Sprites = std::array<std::vector<std::string>, Rules::DIE_SIDES>;
	Sprites sprites = {};	

	// Die height + 1 for gap - 1 to ignore last gap
	std::uint32_t iterations = height * (Rules::DIE_SIDES+1);
	std::uint32_t bar = height+1;
	std::uint32_t faceIndex = 0;
	for (std::uint32_t i = 0; i < iterations; ++i)
	{
		std::uint32_t foo = i >= height ? i - height : 1;
		bool isGap = foo % bar == 0;		
		if (isGap)
		{			
			if(false == CheckGap(file, line))
				return;

			++faceIndex;
			continue;
		}
		
		if (!std::getline(file, line))
		{
			std::cout << "Expected a line, but encountered EOF instead!";
			return;
		}

		if (line.size() < width)
		{
			std::cout << "Expected a line of at least length "
				<< width
				<< "! Got one of length "
				<< line.size()
				<< " instead!";
			return;
		}

		sprites[faceIndex].push_back(line.substr(0, width));
	}
	file.close();
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

void View::RenderRoundHeader(std::uint32_t roundIndex, std::uint32_t playerId)
{
	std::cout << "\n\n" << INDENT
		<< "Round " << roundIndex+1 << " __________________ "
		<< "Player " << playerId+1 << "\n"
		<< std::endl;
}

void View::RenderTable(std::vector<DieEntry> dice, std::vector<ComboEntry> combos)
{
	const auto renderEntry = [](const std::string entry)
		{
			std::cout << std::setw(ENTRY_WIDTH)
				<< std::left
				<< entry;
		};

	std::cout << INDENT;
	renderEntry("Hand___");
	renderEntry("Locked___");
	renderEntry("Combos___");
	std::cout << "\n\n";

	std::uint32_t height = static_cast<std::uint32_t>(std::max(dice.size(), combos.size()));
	for (std::uint32_t i = 0; i < height; ++i)
	{
		std::cout << INDENT;

		std::string column1 = i < dice.size() && !dice[i].isLocked
			? dice[i].Out()
			: EMPTY;
		renderEntry(column1);

		std::string column2 = i < dice.size() && dice[i].isLocked
			? dice[i].Out()
			: EMPTY;
		renderEntry(column2);

		std::string column3 = i < combos.size()
			? combos[i].Out()
			: EMPTY;
		renderEntry(column3);

		std::cout << '\n';
	}
}



void View::RenderInitialPhase()
{
	std::cout << "# Press any key to throw the dice!";
	std::cout.flush();
}

void View::RenderInvalidInput()
{
	std::cout << CLEAR_LINE
		<< INDENT << INVALID_INPUT;
	std::cout.flush();
}

void View::Clear()
{
	std::cout << CLEAR_ALL;
	std::cout.flush();
}