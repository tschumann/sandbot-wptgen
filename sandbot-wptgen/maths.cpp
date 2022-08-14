//=============================================================================
//
// sandbot-wptgen - Sandbot waypoint generator
//
// Based on bsp_tool by Jeffrey "botman" Broome
//
// http://www.teamsandpit.com/
//
// Notes: maths class
//
//=============================================================================

#include "maths.h"

void Maths::VectorInvert( _Inout_ float vector[3] )
{
	vector[0] = -vector[0];
	vector[1] = -vector[1];
	vector[2] = -vector[2];
}