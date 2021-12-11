//
// BSP_tool - botman's Half-Life BSP utilities
//
// (http://planethalflife.com/botman/)
//
// bsp_tool.cpp
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
#include <string.h>

#include "annotation.h"
#include "cmdlib.h"
#include "config.h"
#include "waypoint.h"
#include "world.h"

Config config;
World world;

int main( _In_ int argc, _In_ char **argv )
{
	char szFilename[MAX_PATH];

	if( argc < 2 )
	{
		printf( "Usage: sandbot-wptgen.exe -wN -sS file.bsp\n" );
		printf( "N is the grid size (integer greater than 32)\n" );
		printf( "S is the spawnpoint (e.g. info_player_deathmatch)\n" );

		return 1;
	}

	for( int n = 1; n < argc; n++ )
	{
		const size_t iGridSizeParameterPrefixLength = strlen("-w");
		const size_t iSpawnPointParameterPrefixLength = strlen("-s");

		if( !strncmp(argv[n], "-w", iGridSizeParameterPrefixLength) )
		{
			// if there isn't a valid grid size passed
			if( sscanf( &argv[n][iGridSizeParameterPrefixLength], "%d", &config.iGridSize ) < 1 )
			{
				config.iGridSize = Config::DEFAULT_GRID_SIZE;
			}

			if( config.iGridSize < 32 )
			{
				Config::Warn( "Grid size must be > 32\n" );

				return 1;
			}
		}
		if( !strncmp(argv[n], "-s", iSpawnPointParameterPrefixLength) )
		{
			// if there isn't a spawnpoint passed
			if( sscanf( &argv[n][iSpawnPointParameterPrefixLength], "%s", &config.szSpawnpoint ) < 1 )
			{
				strncpy( config.szSpawnpoint, "info_player_deathmatch", Config::SPAWNPOINT_BUFFER_SIZE);
			}
		}
		else
		{
			strncpy( szFilename, argv[n], MAX_PATH );
		}
	}

	Config::Info( "Processing %s with grid size %u and spawnpoint %s\n", szFilename, config.iGridSize, config.szSpawnpoint );

	const bool bSuccess = world.LoadBSP( szFilename );

	if( !bSuccess )
	{
		Config::Warn( "Unable to open %s\n" );

		return 1;
	}

	WaypointLevel( config );

	return 0;
}
