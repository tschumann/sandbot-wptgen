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

Map::Map() noexcept
{
	strncpy( szSpawnpoint, "info_player_deathmatch", SPAWNPOINT_BUFFER_SIZE );
}

bool Map::IsFormatValid() const
{
	return cFormat == Map::FORMAT_SANDBOT || cFormat == Map::FORMAT_HPB_BOT;
}

