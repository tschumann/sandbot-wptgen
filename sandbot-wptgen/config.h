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
	const static int LOG_NONE = 0;
	const static int LOG_WARN = 1;
	const static int LOG_INFO = 2;
	const static int LOG_TRACE = 3;

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

	char szPath[FILENAME_MAX]; // path where the running application resides
	int iLogLevel;
};

#endif // __CONFIG_H__
