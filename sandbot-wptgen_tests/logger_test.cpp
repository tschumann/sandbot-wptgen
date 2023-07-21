//=============================================================================
//
// sandbot-wptgen - Sandbot waypoint generator
//
// Based on BSP_tool by Jeffrey "botman" Broome
//
// http://www.teamsandpit.com/
//
// Notes: logger class tests
//
//=============================================================================

#include "pch.h"
#include "CppUnitTest.h"

#include "../sandbot-wptgen/logger.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace loggertest
{
	TEST_CLASS(loggertest)
	{
	public:

		TEST_METHOD(TestTrace)
		{
			::Logger::Trace("blah");
		}

		TEST_METHOD(TestInfo)
		{
			::Logger::Info("blah");
		}

		TEST_METHOD(TestWarn)
		{
			::Logger::Warn("blah");
		}
	};
}
