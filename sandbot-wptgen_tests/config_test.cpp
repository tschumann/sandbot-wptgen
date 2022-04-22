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
	};
}
