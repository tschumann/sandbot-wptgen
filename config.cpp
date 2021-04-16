//
// BSP_tool - botman's Half-Life BSP utilities
//
// (http://planethalflife.com/botman/)
//
// config.cpp
//
// Copyright (C) 2001 - Jeffrey "botman" Broome
//
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
//
// See the GNU General Public License for more details at:
// http://www.gnu.org/copyleft/gpl.html
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#include <stdio.h>

#include "config.h"

Config::Config()
{
	strncpy( szSpawnpoint, "info_player_deathmatch", SPAWNPOINT_BUFFER_SIZE);

#if _DEBUG
	iLogLevel = LOG_TRACE;
#else
	iLogLevel = LOG_INFO;
#endif
}

extern Config config;

void Config::Trace( _In_ const char* szFormat, ... )
{
	if( config.iLogLevel >= Config::LOG_TRACE )
	{
		va_list argptr;
		static char szString[LOG_BUFFER_SIZE];

		va_start( argptr, szFormat );
		vsprintf( szString, szFormat, argptr );
		va_end( argptr );

		printf( "%s", szString );
	}
}

void Config::Info( _In_ const char* szFormat, ... )
{
	if( config.iLogLevel >= Config::LOG_INFO )
	{
		va_list argptr;
		static char szString[LOG_BUFFER_SIZE];

		va_start( argptr, szFormat );
		vsprintf( szString, szFormat, argptr );
		va_end( argptr );

		printf( "%s", szString );
	}
}

void Config::Warn( _In_ const char* szFormat, ... )
{
	if( config.iLogLevel >= Config::LOG_WARN )
	{
		va_list argptr;
		static char szString[LOG_BUFFER_SIZE];

		va_start( argptr, szFormat );
		vsprintf( szString, szFormat, argptr );
		va_end( argptr );

		printf( "%s", szString );
	}
}
