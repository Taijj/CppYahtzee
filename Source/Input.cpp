#pragma once

#include "../Headers/Input.h"



const Command Input::GetDefault()
{
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

const Command* Input::GetLock(std::string& result)
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
			return nullptr;
	}
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



const Command* Input::TryGetCommand(const std::string& input)
{
	if (input.size() == 0)
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