#pragma once

#include "../Headers/Input.h"


const std::uint32_t Input::GetPlayers()
{
	if (isAutomatic)
		return 4;

	std::string input;	
	while (true)
	{
		std::cin >> input;	
		if (input.size() != 1)
		{
			Renderer::RenderInvalid();
			continue;
		}

		std::uint32_t result = 0;
		try
		{
			result = std::stoi(input);
		}
		catch (std::exception e)
		{
			Renderer::RenderInvalid();
			continue;
		}
		
		if (result < 1 || result > Rules::MAX_PLAYERS)
			Renderer::RenderInvalid();
		else
			return result;
	}
}

const Command Input::GetInitial()
{
	if (isAutomatic)
		return THROW;

	std::string input;
	const Command* com = nullptr;
	while (true)
	{
		std::cin >> input;
		com = TryGetCommand(input);
				
		if (com == nullptr)
			Renderer::RenderInvalid();
		else if (*com != THROW && *com != EXIT)
			Renderer::RenderInvalid();
		else
			return *com;
	}
}

const Command Input::GetPlaying()
{
	if (isAutomatic)
		return THROW;

	std::string input;
	const Command* com = nullptr;
	while (true)
	{
		std::cin >> input;
		com = TryGetCommand(input);

		if (com == nullptr)
			Renderer::RenderInvalid();
		else
			return *com;
	}
}

const Command* Input::GetLocking(std::string& result)
{
	std::string input = "";
	const Command* command = nullptr;
	while (true)
	{
		result.clear();
		std::cin >> input;

		int length = static_cast<int>(input.size());
		if (length == 0)
		{
			Renderer::RenderInvalid();
			continue;
		}

		// Return early, if one of the default commands was put in
		command = TryGetCommand(input);
		if (command != nullptr && *command != LOCK)
			return command;

		// The user may input millions of characters.To counter that
		// we're only considering the first 10 characters.
		std::uint32_t min = std::min(10, length);
		for (std::uint32_t i = 0; i < min; ++i)
		{
			char c = input[i];
			if (LOCK_COMMANDS.contains(c) && !result.contains(c))
				result += c;
		}

		if (result.size() == 0)
			Renderer::RenderInvalid();
		else
			return command;
	}
}

const Command* Input::GetScoring(Score::Kind& result, Player &player)
{
	if (isAutomatic)
	{
		for (const Combo* c : COMBOS)
		{
			if (false == player.HasScore(c->Kind()))
			{
				result = c->Kind();
				return nullptr;
			}				
		}
	}

	std::string input = "";
	const Command* defaultCommand = nullptr;
	while (true)
	{
		result = Score::Kind::Undefined;
		std::cin >> input;

		int length = static_cast<int>(input.size());
		if (length < 0)
		{
			Renderer::RenderInvalid();
			continue;
		}

		// Return early, if player wants to exit
		defaultCommand = TryGetCommand(input);
		if (defaultCommand != nullptr && *defaultCommand == EXIT)
			return defaultCommand;

		std::uint32_t commandLength = length == 1 ? 1 : 2;		
		for (std::uint32_t i = 0; i < SCORE_COMMANDS.size(); ++i)
		{
			std::string com = input.substr(0, commandLength);
			if (com == SCORE_COMMANDS[i].first)
			{
				result = SCORE_COMMANDS[i].second;
				return defaultCommand;
			}
		}
		
		Renderer::RenderInvalid();
	}
	return defaultCommand;
}



bool Input::IsExitConfirmed()
{
	std::string input;
	while (true)
	{
		std::cin >> input;
		
		if (input.size() != 1)
		{
			Renderer::RenderInvalid();			
			continue;
		}

		const char first = input[0];
		if (first != 'y' && first != 'n')
		{
			Renderer::RenderInvalid();
			continue;
		}

		return first == 'y';
	}
}

void Input::WaitForAnyKey()
{	
	char c;
	std::cin.clear(); // clear any potential error flags
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear input buffer
	std::cin.get(c); // wait for any input
}



const Command* Input::TryGetCommand(const std::string& input)
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