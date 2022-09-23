//=============================================================================
//
// sandbot-wptgen - Sandbot waypoint generator
//
// Based on BSP_tool by Jeffrey "botman" Broome
//
// http://www.teamsandpit.com/
//
// Notes: config class tests
//
//=============================================================================

#include "pch.h"
#include "CppUnitTest.h"

#include "../sandbot-wptgen/config.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace configtest
{
	TEST_CLASS(configtest)
	{
	public:

		TEST_METHOD(TestTrace)
		{
			Config::Trace("blah");
		}

		TEST_METHOD(TestInfo)
		{
			Config::Info("blah");
		}

		TEST_METHOD(TestWarn)
		{
			Config::Warn("blah");
		}
	};
}
