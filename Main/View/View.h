#pragma once

#include <cstdint>
#include <string>
#include <format>
#include <vector>
#include <memory>

#include "SpritesLoader.h"

class View
{
public:

	using uInt = std::uint32_t;
	using string = std::string;

	struct DieData
	{
		uInt id;
		uInt face;
		bool isLocked;
	};

	struct ComboData
	{
		string name;
		uInt score;
	};

	using DieDatas = std::vector<DieData>;
	using ComboDatas = std::vector<ComboData>;



	View() = delete;
	static void Wake();


	static void RenderWelcome();
	static void RenderInitialPhase();
	static void RenderRoundHeader(uInt roundIndex, uInt playerId);	
	static void RenderTable(DieDatas dice, ComboDatas combos);

	static void Clear();
	static void RenderInvalidInput();



private: 
	
	inline static const string CLEAR_ALL = "\x1B[2J\x1B[1;1H";
	inline static const string CLEAR_LINE = "\x1B[1A\x1B[2K";

	inline static const string INDENT = "  ";	
	inline static const string EMPTY = "--";
	
	inline static const string YOUR_INPUT = "# Your Input: ";
	inline static const string INVALID_INPUT = "# INVALID INPUT! Please try again: ";	



	inline static std::unique_ptr<SpritesLoader> _sprites;
	inline static DieDatas _dice;
	inline static ComboDatas _combos;



	// Helpers for Table rendering
	inline static constexpr uInt TABLE_LABEL_WIDTH = 10U;
	inline static constexpr uInt TABLE_COMBO_NAME_WIDTH = 12U;
	inline static constexpr uInt TABLE_COMBO_SCORE_WIDTH = 3U;
	inline static constexpr uInt TABLE_DIE_WIDTH = 7U;

	static void RenderLabelCell(uInt row);
	static void RenderComboCell(uInt row);
	static void RenderDieCell(uInt row, uInt column);
	static void RenderCell(uInt width, string message = "");
};