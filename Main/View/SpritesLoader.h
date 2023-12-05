#pragma once

#include <array>
#include <vector>
#include <string>

#include <memory>
#include <fstream>

#include "../Global/Rules.h"

/// <summary>
/// Helper class that loads a graphical representation of the game dice
/// from a file. The Sprites are parsed and processed for easy later
/// output on the console.
/// </summary>
class SpritesLoader
{
public:

	using Sprite = std::vector<std::string>;
	using Sprites = std::array<Sprite, Rules::DIE_SIDES>;

	SpritesLoader() = default;
	~SpritesLoader() = default;

	/// <summary>
	/// Tries to read sprites for each possible die face
	/// from a file defined by PATH. Throws exceptions, if
	/// something goes wrong.
	/// </summary>
	void LoadSprites();

	/// <summary>
	/// Returns the height in rows every sprite has, without
	/// gaps.
	/// </summary>
	const std::uint32_t SpriteHeight() const;

	/// <summary>
	/// Returns a vector containing all rows of characters that
	/// make up the sprite by the given face value.
	/// </summary>
	const Sprite GetBy(std::uint32_t face) const;

private:

	inline static const std::string PATH = "Resources/Sprites.txt";

	std::uint32_t _spriteWidth;
	std::uint32_t _spriteHeight;
	
	std::ifstream _file;
	std::unique_ptr<Sprites> _sprites;
		
	/// <summary>
	/// Tries to parse the widht and height, defined in the
	/// definition file and stores them.
	/// </summary>
	void ParseDimensions();	

	/// <summary>
	/// Tries to parse all the sprites for the die faces and
	/// stores them.
	/// </summary>
	void ParseSprites();

	/// <summary>
	/// Reads the next line from file and checks, if it is a valid
	/// separator "Gap. Will throw an exception, if not.
	/// </summary>
	void ReadNextAsGap();

	/// <summary>
	/// Reads the next line and tries to store it as a row of the die
	/// sprite with the given face value. Will thrwo an exception if
	/// something goes wrong.
	/// </summary>
	void ReadNextAsRow(std::uint32_t faceIndex);	

	/// <summary>
	/// The expected file structure contains an empty "gap" after each
	/// sprite. This method performs calculations and checks to determine,
	/// if there should be a gap at that line index.
	/// </summary>
	bool IsGap(std::uint32_t lineIndex);
};


