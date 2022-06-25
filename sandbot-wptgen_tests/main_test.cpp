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
			char* argv[4] = { "sandbot.exe", "-w-1", "-sinfo_play_deathmath", "file.bsp" };
			Assert::AreEqual( 1, main( 4, argv ) );
		}

		TEST_METHOD(TestNoSuchMap)
		{
			char* argv[4] = { "sandbot.exe", "-w32", "-sinfo_play_deathmath", "file.bsp" };
			Assert::AreEqual( 1, main( 4, argv ) );
		}

		TEST_METHOD(TestSetSpawnpointEntity)
		{
			char* argv[3] = { "sandbot.exe", "-w32", "-sinfo_player_null" };
			Assert::AreEqual( 1, main( 3, argv ) );
			Assert::IsTrue( !strcmp("info_player_null", config.szSpawnpoint) );
		}
	};
}
