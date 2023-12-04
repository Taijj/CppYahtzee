#include "pch.h"
#include "CppUnitTest.h"

#include "../Main/Model/Model.h"

#include <vector>
#include <algorithm>
#include <functional>
#include "Helpers.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace YahtzeeTest
{
	TEST_CLASS(ModelTests)
	{
	public:

		/// <summary>
		/// Can the dice be retrieved from Model and will a throw
		/// result a reference change to a non-zero value?
		/// </summary>
		TEST_METHOD(DiceCanBeThrown)
		{
			Model::Wake();			
			Model::Dice& dice = Model::GetDice();

			for (const auto& d : dice)
				d->Throw();

			for (const auto& d : dice)
			{
				Assert::IsTrue(d->Face() != 0);
			}
		}

		/// <summary>
		/// Will the values resulting from a die throw be
		/// 1. in a range from 1 to the set number of die sides, and
		/// 2. given a large number of samples, will all possible values appear?
		/// </summary>
		TEST_METHOD(DieValuesAreSensible)
		{
			const std::uint32_t samples = 1000;
			std::vector<std::uint32_t> throws;
			Die d = Die{};

			// Throw dice, check for range, and store unique values
			for (std::uint32_t i = 0; i < samples; ++i)
			{
				d.Throw();

				std::uint32_t value = d.Face();
				Assert::IsTrue(value > 0 && value <= Rules::DIE_SIDES);

				auto it = std::find(throws.begin(), throws.end(), value);
				if (it == throws.end())
					throws.push_back(value);
			}

			// Check if all possible values were thrown
			for (std::uint32_t i = 1; i < Rules::DIE_SIDES; i++)
			{
				auto it = std::find(throws.begin(), throws.end(), i);
				Assert::IsTrue(it != throws.end());
			}
		}



		/// <summary>
		/// Are all 13 combos defined in the right order with the right kind?
		/// </summary>
		TEST_METHOD(CombosExist)
		{			
			for (std::uint32_t i = 0; i < Rules::ROUND_COUNT; ++i)
			{
				auto& c = Model::COMBOS[i];				
				Assert::IsTrue(c->Kind() == static_cast<Score::Kind>(i+1));
			}
		}

		/// <summary>
		/// Does the MaxPossibleScore() getter return the right values for all Combos?
		/// </summary>
		TEST_METHOD(CombosHaveCorrectPossibleScores)
		{
			auto check = [](Score::Kind k, std::uint32_t expected)
			{
				const auto& c = Model::COMBOS.at(k - 1);
				const auto is = c->MaxPossibleScore();

				Assert::IsTrue(is == expected, GetMessage(expected, is, static_cast<std::uint32_t>(k)).c_str());
			};

			check(Score::Aces, 5);
			check(Score::Twos, 10);
			check(Score::Threes, 15);
			check(Score::Fours, 20);
			check(Score::Fives, 25);
			check(Score::Sixes, 30);

			check(Score::OfKind3, 30);
			check(Score::OfKind4, 30);
			check(Score::FullHouse, 25);
			check(Score::StraightSmall, 30);
			check(Score::StraightLarge, 40);
			check(Score::Yahtzee, 50);
			check(Score::Chance, 30);
		}

		/// <summary>
		/// Do the Combos from Aces to Sixes return the right score values?
		/// </summary>
		TEST_METHOD(FaceCombosCorrectlyScore)
		{
			using Roll = std::array<std::uint32_t, Rules::DIE_COUNT>;

			auto check = [](Roll r, const Combo& c, std::uint32_t expected)
			{
				std::uint32_t score = c.Score(r);				
				Assert::IsTrue(score == expected,
					GetMessage(expected, score, static_cast<std::uint32_t>(c.Kind())).c_str());
			};

			const auto& aces = Model::COMBOS.at(0);
			const auto& twos = Model::COMBOS.at(1);
			const auto& threes = Model::COMBOS.at(2);
			const auto& fours = Model::COMBOS.at(3);
			const auto& fives = Model::COMBOS.at(4);
			const auto& sixes = Model::COMBOS.at(5);

			Roll r1 = { 1, 2, 3, 4, 5 };
			check(r1, *aces, 1);
			check(r1, *twos, 2);
			check(r1, *threes, 3);
			check(r1, *fours, 4);
			check(r1, *fives, 5);
			check(r1, *sixes, 0);

			Roll r2 = { 3, 2, 3, 4, 3 };
			check(r2, *aces, 0);
			check(r2, *twos, 2);
			check(r2, *threes, 9);
			check(r2, *fours, 4);
			check(r2, *fives, 0);
			check(r2, *sixes, 0);

			// TODO: More tests
		}
	};
}
