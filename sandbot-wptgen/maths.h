//=============================================================================
//
// sandbot-wptgen - Sandbot waypoint generator
//
// Based on bsp_tool by Jeffrey "botman" Broome
//
// http://www.teamsandpit.com/
//
// Notes: maths class
//
//=============================================================================

#ifndef __MATHS_H__
#define __MATHS_H__

#include "xplatform.h"

class Maths
{
public:
	static void VectorInvert( _Inout_ float vector[3] );

	template <class T> static T Max( _In_ T a, _In_ T b )
	{
		return (a > b) ? a : b;
	}

	template <class T> static T Min( _In_ T a, _In_ T b )
	{
		return (a < b) ? a : b;
	}
};

#endif // __MATHS_H__