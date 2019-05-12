//
// BSP_tool - botman's Half-Life BSP utilities
//
// (http://planethalflife.com/botman/)
//
// bsp_tool.cpp
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

#include <stdio.h>
#include <string.h>

#include "cmdlib.h"
#include "config.h"
#include "world.h"
#include "bspfile.h"
#include "waypoint.h"

Config config("BSP_tool.cfg");
World world;

int main (int argc, char **argv)
{
   char filename[256];
   int grid_size;
   bool do_autowaypoint = FALSE;

   if (argc < 2)
   {
      printf("\n");
      printf("usage: BSP_tool -wN bspfile\n");
      printf("\n");
      printf("where: -wN = run autowaypoint on BSP file\n");
      printf("             (where N is the grid size: 64, 72, 80, 100, 120, 150, 200)\n");
      return 1;
   }

   for (int n = 1; n < argc; n++)
   {
      if (strncmp(argv[n], "-w", 2) == 0)
      {
         do_autowaypoint = TRUE;
         if (sscanf(&argv[n][2], "%d", &grid_size) < 1)
            grid_size = 100;  // default to 100 units for grid size
      }
      else
         strcpy(filename, argv[n]);
   }

   printf("%s\n", filename);

   world.LoadBSP(filename);

   if (do_autowaypoint)
      WaypointLevel(grid_size);  // auto waypoint the BSP world

   return 0;
}

