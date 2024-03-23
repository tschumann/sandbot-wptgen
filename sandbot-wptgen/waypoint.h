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
