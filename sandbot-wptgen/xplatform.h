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

#if (_WIN32 || _WIN64) && _MSC_VER

// from sysexits.h
#define EX_OK 0
#define EX__BASE 64
#define EX_USAGE 64
#define EX_DATAERR 65
#define EX_NOINPUT 66
#define EX_NOUSER 67
#define EX_NOHOST 68
#define EX_UNAVAILABLE 69
#define EX_SOFTWARE 70
#define EX_OSERR 71
#define EX_OSFILE 72
#define EX_CANTCREAT 73
#define EX_IOERR 74
#define EX_TEMPFAIL 75
#define EX_PROTOCOL 76
#define EX_NOPERM 77
#define EX_CONFIG 78
#define EX__MAX 64

// for access
#include <io.h>

// for _In_
#include <sal.h>

// for _stricmp
#include <string.h>

inline int strcasecmp( const char *string1, const char *string2 )
{
	return _stricmp( string1, string2 );
}

inline long __builtin_expect( long exp, long c )
{
	return exp;
}

#elif __GNUC__

// for EX_OK, EX__BASE, EX_USAGE, EX_DATAERR, EX_NOINPUT, EX_NOUSER, EX_NOHOST, EX_UNAVAILABLE, EX_SOFTWARE, EX_OSERR, EX_OSFILE, EX_CANTCREAT, EX_IOERR, EX_TEMPFAIL, EX_PROTOCOL, EX_NOPERM, EX_CONFIG, EX__MAX
#include <sysexits.h>

// for access
#include <unistd.h>

// from sal.h
#define _In_

#else

#error Unsupported platform

#endif

#endif // __XPLATFORM_H__
