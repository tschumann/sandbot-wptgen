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

#include "cmdlib.h"
#include "bspfile.h"
#include "entity.h"
#include "world.h"

World::World()
{
	memset( szMapName, 0, MAX_PATH );
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

void World::LoadBSP( _In_ const char *bspfile )
{
   char pathname[MAX_PATH];
   bool bsp_found;

   bsp_found = false;

   // did we specify a filename on the command line?
   if ((bspfile != nullptr) && (*bspfile != 0))
   {
      strcpy(szMapName, bspfile);

      if (FileTime(szMapName) != -1)  // does the specified file exist?
      {
         LoadBSPFile(szMapName);

         // is this BSP file in a MOD directory?
         ExtractFilePath (szMapName, pathname);

         int len = strlen(pathname);  // remove trailing '/'

         if (len > 0)
            pathname[len-1] = 0;

         bsp_found = true;
      }
   }

   if (!bsp_found)
      Error("Can't load map: %s\n", szMapName);

   ParseEntities();

   LoadEntVars();
}
