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

#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "xplatform.h"

class Config final
{
public:
	enum LogLevel
	{
		LOG_NONE = 0,
		LOG_WARN,
		LOG_INFO,
		LOG_TRACE
	};

	Config() noexcept;
	Config( const Config& ) = delete;
	Config& operator=( Config other ) = delete;

	static void Trace( _In_ const char* const szFormat, ... ) noexcept;
	static void Info( _In_ const char* const szFormat, ... ) noexcept;
	static void Warn( _In_ const char* const szFormat, ... ) noexcept;

private:
	const static int LOG_BUFFER_SIZE = 1024;

	LogLevel logLevel;
};

#endif // __CONFIG_H__
