#pragma once

#include <iostream>

#include "Input.h"
#include "../Global/Rules.h"

const std::uint32_t Input::ForPlayerCount()
{
	if (isAutomatic)
		return Rules::MAX_PLAYER_COUNT;

	std::string input;
	std::cin >> input;	
		
	std::uint32_t result = 0;
	try
	{
		result = std::stoi(input);
	}
	catch (std::exception e)
	{
		return result;
	}

	bool isValid = result > 0 && result <= Rules::MAX_PLAYER_COUNT;
	return isValid ? result : 0;
}

const Command* Input::ForGame()
{
	if (isAutomatic)
		return &THROW;

	std::string input;
	std::cin >> input;
	return ParseForGameCommand(input);
}

const Command* Input::ForLocking(std::vector<std::uint32_t>& dieIds)
{
	const Command* command = nullptr;
	dieIds.clear();
		
	std::string input;
	std::cin >> input;

	int length = static_cast<std::uint32_t>(input.size());
	if (length == 0)
		return command;

	// Return early, if one of the default commands was put in
	command = ParseForGameCommand(input);
	if (command != nullptr && *command != LOCK)
		return command;

	// The user may input millions of characters.To counter that
	// we're only considering the first 10 characters.
	std::uint32_t min = std::min(10, length);
	for (std::uint32_t i = 0; i < min; ++i)
	{
		char c = input[i];
		if (false == LOCK_COMMANDS.contains(c))
			continue;

		std::uint32_t id = c - '0'; // char to digit conversion
		if (std::count(dieIds.begin(), dieIds.end(), id) == 0)
			dieIds.push_back(id);
	}
	
	return command;
}

const Command* Input::ForScoring(Score::Kind& scoreKind)
{
	const Command* command = nullptr;
	scoreKind = Score::Kind::Undefined;

	std::string input;
	std::cin >> input;

	int length = static_cast<int>(input.size());
	if (length <= 0)
		return command;

	// Return early, if player wants to exit
	command = ParseForGameCommand(input);
	if (command != nullptr && *command == EXIT)
		return command;

	// Scoring sub commands are expected to either be 1 or 2 characters long
	std::uint32_t commandLength = length == 1 ? 1 : 2;
	for (std::uint32_t i = 0; i < SCORE_COMMANDS.size(); ++i)
	{
		std::string com = input.substr(0, commandLength);
		if (com == SCORE_COMMANDS[i].first)
		{
			scoreKind = SCORE_COMMANDS[i].second;
			return command;
		}
	}
	
	return command;
}



const Command* Input::ForConfirmation()
{
	std::string input;
	std::cin >> input;

	if (input.size() != 1)
		return nullptr;

	const char first = input[0];
	if (first == YES.character)
		return &YES;
	if (first == NO.character)
		return &NO;

	return nullptr;	
}

void Input::WaitForAnyKey()
{	
	char c;
	std::cin.clear(); // clear any potential error flags
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear input buffer
	std::cin.get(c); // wait for any input
}



const Command* Input::ParseForGameCommand(const std::string& input)
{
	if (input.size() != 1)
		return nullptr;

	char first = input[0];
	if (first == THROW.character)
		return &THROW;
	else if (first == EXIT.character)
		return &EXIT;
	else if (first == LOCK.character)
		return &LOCK;
	else if (first == SCORE.character)
		return &SCORE;
	else
		return nullptr;
}