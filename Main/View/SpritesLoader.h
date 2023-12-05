#pragma once

#include <array>
#include <vector>
#include <string>

#include <memory>
#include <fstream>

#include "../Global/Rules.h"

class SpritesLoader
{
public:

	using Sprite = std::vector<std::string>;
	using Sprites = std::array<Sprite, Rules::DIE_SIDES>;

	SpritesLoader() = default;
	~SpritesLoader() = default;

	void LoadSprites();
	const Sprite GetBy(std::uint32_t face) const;

private:

	inline static const std::string PATH = "Resources/Sprites.txt";

	std::uint32_t _spriteWidth;
	std::uint32_t _spriteHeight;
	
	std::ifstream _file;
	std::unique_ptr<Sprites> _sprites;
		
	void ParseDimensions();
	void ParseSprites();

	void ReadNextAsGap();
	void ReadNextAsRow(std::uint32_t faceIndex);

	bool IsGap(std::uint32_t lineIndex);
};


