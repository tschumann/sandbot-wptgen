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

void Maths::Vector_Copy( const _In_ float source[3], _Out_ float destination[3] )
{
	destination[0] = source[0];
	destination[1] = source[1];
	destination[2] = source[2];
}

void Maths::VectorInvert( _Inout_ float vector[3] )
{
	vector[0] = -vector[0];
	vector[1] = -vector[1];
	vector[2] = -vector[2];
}