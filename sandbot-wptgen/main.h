//=============================================================================
//
// sandbot-wptgen - Sandbot waypoint generator
//
// Based on BSP_tool by Jeffrey "botman" Broome
//
// http://www.teamsandpit.com/
//
// Notes: application entrypoint
//
//=============================================================================

#ifndef __MAIN_H__
#define __MAIN_H__

#include "logger.h"
#include "map.h"
#include "xplatform.h"

extern Map map;

int main( _In_ int argc, _In_ char** argv );

#endif // __MAIN_H__