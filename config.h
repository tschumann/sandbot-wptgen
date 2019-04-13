//
// BSP_tool - botman's Half-Life BSP utilities
//
// (http://planethalflife.com/botman/)
//
// config.h
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

#ifndef CONFIG_H
#define CONFIG_H

#define MAX_MODS 100
#define MAX_MODELS 200

#include <windows.h>

class Config
{
   public:

   int width;  // display width
   int height;  // display height
   int bits_per_pixel;
   int refresh_rate;
   bool enable_fullscreen;

   int x_pos, y_pos;  // X & Y position of upper left corner

   bool enable_lighting;
   float brightness;
   float gamma_adjust;

   int movement_speed;
   float mouse_sensitivity;

   bool enable_inverted_mouse;
   bool enable_noclip;

   bool render_special_textures;
   int  special_texture_transparency;

   int show_edges;

   char halflife_dir[64];
   char bspname[64];
   char spawnpoint[64];

   int num_models;
   char model_classname[MAX_MODELS][64];
   char model_filename[MAX_MODELS][64];

   int num_mods;
   int bsp_mod_index;

   char szPath[MAX_PATH];         // path where the running application resides


   Config(char *config_file);
   ~Config(void);

   bool ParseScriptFile(void);
};

#endif

