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

const char* Map::GetWaypointFileHeaderString() const
{
	if (cFormat == Map::FORMAT_SANDBOT)
	{
		return sandbot::WAYPOINT_HEADER;
	}
	else if (cFormat == Map::FORMAT_HPB_BOT)
	{
		return hpb_bot::WAYPOINT_HEADER;
	}
	else if (cFormat == Map::FORMAT_STURMBOT)
	{
		return sturmbot::WAYPOINT_HEADER;
	}
	else
	{
		return nullptr;
	}
}

unsigned int Map::GetMaxWaypoints() const
{
	if( cFormat == Map::FORMAT_SANDBOT )
	{
		return sandbot::MAX_WAYPOINTS;
	}
	else if( cFormat == Map::FORMAT_HPB_BOT )
	{
		// TODO: check
		return 1024;
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

int Map::GetDayOfDefeatControlPointWaypointFlag() const
{
	if (cFormat == Map::FORMAT_SANDBOT)
	{
		return sandbot::W_FL_DOD_CAP;
	}
	else if (cFormat == Map::FORMAT_HPB_BOT)
	{
		// NOTE: HPB_Bot doesn't support Day of Defeat
		return WAYPOINT_FLAG_NOTHING;
	}
	else if (cFormat == Map::FORMAT_STURMBOT)
	{
		// TODO: what is the actual flag?
		return WAYPOINT_FLAG_NOTHING;
	}

	return WAYPOINT_FLAG_NOTHING;
}

bool Map::IsFormatValid() const
{
	return cFormat == Map::FORMAT_SANDBOT || cFormat == Map::FORMAT_HPB_BOT || cFormat == Map::FORMAT_STURMBOT;
}

void Map::WriteWaypointHeader(FILE *pFile, string mapName) const
{
	extern unsigned int num_waypoints;

	if (cFormat == Map::FORMAT_SANDBOT)
	{
		sandbot::WAYPOINT_HDR header;

		strcpy(header.filetype, GetWaypointFileHeaderString());
		header.waypoint_file_version = sandbot::WAYPOINT_VERSION;
		// not currently used
		header.waypoint_file_flags = 0;
		header.number_of_waypoints = num_waypoints;

		memset(header.mapname, 0, sizeof(header.mapname));
		strncpy(header.mapname, mapName.c_str(), 31);
		header.mapname[31] = 0;

		// write the waypoint header to the file...
		fwrite(&header, sizeof(header), 1, pFile);
	}
	else if (cFormat == Map::FORMAT_HPB_BOT || cFormat == Map::FORMAT_STURMBOT)
	{
		hpb_bot::WAYPOINT_HDR header;

		strcpy(header.filetype, GetWaypointFileHeaderString());
		header.waypoint_file_version = hpb_bot::WAYPOINT_VERSION;
		// not currently used
		header.waypoint_file_flags = 0;
		header.number_of_waypoints = num_waypoints;

		memset(header.mapname, 0, sizeof(header.mapname));
		strncpy(header.mapname, mapName.c_str(), 31);
		header.mapname[31] = 0;

		// write the waypoint header to the file...
		fwrite(&header, sizeof(header), 1, pFile);
	}
}

