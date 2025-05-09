//
// BSP_tool - botman's Half-Life BSP utilities
//
// (http://planethalflife.com/botman/)
//
// waypoint.cpp
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
#include <stack>

#include "bspfile.h"
#include "trace.h"
#include "util.h"
#include "logger.h"
#include "map.h"
#include "waypoint.h"
#include "world.h"

// the size of the 3 dimensional array allocated to store visited and waypoint locations
int array_size;

// array of bits to store whether this point has been visited or not...
unsigned char *visited;

// array of bits to store whether this is a waypoint location or not...
unsigned char *waypoint_loc;

int location_count;

sandbot::waypoint_t sandbotWaypoints[sandbot::MAX_WAYPOINTS];
hpb_bot::WAYPOINT hpbbotWaypoints[hpb_bot::MAX_WAYPOINTS];
unsigned int num_waypoints;

bool overflow;  // flag to indicate too many waypoints

sandbot::path_t **paths;  // pointer to array of paths (one linked list per waypoint)

vec3_t level_min, level_max;  // min and max coordinates of map

extern Logger logger;
extern Map map;
extern World world;

vec3_t spawn_point;


vec3_t forward, back, left, right, up, down;
vec3_t down_to_ground, up_off_floor;

// stacks for the floodfill recursion...
std::stack <float> S0, S1, S2;


void WaypointAdd(const vec3_t &origin, int flags, bool ignore_loc)
{
   int x_index, y_index, z_index, offset;

   // convert origin to integer array indexes...
   x_index = (int)(origin[0] + Map::MAX_ORIGIN) / map.iGridSize;
   y_index = (int)(origin[1] + Map::MAX_ORIGIN) / map.iGridSize;
   z_index = (int)(origin[2] + Map::MAX_ORIGIN) / map.iGridSize;

   offset = x_index * array_size * array_size + y_index * array_size + z_index;
   offset = offset >> 3;

   // is there NOT a waypoint already at this location?
   if (!(waypoint_loc[offset] & (1<<(z_index & 7))) || (ignore_loc))
   {
      waypoint_loc[offset] |= (1<<(z_index & 7));

      if (num_waypoints < map.GetMaxWaypoints())
      {
		  sandbotWaypoints[num_waypoints].flags = flags;

		  sandbotWaypoints[num_waypoints].origin[0] = origin[0];
		  sandbotWaypoints[num_waypoints].origin[1] = origin[1];
		  sandbotWaypoints[num_waypoints].origin[2] = origin[2];

         num_waypoints++;
      }
      else
      {
         overflow = TRUE;
      }
   }
}

// hopefully add a waypoint at the specified location
bool CheckWaypoint(const vec3_t &coord, vec3_t new_coord)
{
   vec3_t start, end;
   trace_t tr;

   static vec3_t wall_forward = {20, 0, 0};
   static vec3_t wall_back = {-20, 0, 0};
   static vec3_t wall_left = {0, 20, 0};
   static vec3_t wall_right = {0, -20, 0};

   // check if this coordinate is outside the bounds of the map...
   if ((coord[0] < level_min[0]) || (coord[0] > level_max[0]) ||
       (coord[1] < level_min[1]) || (coord[1] > level_max[1]) ||
       (coord[2] < level_min[2]) || (coord[2] > level_max[2]))
   {
      return FALSE;
   }

   VectorCopy(coord, start);

   // adjust so that we aren't too close to any walls (forward)...
   VectorAdd(start, wall_forward, end);
   TraceLine(start, end, &tr);

   if (tr.fraction < 1.0)  // did we hit a wall?
      VectorAdd(tr.endpos, wall_back, start);  // adjust, create new start

   // adjust so that we aren't too close to any walls (back)...
   VectorAdd(start, wall_back, end);
   TraceLine(start, end, &tr);

   if (tr.fraction < 1.0)  // did we hit a wall?
      VectorAdd(tr.endpos, wall_forward, start);  // adjust, create new start

   // adjust so that we aren't too close to any walls (left)...
   VectorAdd(start, wall_left, end);
   TraceLine(start, end, &tr);

   if (tr.fraction < 1.0)  // did we hit a wall?
      VectorAdd(tr.endpos, wall_right, start);  // adjust, create new start

   // adjust so that we aren't too close to any walls (right)...
   VectorAdd(start, wall_right, end);
   TraceLine(start, end, &tr);

   if (tr.fraction < 1.0)  // did we hit a wall?
      VectorAdd(tr.endpos, wall_left, start);  // adjust, create new start

   // save the wall adjusted position as new origin...
   VectorCopy(start, new_coord);

   // if waypoint is in lava then just return
   if (PointContents(start) == CONTENTS_LAVA)
      return TRUE;

   // if we aren't in water, then trace down to find the "floor"
   if (PointContents(start) != CONTENTS_WATER)
   {
      // trace downward to find the ground from here...
      VectorAdd(start, down_to_ground, end);
      TraceLine(start, end, &tr);

      if (tr.fraction < 1.0)  // did we hit ground?
      {
         // is the end point in lava?
         if (PointContents(tr.endpos) == CONTENTS_LAVA)
            return TRUE;

         // raise up off of floor (or ledge) to center of player model...
         VectorAdd(tr.endpos, up_off_floor, end);

		 Logger::Trace( "Added a waypoint at (%f, %f, %f)\n", end[0], end[1], end[2] );
         WaypointAdd(end, 0, FALSE);
      }
   }
   else
   {
      WaypointAdd(start, 0, FALSE);
   }

   return TRUE;
}


