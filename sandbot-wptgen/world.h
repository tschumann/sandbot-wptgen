//
// BSP_tool - botman's Half-Life BSP utilities
//
// (http://planethalflife.com/botman/)
//
// world.h
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

#ifndef WORLD_H
#define WORLD_H

#include "xplatform.h"

class World final
{
public:
	// 4096/-4096 is the real boundary but subtract 1 so that > checks can be used
	constexpr static float MAX_ORIGIN = 4095.0f;
	constexpr static float MIN_ORIGIN = -4095.0f;

	constexpr static int MAP_SIZE = (4095 - -4095) + 1;

	World() noexcept;
	~World() noexcept;

	bool LoadBSP( _In_ const char * pszFilename );

	char szMapName[FILENAME_MAX];
};

#endif // WORLD_H
