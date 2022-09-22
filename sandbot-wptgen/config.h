//=============================================================================
//
// sandbot-wptgen - Sandbot waypoint generator
//
// Based on bsp_tool by Jeffrey "botman" Broome
//
// http://www.teamsandpit.com/
//
// Notes: config class
//
//=============================================================================

#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "xplatform.h"

class Config
{
public:
	enum LogLevel
	{
		LOG_NONE = 0,
		LOG_WARN,
		LOG_INFO,
		LOG_TRACE
	};

	const static unsigned int DEFAULT_GRID_SIZE = 100;
	const static unsigned int SPAWNPOINT_BUFFER_SIZE = 64;

	// signed so that it can be negated in waypoint.cpp
	signed int iGridSize = DEFAULT_GRID_SIZE;
	char szSpawnpoint[SPAWNPOINT_BUFFER_SIZE] = "";

	Config();

	static void Trace( _In_ const char* fmt, ... );
	static void Info( _In_ const char* fmt, ... );
	static void Warn( _In_ const char* fmt, ... );

private:
	const static int LOG_BUFFER_SIZE = 1024;

	LogLevel logLevel;
};

#endif // __CONFIG_H__
