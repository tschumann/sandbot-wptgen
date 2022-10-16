//=============================================================================
//
// sandbot-wptgen - Sandbot waypoint generator
//
// Based on BSP_tool by Jeffrey "botman" Broome
//
// http://www.teamsandpit.com/
//
// Notes: maths class
//
//=============================================================================

#include "maths.h"

float Maths::Dot_Product( const _In_ float first[3], const _In_ float second[3] ) noexcept
{
	return (first[0] * second[0]) + (first[1] * second[1]) + (first[2] * second[2]);
}

void Maths::Vector_Add( const _In_ float first[3], const _In_ float second[3], _Out_ float out[3] ) noexcept
{
	out[0] = first[0] + second[0];
	out[1] = first[1] + second[1];
	out[2] = first[2] + second[2];
}

void Maths::Vector_Copy( const _In_ float source[3], _Out_ float destination[3] ) noexcept
{
	destination[0] = source[0];
	destination[1] = source[1];
	destination[2] = source[2];
}

void Maths::VectorInvert( _Inout_ float vector[3] ) noexcept
{
	vector[0] = -vector[0];
	vector[1] = -vector[1];
	vector[2] = -vector[2];
}

void Maths::Vector_Scale( const _In_ float in[3], const _In_ float fScale, _Out_ float out[3] ) noexcept
{
	out[0] = in[0] * fScale;
	out[1] = in[1] * fScale;
	out[2] = in[2] * fScale;
}

void Maths::Vector_Subtract( const _In_ float first[3], const _In_ float second[3], _Out_ float out[3] ) noexcept
{
	out[0] = first[0] - second[0];
	out[1] = first[1] - second[1];
	out[2] = first[2] - second[2];
}