void RecursiveFloodFill(const vec3_t &coord)
{
   vec3_t origin, new_origin, end;
   int x_index, y_index, z_index, offset;
   trace_t tr;

   S0.push(coord[0]);  // push X, Y, and Z
   S1.push(coord[1]);
   S2.push(coord[2]);

   Logger::Info( "Starting RecursiveFloodFill from (%f, %f, %f)\n", coord[0], coord[1], coord[2] );

   while (!S0.empty())  // while there is something on the stack...
   {
      // get the current origin from the top of the stack...
      origin[0] = S0.top();
      origin[1] = S1.top();
      origin[2] = S2.top();

      // check if this origin is outside the world boundries...
      if ((origin[0] < Map::MIN_ORIGIN) || (origin[0] > Map::MAX_ORIGIN) ||
          (origin[1] < Map::MIN_ORIGIN) || (origin[1] > Map::MAX_ORIGIN) ||
          (origin[2] < Map::MIN_ORIGIN) || (origin[2] > Map::MAX_ORIGIN))
      {
         printf("RecursiveFloodFill went outside the world at %7.2f %7.2f %7.2f\n", origin[0], origin[1], origin[2]);
         exit(1);
      }

      // convert origin to integer array indexes...
      x_index = (int)(origin[0] + Map::MAX_ORIGIN) / map.iGridSize;
      y_index = (int)(origin[1] + Map::MAX_ORIGIN) / map.iGridSize;
      z_index = (int)(origin[2] + Map::MAX_ORIGIN) / map.iGridSize;

      offset = x_index * array_size * array_size + y_index * array_size + z_index;
      offset = offset >> 3;

      // have we already visited this location?
      if (visited[offset] & (1<<(z_index & 7)))
      {
         // pop the current location off the stack...
         S0.pop();
         S1.pop();
         S2.pop();
         continue;  // go back to the top of the while loop
      }

      // mark this location as visited (so we don't visit it again)
      visited[offset] |= (1<<(z_index & 7));

      location_count++;
      if ((location_count % 1000) == 0)
      {
         printf("\rLocations visited: %d", location_count);
         fflush(stdout);
      }

      // trace a line in the forward direction...
      VectorAdd(origin, forward, end);
      TraceLine(origin, end, &tr);

      // did the trace complete without hitting anything?
      if (tr.fraction >= 1.0)
      {
         if (CheckWaypoint(tr.endpos, new_origin))
         {
            // add this point to the origins that need to be checked
            S0.push(new_origin[0]);
            S1.push(new_origin[1]);
            S2.push(new_origin[2]);
         }
      }

      // trace a line in the backward direction...
      VectorAdd(origin, back, end);
      TraceLine(origin, end, &tr);

      // did the trace complete without hitting anything?
      if (tr.fraction >= 1.0)
      {
         if (CheckWaypoint(tr.endpos, new_origin))
         {
            // add this point to the origins that need to be checked
            S0.push(new_origin[0]);
            S1.push(new_origin[1]);
            S2.push(new_origin[2]);
         }
      }

      // trace a line in the left-ward direction...
      VectorAdd(origin, left, end);
      TraceLine(origin, end, &tr);

      // did the trace complete without hitting anything?
      if (tr.fraction >= 1.0)
      {
         if (CheckWaypoint(tr.endpos, new_origin))
         {
            // add this point to the origins that need to be checked
            S0.push(new_origin[0]);
            S1.push(new_origin[1]);
            S2.push(new_origin[2]);
         }
      }

      // trace a line in the right-ward direction...
      VectorAdd(origin, right, end);
      TraceLine(origin, end, &tr);

      // did the trace complete without hitting anything?
      if (tr.fraction >= 1.0)
      {
         if (CheckWaypoint(tr.endpos, new_origin))
         {
            // add this point to the origins that need to be checked
            S0.push(new_origin[0]);
            S1.push(new_origin[1]);
            S2.push(new_origin[2]);
         }
      }

      // trace a line in the upward direction...
      VectorAdd(origin, up, end);
      TraceLine(origin, end, &tr);

      // did the trace complete without hitting anything?
      if (tr.fraction >= 1.0)
      {
         if (CheckWaypoint(tr.endpos, new_origin))
         {
            // add this point to the origins that need to be checked
            S0.push(new_origin[0]);
            S1.push(new_origin[1]);
            S2.push(new_origin[2]);
         }
      }

      // trace a line in the downward direction...
      VectorAdd(origin, down, end);
      TraceLine(origin, end, &tr);

      // did the trace complete without hitting anything?
      if (tr.fraction >= 1.0)
      {
         if (CheckWaypoint(tr.endpos, new_origin))
         {
            // add this point to the origins that need to be checked
            S0.push(new_origin[0]);
            S1.push(new_origin[1]);
            S2.push(new_origin[2]);
         }
      }
   }
}


