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

#ifndef __MAP_H__
#define __MAP_H__

#include "util.h"
#include "xplatform.h"

class Map final
{
public:
	// 4096/-4096 is the real boundary but subtract 1 so that > checks can be used
	constexpr static float MAX_ORIGIN = 4095.0f;
	constexpr static float MIN_ORIGIN = -4095.0f;

	constexpr static int MAP_SIZE = (4095 - -4095) + 1;

	constexpr const static char* DEFAULT_SPAWNPOINT_ENTITY = "info_player_deathmatch";

	const static int ENTITY_NOT_FOUND = -1;

	const static unsigned int DEFAULT_GRID_SIZE = 100;
	const static unsigned int SPAWNPOINT_BUFFER_SIZE = 64;

	const static char FORMAT_SANDBOT = 'S';
	const static char FORMAT_HPB_BOT = 'H';
	const static char FORMAT_STURMBOT = 'U';

	// signed so that it can be negated in waypoint.cpp
	signed int iGridSize = DEFAULT_GRID_SIZE;
	// some games/mods have different spawn point entities for different teams, but the spawn point is just used as a start location
	char szSpawnpoint[SPAWNPOINT_BUFFER_SIZE] = "";
	char cFormat = FORMAT_SANDBOT;

	Map() noexcept;
	Map( const Map& ) = delete;
	Map( Map&& ) = delete;
	Map& operator=( const Map other ) = delete;
	Map& operator=( Map&& other) = delete;

	const char* GetWaypointFileHeaderString() const;
	unsigned int GetMaxWaypoints() const;
	unsigned int GetMaxPathIndexes() const;

	bool IsFormatValid() const;

	void WriteWaypointHeader(FILE* pFile, string fileName) const;
};

#endif // __MAP_H__
