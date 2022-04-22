//
// BSP_tool - botman's Half-Life BSP utilities
//
// (http://planethalflife.com/botman/)
//
// entity.cpp
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

int num_entvars = 0;
entvars_t entvars[MAX_MAP_ENTITIES];

void LoadEntVars()
{
   int ent_index = 0;
   char *value;

   while (ent_index < num_entities)
   {
      value = ValueForKey(&entities[ent_index], "classname");

      if (value[0])
      {
         strcpy(entvars[num_entvars].classname, value);

         // initialize the default entvars fields...
         entvars[num_entvars].origin[0] = 0.0f;
         entvars[num_entvars].origin[1] = 0.0f;
         entvars[num_entvars].origin[2] = 0.0f;

         entvars[num_entvars].angles[0] = 0.0f;
         entvars[num_entvars].angles[1] = 0.0f;
         entvars[num_entvars].angles[2] = 0.0f;

         entvars[num_entvars].brush_model_index = 0;

         value = ValueForKey(&entities[ent_index], "origin");
         if (value[0])
         {
            sscanf(value, "%f %f %f", &entvars[num_entvars].origin[0], &entvars[num_entvars].origin[1], &entvars[num_entvars].origin[2]);
         }

         value = ValueForKey(&entities[ent_index], "angle");
         if (value[0])
         {
            // set the yaw angle...
            sscanf(value, "%f", &entvars[num_entvars].angles[1]);
         }

         value = ValueForKey(&entities[ent_index], "model");
         if (value[0])
         {
            if (sscanf(value, "*%d", &entvars[num_entvars].brush_model_index) == 1)
            {
               dmodel_t *model;

               // calculate the origin for this brush model...
               model = &dmodels[entvars[num_entvars].brush_model_index];

               entvars[num_entvars].origin[0] = (model->mins[0] + model->maxs[0]) / 2.0f;
               entvars[num_entvars].origin[1] = (model->mins[1] + model->maxs[1]) / 2.0f;
               entvars[num_entvars].origin[2] = (model->mins[2] + model->maxs[2]) / 2.0f;
            }
         }

         num_entvars++;
      }

      ent_index++;
   }
}
