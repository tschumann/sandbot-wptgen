//
// BSP_tool - botman's Half-Life BSP utilities
//
// (http://planethalflife.com/botman/)
//
// world.cpp
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

#include <cstdlib>
#include "cmdlib.h"
#include "bspfile.h"
#include "entity.h"
#include "world.h"
#include "xplatform.h"

World::World()
{
	memset( szMapName, 0, FILENAME_MAX );
}

World::~World()
{
   FreeEntities();

   if (dmodels)
   {
      free(dmodels);
      dmodels = nullptr;
      nummodels = 0;
   }

   if (dvisdata)
   {
      free(dvisdata);
      dvisdata = nullptr;
      visdatasize = 0;
   }

   if (dlightdata)
   {
      free(dlightdata);
      dlightdata = nullptr;
      lightdatasize = 0;
   }

   if (dtexdata)
   {
      free(dtexdata);
      dtexdata = nullptr;
      texdatasize = 0;
   }

   if (dentdata)
   {
      free(dentdata);
      dentdata = nullptr;
      entdatasize = 0;
   }

   if (dleafs)
   {
      free(dleafs);
      dleafs = nullptr;
      numleafs = 0;
   }

   if (dplanes)
   {
      free(dplanes);
      dplanes = nullptr;
      numplanes = 0;
   }

   if (dvertexes)
   {
      free(dvertexes);
      dvertexes = nullptr;
      numvertexes = 0;
   }

   if (dnodes)
   {
      free(dnodes);
      dnodes = nullptr;
      numnodes = 0;
   }

   if (texinfo)
   {
      free(texinfo);
      texinfo = nullptr;
      numtexinfo = 0;
   }

   if (dfaces)
   {
      free(dfaces);
      dfaces = nullptr;
      numfaces = 0;
   }

   if (dclipnodes)
   {
      free(dclipnodes);
      dclipnodes = nullptr;
      numclipnodes = 0;
   }

   if (dedges)
   {
      free(dedges);
      dedges = nullptr;
      numedges = 0;
   }

   if (dmarksurfaces)
   {
      free(dmarksurfaces);
      dmarksurfaces = nullptr;
      nummarksurfaces = 0;
   }

   if (dsurfedges)
   {
      free(dsurfedges);
      dsurfedges = nullptr;
      numsurfedges = 0;
   }
}

bool World::LoadBSP( _In_ const char *pszFilename )
{
	if( strlen( pszFilename ) > 0 )
	{
		// if the file exists
		if( access( pszFilename, 0 ) != -1 )
		{
			char szPathName[FILENAME_MAX];

			strncpy( szMapName, pszFilename, FILENAME_MAX );
			ExtractFilePath( szMapName, szPathName );

			size_t iPathLength = strlen(szPathName);  // remove trailing '/'

			if( iPathLength > 0 )
			{
				szPathName[iPathLength - 1] = 0;
			}

			LoadBSPFile( const_cast<char *>(pszFilename) );

			ParseEntities();

			LoadEntVars();

			return true;
		}
	}

	return false;
}
