
#include <sstream>
#include <format>
#include <exception>
#include <cctype>

#include "SpritesLoader.h"



#pragma region Main
void SpritesLoader::LoadSprites()
{
	if (_sprites != nullptr)
	{
		Sprites* raw = _sprites.release();
		delete[] raw;
	}
	_sprites = std::make_unique<Sprites>();

	_file = std::ifstream(PATH);
	if (false == _file.is_open())
		throw std::domain_error{ std::format("Could not open file at relative path: {}!", PATH) };

	ParseDimensions();
	ReadNextAsGap();
	ParseSprites();

	_file.close();
}

const std::uint32_t SpritesLoader::SpriteHeight() const
{
	return _spriteHeight;
}

const SpritesLoader::Sprite SpritesLoader::GetBy(std::uint32_t face) const
{
	Sprites& sprites = *_sprites;
	return sprites[face-1];
}
#pragma endregion



#pragma region Parsing
void SpritesLoader::ParseDimensions()
{
	std::string line;
	if (std::getline(_file, line))
	{
		std::istringstream stream(line);
		if (stream >> _spriteWidth >> _spriteHeight)
			return;

		std::string message = "Could not read sprite dimensions from file!\n";
		message += "Are they in the right format?\n";
		message += "Format: '{uint: width} {uint:height}' <- Note the whitespace!";
		throw std::domain_error{message};
	}

	throw std::domain_error{ std::format("The file at {} seems to be empty!", PATH) };
}

void SpritesLoader::ParseSprites()
{
	// Sprite height
	//  + 1 for a gap after each sprite
	//  - 1 to ignore last gap
	std::uint32_t iterations = _spriteHeight * (Rules::DIE_SIDES + 1);
	std::uint32_t faceIndex = 0;

	for (std::uint32_t i = 0; i < iterations; ++i)
	{
		if (IsGap(i))
		{
			++faceIndex;
			ReadNextAsGap();
		}
		else
		{
			ReadNextAsRow(faceIndex);
		}
	}
}

bool SpritesLoader::IsGap(std::uint32_t lineIndex)
{
	std::uint32_t divisor = _spriteHeight + 1;
	std::uint32_t dividend = lineIndex >= _spriteHeight
		? lineIndex - _spriteHeight
		: 1;
	return dividend % divisor == 0;
}
#pragma endregion



#pragma region Reading Helpers
void SpritesLoader::ReadNextAsGap()
{
	std::string line;
	if (!std::getline(_file, line))
		throw std::domain_error{"Tried to read a gap, but encountered EOF instead!"};

	if (line.empty())
		return;

	for (const char c : line)
	{
		if(false == std::isspace(c))
			throw std::domain_error{ "Expected a Gap, but encountered non-empty line instead!" };
	}
}

void SpritesLoader::ReadNextAsRow(std::uint32_t faceIndex)
{
	std::string line;
	if (!std::getline(_file, line))
		throw std::domain_error{ "Tried to read a row, but encountered EOF instead!" };

	if (line.size() < _spriteWidth)
	{
		std::string m = std::format(
			"Expected a row with a length of at least {}. Read one of length {} instead!",
			_spriteWidth, line.size());
		throw std::domain_error{ m };
	}

	Sprites& sprites = *_sprites;
	sprites[faceIndex].push_back(line.substr(0, _spriteWidth));
}
#pragma endregion