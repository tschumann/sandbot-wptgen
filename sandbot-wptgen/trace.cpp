//
// BSP_tool - botman's Half-Life BSP utilities
//
// (http://planethalflife.com/botman/)
//
// trace.cpp
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

#include <math.h>

#include "bspfile.h"
#include "mathlib.h"
#include "maths.h"
#include "trace.h"

dnode_t *gNode;

// return the leaf node for a point in 3D space...
dleaf_t *TracePointInLeaf(const vec3_t& point)
{
   int      nodenum;
   vec_t    d;
   dnode_t  *node;
   dplane_t *plane;

   nodenum = 0;  // start at the root of the BSP tree

   // walk through the tree to find the leaf for the point...
   while (nodenum >= 0)
   {
      node = &dnodes[nodenum];
      plane = &dplanes[node->planenum];
      d = DotProduct(point, plane->normal) - plane->dist;
      if (d > 0)
         nodenum = node->children[0];
      else
         nodenum = node->children[1];
   }

   gNode = node;
   return &dleafs[-nodenum - 1];
}

// find the contents of a coordinate in 3D space...
int PointContents(const vec3_t& coord)
{
   dleaf_t  *leaf = TracePointInLeaf(coord);

   // return contents (CONTENTS_EMPTY, CONTENTS_SOLID, CONTENTS_WATER, etc.)
   return leaf->contents;
}


// trace a line from start to end, fill in trace_t structure with result...
void TraceLine(const vec3_t& start, vec3_t& end, trace_t *tr)
{
   dleaf_t  *startleaf, *endleaf;
   int      numsteps, totalsteps;
   vec3_t   move, step, position;
   float    dist, trace_dist;

   memset(tr, 0, sizeof(trace_t));

   if ((start[0] < -4095) || (start[0] > 4095) ||
       (start[1] < -4095) || (start[1] > 4095) ||
       (start[2] < -4095) || (start[2] > 4095))
   {
      // start beyond edge of world is INVALID!!!
      Error("TraceLine: start point beyond edge of world!\n");
   }

   if (end[0] > 4095.0f)
   {
      float percent = 4095.0f / end[0];
      end[1] = end[1] * percent;
      end[2] = end[2] * percent;
      end[0] = 4095.0f;
   }

   if (end[1] > 4095.0f)
   {
      float percent = 4095.0f / end[1];
      end[0] = end[0] * percent;
      end[2] = end[2] * percent;
      end[1] = 4095.0f;
   }

   if (end[2] > 4095.0f)
   {
      float percent = 4095.0f / end[2];
      end[0] = end[0] * percent;
      end[1] = end[1] * percent;
      end[2] = 4095.0f;
   }

   if (end[0] < -4095.0f)
   {
      float percent = 4095.0f / end[0];
      end[1] = end[1] * percent;
      end[2] = end[2] * percent;
      end[0] = -4095.0f;
   }

   if (end[1] < -4095.0f)
   {
      float percent = 4095.0f / end[1];
      end[0] = end[0] * percent;
      end[2] = end[2] * percent;
      end[1] = -4095.0f;
   }

   if (end[2] < -4095.0f)
   {
      float percent = 4095.0f / end[2];
      end[0] = end[0] * percent;
      end[1] = end[1] * percent;
      end[2] = -4095.0f;
   }

   // find the starting and ending leafs...
   startleaf = TracePointInLeaf(start);
   endleaf = TracePointInLeaf(const_cast<const vec3_t&>(end));

   // set endpos, fraction and contents to the default (trace completed)
   Maths::Vector_Copy(end, tr->endpos);
   tr->fraction = 1.0f;
   tr->contents = endleaf->contents;

   if (startleaf->contents == CONTENTS_SOLID)
   {
      tr->startsolid = TRUE;

      if (endleaf->contents == CONTENTS_SOLID)
         tr->allsolid = TRUE;
   }

   // is start and end leaf the same (couldn't possibly hit the world)...
   if (startleaf == endleaf)
      return;

   // get the length of each interation of the loop...
   VectorSubtract(end, start, move);
   dist = (float)VectorLength(move);

   // determine the number of steps from start to end...
   if (dist > 1.0f)
      numsteps = totalsteps = (int)dist + 1;
   else
      numsteps = totalsteps = 1;

   // calculate the length of the step vector...
   VectorScale(move, (float)2/numsteps, step);

   Maths::Vector_Copy(start, position);

   while (numsteps)
   {
      VectorAdd(position, step, position);

      endleaf = TracePointInLeaf(position);

      if ((endleaf->contents == CONTENTS_SOLID) ||  // we hit something solid...
          (endleaf->contents == CONTENTS_SKY))      // we hit the sky
      {
         vec3_t hitpos;

		 Maths::Vector_Copy(position, hitpos);

         // store the hit position
		 Maths::Vector_Copy(position, tr->hitpos);

         // back off one step before solid
         VectorSubtract(position, step, position);

         // store the end position and end position contents
		 Maths::Vector_Copy(position, tr->endpos);
         tr->contents = endleaf->contents;

         VectorSubtract(position, start, move);
         trace_dist = (float)VectorLength(move);
         tr->fraction = trace_dist / dist;

         break;  // break out of while loop
      }

      numsteps--;
   }
}