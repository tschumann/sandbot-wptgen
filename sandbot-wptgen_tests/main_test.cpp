//=============================================================================
//
// sandbot-wptgen - Sandbot waypoint generator
//
// Based on BSP_tool by Jeffrey "botman" Broome
//
// http://www.teamsandpit.com/
//
// Notes: application entrypoint tests
//
//=============================================================================

#include "pch.h"
#include "CppUnitTest.h"

#include "vector"

#include "../sandbot-wptgen/main.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::vector;

namespace maintest
{
	TEST_CLASS(maintest)
	{
	public:

		TEST_METHOD(TestInsufficientArguments)
		{
			vector<const char*> argv = { "sandbot.exe" };
			Assert::AreEqual( EX_USAGE, main( (int)argv.size(), const_cast<char**>(argv.data()) ) );
		}

		TEST_METHOD(TestInvalidGridSize)
		{
			vector<const char*> argv = { "sandbot.exe", "-w-1", "-sinfo_play_deathmath", "file.bsp" };
			Assert::AreEqual( EX_CONFIG, main( (int)argv.size(), const_cast<char**>(argv.data()) ) );
		}

		TEST_METHOD(TestInvalidFormat)
		{
			vector<const char*> argv = { "sandbot.exe", "-fR", "file.bsp" };
			Assert::AreEqual( EX_CONFIG, main( (int)argv.size(), const_cast<char**>(argv.data()) ) );
		}

		TEST_METHOD(TestNoSuchMap)
		{
			vector<const char*> argv = { "sandbot.exe", "-w32", "-sinfo_play_deathmath", "file.bsp" };
			Assert::AreEqual( EX_NOINPUT, main( (int)argv.size(), const_cast<char**>(argv.data()) ) );
		}

		TEST_METHOD(TestSetSpawnpointEntity)
		{
			vector<const char*> argv = { "sandbot.exe", "-w32", "-sinfo_player_null" };
			Assert::AreEqual( EX_NOINPUT, main( (int)argv.size(), const_cast<char **>(argv.data()) ) );
			Assert::IsTrue( !strcmp("info_player_null", map.szSpawnpoint) );
		}
	};
}