void WaypointAddEntities(const char *item_name, const int iWaypointFlags)
{
	const char *value;
	vec3_t origin, start, end;
	const vec3_t vAboveEntity = { 0.0f, 0.0f, 10.0f };
	trace_t tr;

	const unsigned int iEntityNameLength = strlen(item_name);
	int iEntityIndex = Map::ENTITY_NOT_FOUND;

	while ((iEntityIndex = FindEntityByWildcard(iEntityIndex, item_name, iEntityNameLength)) != Map::ENTITY_NOT_FOUND)
	{
		value = ValueForKey(&entities[iEntityIndex], "origin");
		if (value[0])
		{
			sscanf(value, "%f %f %f", &origin[0], &origin[1], &origin[2]);

			Maths::Vector_Add( origin, vAboveEntity, start );

			// trace downward to find the ground from here
			Maths::Vector_Add( start, down_to_ground, end );
			TraceLine(start, end, &tr);

			if (tr.fraction < 1.0)  // did we hit ground?
			{
				// raise up off of floor (or ledge) to center of player model
				Maths::Vector_Add( tr.endpos, up_off_floor, end );

				WaypointAdd(end, iWaypointFlags, TRUE);
			}
		}
	}
}


void WaypointAddWallMountedEntities(const char *item_name, const int waypoint_flags)
{
   const char *value;
   int model_index;
   vec3_t origin;
   dmodel_t *model;
   vec3_t start, end;
   trace_t tr;

   // distances from origin for checking for wall...
   static vec3_t wall_forward = {10, 0, 0};
   static vec3_t wall_back = {-10, 0, 0};
   static vec3_t wall_left = {0, 10, 0};
   static vec3_t wall_right = {0, -10, 0};

   // distances to place origin out from wall...
   static vec3_t wall_out_forward = { 32, 0, 0};
   static vec3_t wall_out_back = { -32, 0, 0};
   static vec3_t wall_out_left = { 0, 32, 0};
   static vec3_t wall_out_right = { 0, -32, 0};

   unsigned int len = strlen(item_name);
   int ent_index = -1;

   while ((ent_index = FindEntityByWildcard(ent_index, item_name, len)) != -1)
   {
      value = ValueForKey(&entities[ent_index], "model");
      if (value[0])
      {
         sscanf(value, "*%d", &model_index);

         // get the min/max coordinates of this brush model...

         model = &dmodels[model_index];

         // calculate the "origin" of the brush model...

         origin[0] = (model->mins[0] + model->maxs[0]) / 2.0f;
         origin[1] = (model->mins[1] + model->maxs[1]) / 2.0f;
         origin[2] = (model->mins[2] + model->maxs[2]) / 2.0f;

         // trace 4 lines outward looking for a nearby wall...
         // (only ONE of these should hit a wall)

         VectorCopy(origin, start);

         VectorAdd(start, wall_forward, end);  // forward
         TraceLine(start, end, &tr);

         if (tr.fraction < 1.0)  // did we hit a wall?
            VectorAdd(tr.endpos, wall_out_back, origin);  // adjust, create new origin

         VectorAdd(start, wall_back, end);  // back
         TraceLine(start, end, &tr);

         if (tr.fraction < 1.0)  // did we hit a wall?
            VectorAdd(tr.endpos, wall_out_forward, origin);  // adjust, create new origin

         VectorAdd(start, wall_left, end);  // left
         TraceLine(start, end, &tr);

         if (tr.fraction < 1.0)  // did we hit a wall?
            VectorAdd(tr.endpos, wall_out_right, origin);  // adjust, create new origin

         VectorAdd(start, wall_right, end);  // right
         TraceLine(start, end, &tr);

         if (tr.fraction < 1.0)  // did we hit a wall?
            VectorAdd(tr.endpos, wall_out_left, origin);  // adjust, create new origin

         // now origin should be out away from the wall

         // trace downward to find the ground from here...
         VectorAdd(origin, down_to_ground, end);
         TraceLine(origin, end, &tr);

         if (tr.fraction < 1.0)  // did we hit ground?
         {
            // raise up off of floor (or ledge) to center of player model...
            VectorAdd(tr.endpos, up_off_floor, origin);

            WaypointAdd(origin, waypoint_flags, TRUE);
         }
      }
   }
}


