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

#include <stdio.h>

#ifdef WIN32
#include <direct.h>
#else
#include <unistd.h>
#endif // WIN32

#include "scriplib.h"
#include "config.h"


Config::Config(char *config_file)
{
	char config_filename[MAX_PATH];

	// set up configuration defaults...
	spawnpoint[0] = 0;

#ifdef WIN32
	_getcwd(szPath, MAX_PATH);
	strcat(szPath, "\\");
#else
	getcwd(szPath, MAX_PATH);
	strcat(szPath, "/");
#endif

	strcpy(config_filename, szPath);
	strcat(config_filename, config_file);

	LoadScriptFile(config_filename);

	ParseScriptFile();
}

Config::~Config()
{
}

bool Config::ParseScriptFile()
{
	while( true )
	{
		do
		{
			// look for a line starting with a '$'
			GetToken( true );

			if( endofscript )
			{
				// indicate success
				return false;
			}
			if( token[0] == '$' )
			{
				break;
			}

			while( TokenAvailable() )
			{
				GetToken( false );
			}
		} while( true );

		if( !strcmp( token, "$spawnpoint" ) )
		{
			if( spawnpoint[0] )
			{
				Error( "Multiple $spawnpoint entries found in .cfg file!\n" );
			}

			GetToken( false );
			sscanf( token, "%s", spawnpoint );
		}
		else
		{
			Error( "Unknown Config file option: %s\n", token );
		}
	}
}
