#include "config.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#undef TEST_METHOD
#define TEST_METHOD(methodName) static const void* test##methodName() { return nullptr; } void methodName()

namespace configtest
{
	TEST_CLASS(configtest)
	{
	public:

		TEST_METHOD(TestTrace)
		{
			Config::Trace( "blah" );
		}
	};
}
