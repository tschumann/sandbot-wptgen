//=============================================================================
//
// sandbot-wptgen - Sandbot waypoint generator
//
// Based on BSP_tool by Jeffrey "botman" Broome
//
// http://www.teamsandpit.com/
//
// Notes: config class
//
//=============================================================================

#include <cstdarg>
#include <cstdio>
#include <cstring>

#include "config.h"

Config::Config()
{
	strncpy( szSpawnpoint, "info_player_deathmatch", SPAWNPOINT_BUFFER_SIZE );

#if _DEBUG
	logLevel = LogLevel::LOG_TRACE;
#else
	logLevel = LogLevel::LOG_INFO;
#endif
}

extern Config config;

void Config::Trace( _In_ const char* szFormat, ... )
{
	if( config.logLevel >= LogLevel::LOG_TRACE )
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
	if( config.logLevel >= LogLevel::LOG_INFO )
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
	if( config.logLevel >= LogLevel::LOG_WARN )
	{
		va_list argptr;
		static char szString[LOG_BUFFER_SIZE];

		va_start( argptr, szFormat );
		vsprintf( szString, szFormat, argptr );
		va_end( argptr );

		printf( "%s", szString );
	}
}
