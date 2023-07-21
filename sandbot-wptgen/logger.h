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

#ifndef __LOGGER_H__
#define __LOGGER_H__

#include "xplatform.h"

class Logger final
{
public:
	enum LogLevel
	{
		LOG_NONE = 0,
		LOG_WARN,
		LOG_INFO,
		LOG_TRACE
	};

	Logger() noexcept;
	Logger( const Logger& ) = delete;
	Logger( Logger&& ) = delete;
	Logger& operator=( const Logger other ) = delete;
	Logger& operator=( Logger&& other ) = delete;

	static void Trace( _In_ const char* const szFormat, ... ) noexcept;
	static void Info( _In_ const char* const szFormat, ... ) noexcept;
	static void Warn( _In_ const char* const szFormat, ... ) noexcept;

private:
	const static int LOG_BUFFER_SIZE = 1024;

	LogLevel logLevel;
};

extern Logger logger;

#endif // __LOGGER_H__