void WaypointAddLadders(const int waypoint_flags)
{
   int model_index;
   const char *value;
   vec3_t ladder_origin;
   dmodel_t *model;
   dface_t *face;
   dplane_t *plane;
   int face_index, edges, edge_index;
   vec3_t v[4];  // hold up to four vertexes for each face
   int vertex_index;
   int front_face_index;
   float face_width, max_face_width;
   vec3_t v_top[2], v_bottom[2], v_temp;
   vec3_t v_forward, v_backward, v_outward;
   vec3_t ladder_points[3];  // origin, "top" and "bottom" of ladder
   vec3_t v_start, v_end;
   trace_t tr;
   int loop, num_segments;
   bool outward_found;
   float dist;

   // loop through all the entities looking for "func_ladder"...
   int ent_index = -1;
   while ((ent_index = FindEntityByClassname(ent_index, "func_ladder")) != -1)
   {
      value = ValueForKey(&entities[ent_index], "model");
      if (value[0])
      {
         sscanf(value, "*%d", &model_index);

         // get the "origin" of the ladder...
         model = &dmodels[model_index];

         // calculate the "origin" of the brush model...

         ladder_origin[0] = (model->mins[0] + model->maxs[0]) / 2.0f;
         ladder_origin[1] = (model->mins[1] + model->maxs[1]) / 2.0f;
         ladder_origin[2] = (model->mins[2] + model->maxs[2]) / 2.0f;

         // find the "front" and "back" of the ladder.  do this by looking
         // for a faces whose vertex Z values are not all the same (i.e. it's
         // not the top face or the bottom face).  then look for the face
         // that is the widest.  this should be either the front or the back.

         max_face_width = 0.0;

         // loop though each face for this model...
         for (face_index = 0; face_index < model->numfaces; face_index++)
         {
            face = &dfaces[model->firstface + face_index];

            plane = &dplanes[face->planenum];

            for (vertex_index = 0; vertex_index < 4; vertex_index++)
            {
               v[vertex_index][0] = 0;
               v[vertex_index][1] = 0;
               v[vertex_index][2] = 0;
            }

            vertex_index = 0;

            for (edges = 0; edges < face->numedges; edges++)
            {
               // get the coordinates of the vertex of this edge...
               edge_index = dsurfedges[face->firstedge + edges];

               if (edge_index < 0)
               {
                  edge_index = -edge_index;
                  dedge_t* e = &dedges[edge_index];
                  v[vertex_index][0] = dvertexes[e->v[1]].point[0];
                  v[vertex_index][1] = dvertexes[e->v[1]].point[1];
                  v[vertex_index][2] = dvertexes[e->v[1]].point[2];
               }
               else
               {
                  dedge_t* e = &dedges[edge_index];
                  v[vertex_index][0] = dvertexes[e->v[0]].point[0];
                  v[vertex_index][1] = dvertexes[e->v[0]].point[1];
                  v[vertex_index][2] = dvertexes[e->v[0]].point[2];
               }

               if (vertex_index < 3)
                  vertex_index++;
            }

            // now look through the 4 vertexs to see if the Z coordinates
            // are the "same".

            if ((abs(v[0][2] - v[1][2]) < 8) && (abs(v[1][2] - v[2][2]) < 8) &&
                (abs(v[2][2] - v[3][2]) < 8) && (abs(v[3][2] - v[0][2]) < 8))
               continue;  // continue with next face if this is top or bottom

            // now calculate the 2D "width" of this face (ignoring Z axis)

            // is this a "base" (i.e. are the Z coordinates the "same")
            if (abs(v[0][2] - v[1][2]) < 8)
            {
               VectorSubtract(v[0], v[1], v_temp);
               face_width = Vector2DLength(v_temp);

               if (face_width > max_face_width)  // widest so far?
               {
                  max_face_width = face_width;
                  front_face_index = face_index;  // save it for later

                  // compare the Z coordinates of the 2 "bases"
                  if (v[0][2] > v[2][2])  // v[0] higher than v[2]?
                  {
                     VectorCopy(v[0], v_top[0]);     // save the top for later
                     VectorCopy(v[1], v_top[1]);
                     VectorCopy(v[2], v_bottom[0]);  // save the bottom for later
                     VectorCopy(v[3], v_bottom[1]);
                  }
                  else
                  {
                     VectorCopy(v[2], v_top[0]);     // save the top for later
                     VectorCopy(v[3], v_top[1]);
                     VectorCopy(v[0], v_bottom[0]);  // save the bottom for later
                     VectorCopy(v[1], v_bottom[1]);
                  }
               }
            }

            if (abs(v[1][2] - v[2][2]) < 8)  // is this a "base"?
            {
               VectorSubtract(v[1], v[2], v_temp);
               face_width = Vector2DLength(v_temp);

               if (face_width > max_face_width)  // widest so far?
               {
                  max_face_width = face_width;
                  front_face_index = face_index;  // save it for later

                  // compare the Z coordinates of the 2 "bases"
                  if (v[1][2] > v[0][2])  // v[0] higher than v[2]?
                  {
                     VectorCopy(v[1], v_top[0]);     // save the top for later
                     VectorCopy(v[2], v_top[1]);
                     VectorCopy(v[0], v_bottom[0]);  // save the bottom for later
                     VectorCopy(v[3], v_bottom[1]);
                  }
                  else
                  {
                     VectorCopy(v[0], v_top[0]);     // save the top for later
                     VectorCopy(v[3], v_top[1]);
                     VectorCopy(v[1], v_bottom[0]);  // save the bottom for later
                     VectorCopy(v[2], v_bottom[1]);
                  }
               }
            }
         }

         // now we know that front_face_index is either the front or back
         // trace vectors out from the ladder to see if world collisions or
         // brush model collisions occur to find out which direction this
         // func_ladder is aproachable from.

         face = &dfaces[model->firstface + front_face_index];

         plane = &dplanes[face->planenum];

         // create points in the middle of the ladder lengthwise...

         VectorCopy(ladder_origin, ladder_points[0]);  // middle of the ladder

         VectorAdd(v_top[0], v_top[1], v_temp);
         VectorScale(v_temp, 0.5, ladder_points[1]);  // middle of the top
         VectorAdd(v_bottom[0], v_bottom[1], v_temp);
         VectorScale(v_temp, 0.5, ladder_points[2]);  // middle of the bottom

         // adjust top middle and bottom middle by 10 units (towards the center)
         VectorSubtract(ladder_points[2], ladder_points[1], v_temp);
         VectorNormalize(v_temp);
         VectorScale(v_temp, 10.0, v_temp);
         VectorAdd(ladder_points[1], v_temp, ladder_points[1]);
         Maths::VectorInvert(v_temp);
         VectorAdd(ladder_points[2], v_temp, ladder_points[2]);

         // loop though the ladder points tracing a line outward in both the
         // forward and backward directions to see if we hit the world.

         VectorScale(plane->normal, 20.0, v_forward);
         VectorScale(plane->normal, 20.0, v_backward);
		 Maths::VectorInvert(v_backward);

         outward_found = FALSE;

         loop = 0;
         while ((loop < 3) && (!outward_found))
         {
            VectorCopy(ladder_points[loop], v_start);
            VectorAdd(ladder_points[loop], v_forward, v_end);

            TraceLine(v_start, v_end, &tr);

            if (tr.fraction < 1.0)  // we hit something going forward
            {
               VectorCopy(v_backward, v_outward);  // outward is v_backward
               VectorNormalize(v_outward);  // make unit vector
               outward_found = TRUE;
            }
            else
            {
               VectorCopy(ladder_points[loop], v_start);
               VectorAdd(ladder_points[loop], v_backward, v_end);

               TraceLine(v_start, v_end, &tr);

               if (tr.fraction < 1.0)  // we hit something going backward
               {
                  VectorCopy(v_forward, v_outward);  // outward is forward
                  VectorNormalize(v_outward);  // make unit vector
                  outward_found = TRUE;
               }
            }

            loop++;
         }

         // if outward_found is still FALSE here then need to check for
         // collisions with other world brushes (other than func_ladder)...

         // ADD THIS CODE LATER - FIXME!!!


         if (outward_found)  // do we now know which way is outward?
         {
            // create a waypoint at the top of the ladder
            // (remember that ladder_points[1] is already down 10 units...

            VectorSubtract(ladder_points[1], ladder_points[2], v_temp);
            VectorNormalize(v_temp);
            // a little bit lower than half of the player height...
            VectorScale(v_temp, 32.0 + 10.0, v_temp);
            VectorAdd(ladder_points[1], v_temp, v_end);  // top of ladder

            VectorScale(v_outward, 20.0, v_temp);
            VectorAdd(v_end, v_temp, v_end);  // move outward 20 units

            WaypointAdd(v_end, waypoint_flags, TRUE);  // add top waypoint

            // create a waypoint at the bottom of the ladder
            // (remember that ladder_points[2] is already up 10 units...
            VectorSubtract(ladder_points[1], ladder_points[2], v_temp);
            VectorNormalize(v_temp);
            // a little bit higher than half of the player height...
            VectorScale(v_temp, 44.0 - 10.0, v_temp);
            VectorAdd(ladder_points[2], v_temp, v_start);

            VectorScale(v_outward, 20.0, v_temp);
            VectorAdd(v_start, v_temp, v_start);  // move outward 20 units

            WaypointAdd(v_start, waypoint_flags, TRUE);  // add bottom waypoint

            // now determine how many waypoints to place in between
            // the start and end points on the ladder...

            VectorSubtract(v_end, v_start, v_temp);
            dist = VectorLength(v_temp);

            num_segments = (dist + 100.0) / 200.0;  // place every 200 units

            dist = VectorLength(v_temp) / num_segments;  // distance apart

            VectorSubtract(v_end, v_start, v_temp);
            VectorNormalize(v_temp);
            VectorScale(v_temp, dist, v_temp);  // delta vector for steps

            for (loop = 1; loop < num_segments; loop++)
            {
               VectorAdd(v_start, v_temp, v_start);

               WaypointAdd(v_start, waypoint_flags, TRUE);  // add middle waypoints
            }
         }
         else
         {
            printf("Ladder found, but can't tell which way is outward!\n");
         }
      }
   }
}


