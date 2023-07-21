//=============================================================================
//
// sandbot-wptgen - Sandbot waypoint generator
//
// Based on BSP_tool by Jeffrey "botman" Broome
//
// http://www.teamsandpit.com/
//
// Notes: logger class
//
//=============================================================================

#include <cstdarg>
#include <cstdio>

#include "logger.h"

Logger logger;

Logger::Logger() noexcept :
#if _DEBUG
	logLevel(LogLevel::LOG_TRACE)
#else
	logLevel(LogLevel::LOG_INFO)
#endif // _DEBUG
{
}

void Logger::Trace( _In_ const char* const szFormat, ... ) noexcept
{
	if( logger.logLevel >= LogLevel::LOG_TRACE )
	{
		va_list argptr;
		static char szString[LOG_BUFFER_SIZE];

		va_start( argptr, szFormat );
		vsprintf( szString, szFormat, argptr );
		va_end( argptr );

		printf( "%s", szString );
	}
}

void Logger::Info( _In_ const char* const szFormat, ... ) noexcept
{
	if( logger.logLevel >= LogLevel::LOG_INFO )
	{
		va_list argptr;
		static char szString[LOG_BUFFER_SIZE];

		va_start( argptr, szFormat );
		vsprintf( szString, szFormat, argptr );
		va_end( argptr );

		printf( "%s", szString );
	}
}

void Logger::Warn( _In_ const char* const szFormat, ... ) noexcept
{
	if( logger.logLevel >= LogLevel::LOG_WARN )
	{
		va_list argptr;
		static char szString[LOG_BUFFER_SIZE];

		va_start( argptr, szFormat );
		vsprintf( szString, szFormat, argptr );
		va_end( argptr );

		printf( "%s", szString );
	}
}
