
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
	for (const auto& l : LOCK_TUTORIAL)
	{
		std::cout
			<< INDENT
			<< l
			<< '\n';
	}
	std::cout << '\n';
}