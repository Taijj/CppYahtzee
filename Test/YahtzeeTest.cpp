#include "pch.h"
#include "CppUnitTest.h"
#include "../Main/Model/Model.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace YahtzeeTest
{
	TEST_CLASS(YahtzeeTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Model::Wake();
			Assert::IsTrue(true);
		}
	};	
}