void WaypointAddDoors(const char *item_name, int waypoint_flags)
{
	// do some clever stuff with func_door entities here!!!

	// REMEMBER! MANY func_door ENTITIES ARE ACTUALLY LIFTS, NOT DOORS!!!

	// FIXME!!!
}


bool CheckBeyondJumpHeight(const vec3_t start, const vec3_t end)
{
   int step, num_steps;  // not the "step up" kind of steps
   float dist, prev_dist, down_dist;
   vec3_t v_temp, v_normal, v_step, v_down;
   trace_t tr;

   static vec3_t downward = {0, 0, -1000};

   // move from start to end 10 units at a time checking to see if the
   // distance to the "ground" suddenly changes by a value larger than
   // the player jump height.  If so, then the player will not be able
   // to get from the start point to the end point.

   down_dist = VectorLength(downward);

   VectorSubtract(end, start, v_temp);
   dist = VectorLength(v_temp);

   num_steps = dist / 10.0f;  // move 10 units during each test
   num_steps++;  // make sure you go up to and beyond the end point

   VectorCopy(v_temp, v_normal);
   VectorNormalize(v_normal);  // make 1 unit long
   VectorScale(v_normal, 10.0f, v_step);

   VectorCopy(start, v_temp);

   // find the distance to the "ground" from v_temp...
   VectorAdd(v_temp, downward, v_down);
   TraceLine(v_temp, v_down, &tr);

   prev_dist = down_dist * tr.fraction;  // calculate the distance to the ground

   VectorAdd(v_temp, v_step, v_temp);  // move outward one step size

   for (step = 0; step < num_steps; step++)
   {
      // find the distance to the "ground" from v_temp...
      VectorAdd(v_temp, downward, v_down);
      TraceLine(v_temp, v_down, &tr);

      dist = down_dist * tr.fraction;  // calculate the distance to the ground

      // check if the distance to the ground is much less than the previous
      if ((dist + 45) < prev_dist)  // 45 is max jump height
      {
         return TRUE;  // can't jump this high, so return
      }

      prev_dist = dist;

      VectorAdd(v_temp, v_step, v_temp);  // move outward one step size
   }

   return FALSE;  // not beyond step/jump height (path is okay)
}


