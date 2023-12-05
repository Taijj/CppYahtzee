
#include <iostream>
#include <iomanip>

#include "View.h"



void View::Wake()
{
	_sprites = std::make_unique<SpritesLoader>();
	_sprites->LoadSprites();
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
	std::cout << '\n' << INDENT
		<< "Round " << roundIndex+1 << " __________________ "
		<< "Player " << playerId+1 << "\n"
		<< std::endl;
}





void View::RenderInitialPhase()
{
	std::cout
		<< INDENT
		<< "# Press any key to throw the dice!";
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



void View::RenderCommands(const CommandDatas& commands, Tutorial tutorial)
{
	// Headline
	std::cout
		<< INDENT
		<< "# Use the following commands to continue:\n\n";

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

	// Tutorial
	if (tutorial.size() != 0)
	{
		std::cout << "\n\n";
		for (const auto& l : tutorial)
		{
			std::cout
				<< INDENT
				<< l
				<< '\n';
		}
	}

	// Input field
	std::cout << '\n'
		<< INDENT
		<< YOUR_INPUT;
	std::cout.flush();
}