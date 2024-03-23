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

#include "xplatform.h"

class Map final
{
public:
	// 4096/-4096 is the real boundary but subtract 1 so that > checks can be used
	constexpr static float MAX_ORIGIN = 4095.0f;
	constexpr static float MIN_ORIGIN = -4095.0f;

	constexpr static int MAP_SIZE = (4095 - -4095) + 1;

	const static int ENTITY_NOT_FOUND = -1;

	const static unsigned int DEFAULT_GRID_SIZE = 100;
	const static unsigned int SPAWNPOINT_BUFFER_SIZE = 64;

	const static char FORMAT_SANDBOT = 'S';
	const static char FORMAT_HPB_BOT = 'H';

	// signed so that it can be negated in waypoint.cpp
	signed int iGridSize = DEFAULT_GRID_SIZE;
	char szSpawnpoint[SPAWNPOINT_BUFFER_SIZE] = "";
	char cFormat = FORMAT_SANDBOT;

	Map() noexcept;
	Map( const Map& ) = delete;
	Map( Map&& ) = delete;
	Map& operator=( const Map other ) = delete;
	Map& operator=( Map&& other) = delete;

	unsigned int GetMaxWaypoints() const;
	unsigned int GetMaxPathIndexes() const;

	bool IsFormatValid() const;
};

#endif // __MAP_H__