bool CheckModelIntersection(const vec3_t start, const vec3_t end)
{
   vec3_t vector;
   int model_index, face_index;
   vec3_t min, max, intersect;
   dmodel_t *model;
   dface_t *face;
   dplane_t *plane;
   vec3_t v;
   int edge_index;
   int ent_index;
   const char *value;

   // Check if there are any specific brush models (ladders, railings, fences,
   // etc.) that will block the player moving from start to end.  Do this by
   // going though each brush model, calculating whether the vector from start
   // to end will intersect a plane (defined by a face of the brush model) and
   // check to see if the intersection point lies between the min and max
   // coordinates of the bounding box of the brush model

   // create a vector from start to end and normalize it...
   VectorSubtract(end, start, vector);
   VectorNormalize(vector);

   // loop through all entities...
   for (ent_index = 0; ent_index < num_entities; ent_index++)
   {
      value = ValueForKey(&entities[ent_index], "classname");
      if (value[0])
      {
         if ((strcmp(value, "func_wall") == 0) ||    // check for func_wall OR
             (strcmp(value, "func_ladder") == 0) ||  // func_ladder OR
             (strcmp(value, "func_door") == 0))      // func_door
         {
            value = ValueForKey(&entities[ent_index], "model");
            if (value[0])
            {
               sscanf(value, "*%d", &model_index);

               model = &dmodels[model_index];

               // get the brush model bounding box min and max coordinates...
               VectorCopy(model->mins, min);
               VectorCopy(model->maxs, max);

               // adjust bounding box by a small delta (make it slightly bigger)...
               min[0] -= 0.001f; min[1] -= 0.001f; min[2] -= 0.001f;
               max[0] += 0.001f; max[1] += 0.001f; max[2] += 0.001f;

               // loop though each face for this model...
               for (face_index = 0; face_index < model->numfaces; face_index++)
               {
                  face = &dfaces[model->firstface + face_index];

                  plane = &dplanes[face->planenum];

                  // get the coordinates of the vertex of the first edge...
                  edge_index = *(dsurfedges + face->firstedge);

                  if (edge_index < 0)
                  {
                     edge_index = -edge_index;
                     dedge_t* e = &dedges[edge_index];
                     v[0] = dvertexes[e->v[1]].point[0];
                     v[1] = dvertexes[e->v[1]].point[1];
                     v[2] = dvertexes[e->v[1]].point[2];
                  }
                  else
                  {
                     dedge_t* e = &dedges[edge_index];
                     v[0] = dvertexes[e->v[0]].point[0];
                     v[1] = dvertexes[e->v[0]].point[1];
                     v[2] = dvertexes[e->v[0]].point[2];
                  }

                  // find where this vector (from start to end) intersects
                  // this plane (of the model)...
                  if (VectorIntersectPlane(start, vector, v, plane->normal, intersect))
                  {
                     // check if the intersection point is within the model bounding box...
                     if ((intersect[0] > min[0]) && (intersect[0] < max[0]) &&
                         (intersect[1] > min[1]) && (intersect[1] < max[1]) &&
                         (intersect[2] > min[2]) && (intersect[2] < max[2]))
                        return TRUE;  // vector from start to end intersects this brush model
                  }
               }
            }
         }
      }
   }

   return FALSE;  // didn't intersect with a brush model
}


