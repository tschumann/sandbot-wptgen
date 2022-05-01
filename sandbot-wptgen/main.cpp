//=============================================================================
//
// sandbot-wptgen - Sandbot waypoint generator
//
// Based on bsp_tool by Jeffrey "botman" Broome
//
// http://www.teamsandpit.com/
//
// Notes: application entrypoint
//
//=============================================================================

#include <stdio.h>
#include <string.h>

#include "cmdlib.h"
#include "config.h"
#include "waypoint.h"
#include "world.h"
#include "xplatform.h"

Config config;
World world;

int main( _In_ int argc, _In_ char **argv )
{
	char szFilename[FILENAME_MAX];

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
			strncpy( szFilename, argv[n], FILENAME_MAX );
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
