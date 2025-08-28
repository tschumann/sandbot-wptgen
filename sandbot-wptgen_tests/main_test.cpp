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
			Assert::AreEqual( EX_DATAERR, main( (int)argv.size(), const_cast<char **>(argv.data()) ) );
			Assert::IsTrue( !strcmp("info_player_null", map.szSpawnpoint) );
		}

		TEST_METHOD(TestNoSuchWaypointFile)
		{
			vector<const char*> argv = { "sandbot.exe", "file.wpt" };
			Assert::AreEqual( EX_NOINPUT, main( (int)argv.size(), const_cast<char**>(argv.data()) ) );
		}

		TEST_METHOD(TestEmptyWaypointFile)
		{
#ifdef _WIN64
			vector<const char*> argv = { "sandbot.exe", "..\\..\\tests\\wpt\\empty.wpt" };
#else
			vector<const char*> argv = { "sandbot.exe", "..\\tests\\wpt\\empty.wpt" };
#endif // _WIN64
			Assert::AreEqual(EX_NOINPUT, main((int)argv.size(), const_cast<char**>(argv.data())));
		}

		TEST_METHOD(TestTooShortWaypointFile)
		{
#ifdef _WIN64
			vector<const char*> argv = { "sandbot.exe", "..\\..\\tests\\wpt\\short.wpt" };
#else
			vector<const char*> argv = { "sandbot.exe", "..\\tests\\wpt\\short.wpt" };
#endif // _WIN64
			Assert::AreEqual(EX_DATAERR, main((int)argv.size(), const_cast<char**>(argv.data())));
		}

		TEST_METHOD(TestInvalidWaypointFile)
		{
#ifdef _WIN64
			vector<const char*> argv = { "sandbot.exe", "..\\..\\tests\\wpt\\invalid.wpt" };
#else
			vector<const char*> argv = { "sandbot.exe", "..\\tests\\wpt\\invalid.wpt" };
#endif // _WIN64
			Assert::AreEqual(EX_DATAERR, main((int)argv.size(), const_cast<char**>(argv.data())));
		}
	};
}
