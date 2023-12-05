
#include <iostream>
#include <iomanip>

#include "View.h"



void View::Wake()
{
	_sprites = std::make_unique<SpritesLoader>();
	_sprites->LoadSprites();
		
	for(std::uint32_t i = 0; i < Rules::DIE_SIDES; ++i)
	{
		const SpritesLoader::Sprite s = _sprites->GetBy(i);
		for (const auto& r : s)
			std::cout << r << '\n';
	}
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