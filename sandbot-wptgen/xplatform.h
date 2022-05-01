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

#include <sal.h>

#else

// for access
#include <unistd.h>

// from sal.h
#define _In_

#endif // _WIN32

#endif // __XPLATFORM_H__