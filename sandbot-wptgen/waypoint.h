//
// BSP_tool - botman's Half-Life BSP utilities
//
// (http://planethalflife.com/botman/)
//
// waypoint.h
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

#ifndef __MATHLIB__
#include "mathlib.h"
#endif

#include "maths.h"

// only for wpt.h
typedef vec3_t Vector;

namespace hpb_bot
{
	// adapted from HPB Bot's waypoint.h
	constexpr int MAX_WAYPOINTS = 1024;

	// defines for waypoint flags field (32 bits are available)
	constexpr int  W_FL_TEAM = ((1 << 0) + (1 << 1));  /* allow for 4 teams (0-3) */
	constexpr int  W_FL_TEAM_SPECIFIC = (1 << 2);  /* waypoint only for specified team */
	constexpr int  W_FL_CROUCH = (1 << 3);  /* must crouch to reach this waypoint */
	constexpr int  W_FL_LADDER = (1 << 4);  /* waypoint on a ladder */
	constexpr int  W_FL_LIFT = (1 << 5);  /* wait for lift to be down before approaching this waypoint */
	constexpr int  W_FL_DOOR = (1 << 6);  /* wait for door to open */
	constexpr int  W_FL_HEALTH = (1 << 7);  /* health kit (or wall mounted) location */
	constexpr int  W_FL_ARMOR = (1 << 8);  /* armor (or HEV) location */
	constexpr int  W_FL_AMMO = (1 << 9);  /* ammo location */
	constexpr int  W_FL_SNIPER = (1 << 10); /* sniper waypoint (a good sniper spot) */

	constexpr int  W_FL_TFC_FLAG = (1 << 11); /* flag position (or hostage or president) */
	constexpr int  W_FL_FLF_CAP = (1 << 11); /* Front Line Force capture point */

	constexpr int  W_FL_TFC_FLAG_GOAL = (1 << 12); /* flag return position (or rescue zone) */
	constexpr int  W_FL_FLF_DEFEND = (1 << 12); /* Front Line Force defend point */

	constexpr int  W_FL_PRONE = (1 << 13); /* go prone (laying down) */
	constexpr int  W_FL_AIMING = (1 << 14); /* aiming waypoint */

	constexpr int  W_FL_DELETED = (1 << 31); /* used by waypoint allocation code */

	constexpr int WAYPOINT_VERSION = 4;

	// define the waypoint file header structure...
	typedef struct {
		char filetype[8];  // should be "HPB_bot\0"
		int  waypoint_file_version;
		int  waypoint_file_flags;  // not currently used
		int  number_of_waypoints;
		char mapname[32];  // name of map for these waypoints
	} WAYPOINT_HDR;

	typedef struct {
		int    flags;    // button, lift, flag, health, ammo, etc.
		Vector origin;   // location
	} WAYPOINT;

	constexpr int MAX_PATH_INDEX = 4;

	// define the structure for waypoint paths (paths are connections between
	// two waypoint nodes that indicates the bot can get from point A to point B.
	// note that paths DON'T have to be two-way.  sometimes they are just one-way
	// connections between two points.  There is an array called "paths" that
	// contains head pointers to these structures for each waypoint index.
	typedef struct path {
		short int index[MAX_PATH_INDEX];  // indexes of waypoints (index -1 means not used)
		struct path* next;   // link to next structure
	} PATH;
}

namespace sandbot
{
	// this file is copied directly from Sandbot - could use a git submodule but that would be overkill
	#include "wpt.h"
}

#ifndef WAYPOINT_H
#define WAYPOINT_H

bool CheckWaypoint(const vec3_t &coord, vec3_t new_coord);
void RecursiveFloodFill(const vec3_t &coord);
void WaypointAddEntities(const char *item_name, const int waypoint_flags);
void WaypointAddWallMountedEntities(const char *item_name, const int iWaypointFlags);
void WaypointAddLadders(const int waypoint_flags);
void WaypointLevel( const Map& map );

void WriteSandbotWaypointFile();
void WriteHPB_BotWaypointFile();

#endif
