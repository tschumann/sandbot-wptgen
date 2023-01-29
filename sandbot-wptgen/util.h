//=============================================================================
//
// sandbot-wptgen - Sandbot waypoint generator
//
// Based on BSP_tool by Jeffrey "botman" Broome
//
// http://www.teamsandpit.com/
//
// Notes: utilities class
//
//=============================================================================

#ifndef __UTIL_H__
#define __UTIL_H__

#include "xplatform.h"
#include "string"

using std::string;

class Util final
{
public:
	Util() = delete;

	static string ExtractFileNameWithoutExtension( const string &strPath );

	static bool IsPathSeparator( const char cCharacter ) noexcept;
};

#endif // __UTIL_H__