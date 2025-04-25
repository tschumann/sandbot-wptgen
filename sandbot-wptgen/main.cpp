//=============================================================================
//
// sandbot-wptgen - Sandbot waypoint generator
//
// Based on BSP_tool by Jeffrey "botman" Broome
//
// http://www.teamsandpit.com/
//
// Notes: application entrypoint
//
//=============================================================================

#include <stdio.h>
#include <string.h>

#include "cmdlib.h"
#include "main.h"
#include "waypoint.h"
#include "world.h"

Map map;
World world;

int main( _In_ int argc, _In_ char **argv )
{
	char szFilename[FILENAME_MAX] = "\0";

	if( __builtin_expect( argc < 2, 0 ) )
	{
		printf( "Usage: sandbot-wptgen.exe -wN -sS -fS file.bsp\n" );
		printf( "-w is the grid size (integer greater than 32)\n" );
		printf( "-s is the spawnpoint (e.g. info_player_deathmatch)\n" );
		printf( "-f is the format (e.g. S for Sandbot, H for HPB_Bot or U for Sturmbot)\n" );

		return EX_USAGE;
	}

	for( int n = 1; n < argc; n++ )
	{
		const size_t iGridSizeParameterPrefixLength = strlen("-w");
		const size_t iSpawnPointParameterPrefixLength = strlen("-s");
		const size_t iFormatParameterPrefixLength = strlen("-f");

		if( !strncmp(argv[n], "-w", iGridSizeParameterPrefixLength) )
		{
			// if there isn't a valid grid size passed
			if( sscanf( &argv[n][iGridSizeParameterPrefixLength], "%d", &map.iGridSize ) < 1 )
			{
				map.iGridSize = Map::DEFAULT_GRID_SIZE;
			}

			if( map.iGridSize < 32 )
			{
				Logger::Warn( "Grid size must be > 32\n" );

				return EX_CONFIG;
			}
		}
		else if( !strncmp(argv[n], "-s", iSpawnPointParameterPrefixLength) )
		{
			// if an empty spawnpoint is passed
			if( sscanf( &argv[n][iSpawnPointParameterPrefixLength], "%s", map.szSpawnpoint ) < 1 )
			{
				strncpy( map.szSpawnpoint, Map::DEFAULT_SPAWNPOINT_ENTITY, Map::SPAWNPOINT_BUFFER_SIZE );
			}
		}
		else if( !strncmp(argv[n], "-f", iFormatParameterPrefixLength) )
		{
			// if an empty format is passed
			if( sscanf( &argv[n][iSpawnPointParameterPrefixLength], "%c", &map.cFormat ) < 1 )
			{
				map.cFormat = Map::FORMAT_SANDBOT;
			}

			if( !map.IsFormatValid() )
			{
				Logger::Warn( "Format must be %c, %c or %c\n", Map::FORMAT_SANDBOT, Map::FORMAT_HPB_BOT, Map::FORMAT_STURMBOT );

				return EX_CONFIG;
			}
		}
		else
		{
			strncpy( szFilename, argv[n], FILENAME_MAX );
			// make sure the string is NULL terminated
			szFilename[FILENAME_MAX - 1] = '\0';
		}
	}

	Logger::Info( "Processing %s with grid size %u and spawnpoint %s\n", szFilename, map.iGridSize, map.szSpawnpoint );

	const bool bSuccess = world.LoadBSP( szFilename );

	if( !bSuccess )
	{
		Logger::Warn( "Unable to open %s\n", szFilename );

		return EX_NOINPUT;
	}

	WaypointLevel( map );

	return EX_OK;
}
