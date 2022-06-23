//=============================================================================
//
// sandbot-wptgen - Sandbot waypoint generator
//
// Based on bsp_tool by Jeffrey "botman" Broome
//
// http://www.teamsandpit.com/
//
// Notes: application entrypoint tests
//
//=============================================================================

#include "pch.h"
#include "CppUnitTest.h"

#include "../sandbot-wptgen/main.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace maintest
{
	TEST_CLASS(maintest)
	{
	public:

		TEST_METHOD(TestInsufficientArguments)
		{
			char* argv[1] = { "sandbot.exe" };
			Assert::AreEqual( 1, main( 1, argv ) );
		}

		TEST_METHOD(TestInvalidGridSize)
		{
			char* argv[3] = { "sandbot.exe", "-w", "-1" };
			Assert::AreEqual( 1, main( 1, argv ) );
		}

		TEST_METHOD(TestNoSuchMap)
		{
			char* argv[2] = { "sandbot.exe", "file.bsp" };
			Assert::AreEqual( 1, main( 1, argv ) );
		}
	};
}
