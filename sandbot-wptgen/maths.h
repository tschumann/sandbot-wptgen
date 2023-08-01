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

#ifndef __MATHS_H__
#define __MATHS_H__

#include "xplatform.h"

class Maths final
{
public:
	Maths() = delete;

	static float Dot_Product( const _In_ float (&first)[3], const _In_ float (&second)[3] ) noexcept;
	static void Vector_Add( const _In_ float (&first)[3], const _In_ float (&second)[3], _Out_ float (&out)[3] ) noexcept;
	static void Vector_Copy( const _In_ float (&source)[3], _Out_ float (&destination)[3] ) noexcept;
	static void VectorInvert( _Inout_ float (&vector)[3] ) noexcept;
	static void Vector_Scale( const _In_ float in[3], const _In_ float fScale, _Out_ float (&out)[3] ) noexcept;
	static void Vector_Subtract( const _In_ float (&first)[3], const _In_ float (&second)[3], _Out_ float (&out)[3] ) noexcept;

	template <class T> static T Max( _In_ T a, _In_ T b ) noexcept
	{
		return (a > b) ? a : b;
	}

	template <class T> static T Min( _In_ T a, _In_ T b ) noexcept
	{
		return (a < b) ? a : b;
	}
};

#endif // __MATHS_H__