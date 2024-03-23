//=============================================================================
//
// sandbot-wptgen - Sandbot waypoint generator
//
// Based on BSP_tool by Jeffrey "botman" Broome
//
// http://www.teamsandpit.com/
//
// Notes: map class
//
//=============================================================================

#include <cstdarg>
#include <cstdio>
#include <cstring>

#include "map.h"
#include "waypoint.h"

Map::Map() noexcept
{
	strncpy( szSpawnpoint, "info_player_deathmatch", SPAWNPOINT_BUFFER_SIZE );
}

unsigned int Map::GetMaxWaypoints() const
{
	if( cFormat == Map::FORMAT_SANDBOT )
	{
		return sandbot::MAX_WAYPOINTS;
	}
	else if( cFormat == Map::FORMAT_HPB_BOT )
	{
		return 0;
	}
	else
	{
		return 0;
	}
}

unsigned int Map::GetMaxPathIndexes() const
{
	if( cFormat == Map::FORMAT_SANDBOT )
	{
		return sandbot::MAX_PATH_INDEX;
	}
	else if( cFormat == Map::FORMAT_HPB_BOT )
	{
		return 0;
	}
	else
	{
		return 0;
	}
}

bool Map::IsFormatValid() const
{
	return cFormat == Map::FORMAT_SANDBOT || cFormat == Map::FORMAT_HPB_BOT;
}

