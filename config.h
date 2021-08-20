//
// BSP_tool - botman's Half-Life BSP utilities
//
// (http://planethalflife.com/botman/)
//
// config.h
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

#ifndef CONFIG_H
#define CONFIG_H

#include "annotation.h"

#ifdef _WIN32
#include <windows.h>
#else
#define MAX_PATH 256
#endif // _WIN32

class Config
{
public:
	const static int LOG_NONE = 0;
	const static int LOG_WARN = 1;
	const static int LOG_INFO = 2;
	const static int LOG_TRACE = 3;

	const static unsigned int DEFAULT_GRID_SIZE = 100;
	const static unsigned int SPAWNPOINT_BUFFER_SIZE = 64;

	unsigned int iGridSize = DEFAULT_GRID_SIZE;
	char szSpawnpoint[SPAWNPOINT_BUFFER_SIZE] = "";

	Config();

	static void Trace( _In_ const char* fmt, ... );
	static void Info( _In_ const char* fmt, ... );
	static void Warn( _In_ const char* fmt, ... );

private:
	const static int LOG_BUFFER_SIZE = 1024;

	char szPath[MAX_PATH]; // path where the running application resides
	int iLogLevel;
};

#endif
