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

#include "util.h"

string Util::ExtractFileNameWithoutExtension( const string &strPath )
{
	size_t iLastSeparatorIndex = 0;
	size_t iExtensionIndex = string::npos;
	size_t iPathLength = strPath.size();

	for( size_t i = iPathLength; i != 0; i-- )
	{
		if( Util::IsPathSeparator( strPath[i] ) )
		{
			iLastSeparatorIndex = i;
			break;
		}
	}

	for( size_t i = iLastSeparatorIndex + 1; i < iPathLength; i++ )
	{
		if( strPath[i] == '.' )
		{
			iExtensionIndex = i;
			break;
		}
	}

	return strPath.substr( iLastSeparatorIndex + 1, ( iExtensionIndex - 1 - iLastSeparatorIndex ) );
}

bool Util::IsPathSeparator( const char cCharacter ) noexcept
{
	return cCharacter == '\\' || cCharacter == '/';
}