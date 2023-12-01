#include "pch.h"
#include "CppUnitTest.h"
#include "../Main/Model/Model.h"

#include <vector>
#include <algorithm>

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
				Assert::IsTrue(d->Value() != 0);
		}

		/// <summary>
		/// Will the values resulting from a die throw be
		/// 1. in a range from 1 to the set number of die sides, and
		/// 2. given a large number of samples, will all possible values appear
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

				std::uint32_t value = d.Value();
				Assert::IsTrue(value > 0 && value <= Die::SIDES);

				auto it = std::find(throws.begin(), throws.end(), value);
				if (it == throws.end())
					throws.push_back(value);
			}

			// Check if all possible values were thrown
			for (std::uint32_t i = 1; i < Die::SIDES; i++)
			{
				auto it = std::find(throws.begin(), throws.end(), i);
				Assert::IsTrue(it != throws.end());
			}
		}
	};
}
