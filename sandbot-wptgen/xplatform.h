//=============================================================================
//
// sandbot-wptgen - Sandbot waypoint generator
//
// Based on bsp_tool by Jeffrey "botman" Broome
//
// http://www.teamsandpit.com/
//
// Notes: platform-specific code
//
//=============================================================================

#ifndef __XPLATFORM_H__
#define __XPLATFORM_H__

#ifdef _WIN32

// for access
#include <io.h>

// for _In_
#include <sal.h>

inline long __builtin_expect( long exp, long c )
{
	return exp;
}

#elif __GNUC__

// for access
#include <unistd.h>

// from sal.h
#define _In_

#else

#error Unsupported platform

#endif

#endif // __XPLATFORM_H__