void CalculateWaypointPaths()
{
   int size;
   int index, index2;
   float dist, max_range;
   vec3_t vec;
   sandbot::path_t *p, *p_new;
   int percent_complete, prev_percent;
   vec3_t start, end;
   trace_t tr;

   Logger::Info( "Running CalculateWaypointPaths\n" );

   size = sizeof(sandbot::path_t *) * num_waypoints;

   paths = (sandbot::path_t **)malloc(size);

   if (paths == NULL)
   {
      printf("Error allocating memory for waypoint paths!\n");
      return;
   }

   memset(paths, 0, size);

   prev_percent = -1;

   // the max range is 1.5 times the hypotenuse of the grid size plus a little bit...
   max_range = 1.5f * sqrt(map.iGridSize * map.iGridSize * 2) + 10.0f;

   // calculate the waypoint paths for all waypoints...
   for (index = 0; index < num_waypoints; index++)
   {
      percent_complete = index * 100 / num_waypoints;

      if (percent_complete > prev_percent)
      {
         printf("Percent of paths calculated: %d%%\n", percent_complete);
         fflush(stdout);
         prev_percent = percent_complete;
      }

      p = paths[index];

      VectorCopy(sandbotWaypoints[index].origin, start);

      // find which waypoints are "reachable" from this waypoint...
      for (index2 = 0; index2 < num_waypoints; index2++)
      {
         if (index2 == index)  // if source and dest are the same, skip it
            continue;

         // see if the destination waypoint is within rangesandbotWaypoints
         VectorSubtract(sandbotWaypoints[index2].origin, sandbotWaypoints[index].origin, vec);
         dist = VectorLength(vec);

         if (dist > max_range)  // beyond maximum path range?
            continue;

         // check if the destination waypoint is "reachable"...
         VectorCopy(sandbotWaypoints[index2].origin, end);

         TraceLine(start, end, &tr);

         if (tr.fraction < 1.0)  // did we hit something?
            continue;

         // if this is NOT a ladder waypoint...
         if ((sandbotWaypoints[index].flags & sandbot::W_FL_LADDER) == 0)
         {
            // check if ground suddenly changes height between start and end
            if (CheckBeyondJumpHeight(start, end))
               continue;
         }

         // check if path will intersect a brush model (ladders, railings, fences, etc.)
         if (CheckModelIntersection(start, end))
            continue;

         // add waypoint index2 to paths from index...
         p_new = (sandbot::path_t *)malloc(sizeof(sandbot::path_t));

         if (p_new == NULL)
         {
            printf("Error allocating path node in linked list!\n");
            return;
         }

		 Logger::Trace( "Adding path between %d and %d\n", index, index2 );

		 // TODO: sort out the multiple index entries
         p_new->index[0] = index2;
		 p_new->index[1] = -1;
		 p_new->index[2] = -1;
		 p_new->index[3] = -1;
         p_new->next = p;
         p = p_new;
      }

      paths[index] = p;  // save the new linked list head pointer
   }

   printf("\rPercent of paths calculated: 100%%\n");
}


void WaypointLevel( const Map& map )
{
	Logger::Info( "Generating waypoints...\n" );

   array_size = (Map::MAP_SIZE + (map.iGridSize -1)) / map.iGridSize;

   array_size = ((array_size + 7) / 8) * 8;  // make even multiple of 8

   int table_size = array_size * array_size * array_size / 8;  // 3 dimensional bit array

   visited = (unsigned char *)malloc(table_size);  // 3 dimensional array of grid size

   if (visited == NULL)
   {
	   Error("Error allocating memory for waypoint visited array!");
   }

   waypoint_loc = (unsigned char *)malloc(table_size);  // 3 dimensional array of grid size

   if (waypoint_loc == NULL)
   {
	   Error("Error allocating memory for waypoint location array!");
   }

   memset(visited, 0, table_size);
   memset(waypoint_loc, 0, table_size);

   Logger::Info( "Using waypoint grid size of %d units\n", map.iGridSize );

   num_waypoints = 0;

   overflow = FALSE;

   forward[0] =  map.iGridSize;  forward[1] = 0;           forward[2] = 0;
   back[0]    = -map.iGridSize;  back[1]    = 0;           back[2]    = 0;
   left[0]    = 0;           left[1]    = map.iGridSize;  left[2]    = 0;
   right[0]   = 0;           right[1]   = -map.iGridSize;  right[2]   = 0;
   up[0]      = 0;           up[1]      = 0;           up[2]      = map.iGridSize;
   down[0]    = 0;           down[1]    = 0;           down[2]    = -map.iGridSize;

   // intialize vectors used to detect waypoints in mid-air...
   down_to_ground[0] = 0.0;  down_to_ground[1] = 0.0;  down_to_ground[2] = -(map.iGridSize + 10.0);

   // player is 72 units, origin is half that
   up_off_floor[0] = 0;  up_off_floor[1] = 0;  up_off_floor[2] = 36.0f;

   level_min[0] =  9999.9f;  level_min[1] =  9999.9f;  level_min[2] =  9999.9f;
   level_max[0] = -9999.9f;  level_max[1] = -9999.9f;  level_max[2] = -9999.9f;

   // get the min and max coordinates of the level...

   dmodel_t* model = &dmodels[0];  // model 0 is the BSP world

   VectorCopy(model->mins, level_min);
   VectorCopy(model->maxs, level_max);

	// TODO: replace all this with one function to iterate over the entities once? should be faster than interating for each entity individually

   // go through "important" items first and add waypoints for them...
   WaypointAddEntities("weapon_", sandbot::W_FL_WEAPON);
   WaypointAddEntities("ammo_", sandbot::W_FL_AMMO);
   WaypointAddEntities("item_healthkit", sandbot::W_FL_HEALTH);
   WaypointAddEntities("item_battery", sandbot::W_FL_ARMOR);

	// Day of Defeat
	WaypointAddEntities( "dod_control_point", sandbot::W_FL_DOD_CAP );
	// Natural Selection
	WaypointAddEntities( "team_hive", sandbot::W_FL_NS_HIVE );
	WaypointAddEntities( "team_command", sandbot::W_FL_NS_COMMAND_CHAIR );

   // add wall mounted entities (func_healthcharger, func_recharge, func_button, etc.)
   WaypointAddWallMountedEntities("func_healthcharger", sandbot::W_FL_HEALTH);
   WaypointAddWallMountedEntities("func_recharge", sandbot::W_FL_ARMOR);

   // add waypoints for ladders...
   WaypointAddLadders(sandbot::W_FL_LADDER);

   // add waypoints for doors and lifts (make a separate function for lifts???)
   WaypointAddDoors("func_ladder", sandbot::W_FL_DOOR);

	// start at the "first" spawn point...
	int ent_index = -1;
	const char *value;

	if ((ent_index = FindEntityByClassname(ent_index, map.szSpawnpoint)) != -1)
	{
		value = ValueForKey(&entities[ent_index], "origin");
		if (value[0])
		{
			sscanf(value, "%f %f %f", &spawn_point[0], &spawn_point[1], &spawn_point[2]);
		}
	}
	else
	{
		printf("Error! Can't find a spawn point: %s\n", map.szSpawnpoint);
		return;
	}

	location_count = 0;

	RecursiveFloodFill(spawn_point);

	if (location_count > 999)
	{
		printf("\n");
	}

	Logger::Info( "%d locations were visited\n", location_count );

	if (overflow)
	{
		Logger::Warn("WARNING: Waypointing incomplete! Too many waypoints generated!\n");
	}

	Logger::Info( "%d waypoints were generated\n", num_waypoints );

	Logger::Info( "Calculating waypoint paths...\n" );

	paths = nullptr;

	CalculateWaypointPaths();

	// write the waypoints and paths to the waypoint file
	if( map.cFormat == Map::FORMAT_SANDBOT )
	{
		WriteSandbotWaypointFile();
	}
	else if( map.cFormat == Map::FORMAT_HPB_BOT )
	{
		WriteHPB_BotWaypointFile();
	}

	free(visited);
	free(waypoint_loc);

	Logger::Info( "Done!\n" );
}

