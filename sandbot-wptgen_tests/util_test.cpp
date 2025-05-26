//=============================================================================
//
// sandbot-wptgen - Sandbot waypoint generator
//
// Based on BSP_tool by Jeffrey "botman" Broome
//
// http://www.teamsandpit.com/
//
// Notes: utilities class tests
//
//=============================================================================

#include "pch.h"
#include "CppUnitTest.h"

#include "../sandbot-wptgen/util.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace utiltest
{
	TEST_CLASS(utiltest)
	{
	public:

		TEST_METHOD(TestExtractFileNameWithoutExtension)
		{
			Assert::AreEqual( string("path"), Util::ExtractFileNameWithoutExtension( "long\\file\\path.txt" ) );
			Assert::AreEqual( string("path"), Util::ExtractFileNameWithoutExtension( "long/file/path.txt" ) );
			Assert::AreEqual( string("path"), Util::ExtractFileNameWithoutExtension( "file/path.txt" ) );
			Assert::AreEqual( string("path"), Util::ExtractFileNameWithoutExtension( "file/path." ) );
			Assert::AreEqual( string("path"), Util::ExtractFileNameWithoutExtension( "file/path" ) );
		}

		TEST_METHOD(TestExtractFileExtension)
		{
			Assert::AreEqual( string("txt"), Util::ExtractFileExtension("long\\file\\path.txt") );
			Assert::AreEqual( string("txt"), Util::ExtractFileExtension("long/file/path.txt") );
			Assert::AreEqual( string("txt"), Util::ExtractFileExtension("file/path.txt") );
			Assert::AreEqual( string(""), Util::ExtractFileExtension("file/path.") );
			Assert::AreEqual( string(""), Util::ExtractFileExtension("file/path") );
		}

		TEST_METHOD(TestIsPathSeparator)
		{
			Assert::IsTrue( Util::IsPathSeparator( '\\' ) );
			Assert::IsTrue( Util::IsPathSeparator( '/' ) );
			Assert::IsFalse( Util::IsPathSeparator( 'a' ) );
			Assert::IsFalse( Util::IsPathSeparator( '.' ) );
			Assert::IsFalse( Util::IsPathSeparator( NULL ) );
		}
	};
}
