
#include <iostream>

#include "View.h"

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