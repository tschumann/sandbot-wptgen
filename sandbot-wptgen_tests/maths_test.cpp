//=============================================================================
//
// sandbot-wptgen - Sandbot waypoint generator
//
// Based on bsp_tool by Jeffrey "botman" Broome
//
// http://www.teamsandpit.com/
//
// Notes: maths class tests
//
//=============================================================================

#include "pch.h"
#include "CppUnitTest.h"

#include "../sandbot-wptgen/maths.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace configtest
{
	TEST_CLASS(mathstest)
	{
	public:

		TEST_METHOD(TestVectorCopy)
		{
			float source[3] = { 1.0f, 1.0f, 1.0f };
			float destination[3] = { 0.0f, 0.0f, 0.0f };
			Maths::Vector_Copy( source, destination );
			Assert::AreEqual( source[0], destination[0] );
			Assert::AreEqual( source[1], destination[1] );
			Assert::AreEqual( source[2], destination[2] );
		}

		TEST_METHOD(TestVectorInvertPositive)
		{
			float vector[3] = { 1.0f, 1.0f, 1.0f };
			Maths::VectorInvert( vector );
			Assert::AreEqual( -1.0f, vector[0] );
			Assert::AreEqual( -1.0f, vector[1] );
			Assert::AreEqual( -1.0f, vector[2] );
		}

		TEST_METHOD(TestVectorInvertNegative)
		{
			float vector[3] = { -1.0f, -1.0f, -1.0f };
			Maths::VectorInvert( vector );
			Assert::AreEqual( 1.0f, vector[0] );
			Assert::AreEqual( 1.0f, vector[1] );
			Assert::AreEqual( 1.0f, vector[2] );
		}

		TEST_METHOD(TestMaxMaximum)
		{
			Assert::AreEqual( 1, Maths::Max( 1, 0 ) );
		}

		TEST_METHOD(TestMaxMinimum)
		{
			Assert::AreEqual( 1, Maths::Max( 0, 1) );
		}

		TEST_METHOD(TestMaxEqual)
		{
			Assert::AreEqual( 1, Maths::Max( 1, 1 ) );
		}

		TEST_METHOD(TestMinMaximum)
		{
			Assert::AreEqual( 0, Maths::Min( 1, 0 ) );
		}

		TEST_METHOD(TestMinMinimum)
		{
			Assert::AreEqual( 0, Maths::Min( 0, 1 ) );
		}

		TEST_METHOD(TestMinEqual)
		{
			Assert::AreEqual( 1, Maths::Min( 1, 1 ) );
		}
	};
}
