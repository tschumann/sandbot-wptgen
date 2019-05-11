//
// BSP_tool - botman's Half-Life BSP utilities
//
// (http://planethalflife.com/botman/)
//
// config.cpp
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

#ifdef WIN32
#include "windows.h"
#include "direct.h"
#else
#include "stdio.h"
#endif

#include "scriplib.h"
#include "config.h"

extern Config config;


Config::Config(char *config_file)
{
   int index;
   char config_filename[MAX_PATH];

   // set up configuration defaults...

   bspname[0] = 0;
   spawnpoint[0] = 0;

   _getcwd(szPath, MAX_PATH);
#ifdef WIN32
   strcat(szPath, "\\");
#else
   strcat(szPath, "/");
#endif

   strcpy(config_filename, szPath);
   strcat(config_filename, config_file);

   LoadScriptFile(config_filename);

   ParseScriptFile();
}


Config::~Config(void)
{
}

bool Config::ParseScriptFile(void)
{
   while (1)
   {
      do
      {
         GetToken (true);  // look for a line starting with a '$'
         if (endofscript)
            return 0;  // indicate success
         if (token[0] == '$')
            break;
         while (TokenAvailable())
            GetToken (false);
      } while (1);

      if (strcmp(token, "$bspfile") == 0)
      {
         if (bspname[0])
            Error("Duplicate $bspfile entry found in .cfg file!\n");

         GetToken(false);
         strcpy(bspname, token);
      }
      else if (strcmp(token, "$spawnpoint") == 0)
      {
         if (spawnpoint[0])
            Error("multiple $spawnpoint found in .cfg file!\n");

         GetToken(false);
         sscanf(token, "%s", spawnpoint);
      }
      else
         Error("Unknown Config file option: %s\n", token);
   }
}