void WriteSandbotWaypointFile()
{
	int index;
	sandbot::path_t *p, *p_next;

    string mapName = Util::ExtractFileNameWithoutExtension(world.GetMapName());
    string strFilename = mapName + ".wpt";

	Logger::Info( "Creating waypoint file %s...\n", strFilename.c_str() );

	FILE *bfp = fopen(strFilename.c_str(), "wb");

    map.WriteWaypointHeader(bfp, mapName);

	Logger::Info( "Writing waypoints...\n" );
	// write the waypoint information...
	for (index = 0; index < num_waypoints; index++)
	{
		fwrite(&sandbotWaypoints[index], sizeof(sandbot::waypoint_t), 1, bfp);
	}

	if (paths)
	{
		Logger::Info( "Writing paths...\n" );

		Logger::Info( "Writing paths for waypoints...\n" );
		// save the waypoint paths...
		int i;
		short int num;
		for (index = 0; index < num_waypoints; index++)
		{
			// count the number of paths from this node...
			p = paths[index];
			num = 0;

			while (p != nullptr)
			{
				i = 0;

				while (i < map.GetMaxPathIndexes())
				{
					if (p->index[i] != -1)
						num++;  // count path node if it's used

					i++;
				}

				p = p->next;  // go to next node in linked list
			}

			// write the count
			fwrite(&num, sizeof(num), 1, bfp);

			// now write out each path index
			p = paths[index];

			while (p != nullptr)
			{
				i = 0;

				while (i < map.GetMaxPathIndexes())
				{
					if (p->index[i] != -1)  // save path node if it's used
						fwrite(&p->index[i], sizeof(p->index[0]), 1, bfp);

					i++;
				}

				// go to next node in linked list
				p = p->next;
			}
			Logger::Trace( "Wrote paths for waypoint %d\n", index );
		}

		Logger::Info( "Freeing paths for waypoints...\n" );
		for (index = 0; index < num_waypoints; index++)
		{
			p = paths[index];
			while (p)
			{
				p_next = p->next;
				free(p);
				p = p_next;
			}
		}

		free(paths);
		paths = nullptr;
	}
	else
	{
		short int count = 0;

		// write empty paths...
		for (index = 0; index < num_waypoints; index++)
			fwrite(&count, sizeof(count), 1, bfp);
	}

	fclose(bfp);
}

void WriteHPB_BotWaypointFile()
{
	string mapName = Util::ExtractFileNameWithoutExtension(world.GetMapName());
    string strFilename = mapName + ".wpt";

	Logger::Info("Creating waypoint file %s...\n", strFilename.c_str());

	FILE* bfp = fopen(strFilename.c_str(), "wb");

    map.WriteWaypointHeader(bfp, mapName);

	Logger::Info("Writing waypoints...\n");
	// write the waypoint information...
	for (int index = 0; index < num_waypoints; index++)
	{
		fwrite(&hpbbotWaypoints[index], sizeof(hpb_bot::WAYPOINT), 1, bfp);
	}
}