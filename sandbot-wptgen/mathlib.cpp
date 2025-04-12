/***
*
*	Copyright (c) 1996-2001, Valve LLC. All rights reserved.
*	
*	This product contains software technology licensed from Id 
*	Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc. 
*	All Rights Reserved.
*
****/

// mathlib.c -- math primitives

#pragma warning( disable : 4244 )
#pragma warning( disable : 4237 )
#pragma warning( disable : 4305 )

#include "cmdlib.h"
#include "mathlib.h"

double Vector2DLength(vec3_t v)
{
   int   i;
   double length;

   length = 0;
   for (i=0 ; i< 2 ; i++)  // ignore the Z axis
      length += v[i]*v[i];
   length = (float)sqrt(length); // FIXME

   return length;
}

double VectorLength(vec3_t v)
{
	int		i;
	double	length;
	
	length = 0;
	for (i=0 ; i< 3 ; i++)
		length += v[i]*v[i];
	length = sqrt (length);		// FIXME

	return length;
}

vec_t VectorNormalize (vec3_t v)
{
	int		i;
	double	length;

if ( fabs(v[1] - 0.000215956) < 0.0001)
i=1;

	length = 0;
	for (i=0 ; i< 3 ; i++)
		length += v[i]*v[i];
	length = sqrt (length);
	if (length == 0)
		return 0;
		
	for (i=0 ; i< 3 ; i++)
		v[i] /= length;	

	return length;
}

// WARNING!!! the "vector" parameter should be NORMALIZED!!!
float DistanceToIntersection(const vec3_t origin, const vec3_t vector,
                             const vec3_t plane_origin, const vec3_t plane_normal)
{
   float d = -(DotProduct(plane_normal, plane_origin));
 
   float numerator = DotProduct(plane_normal, origin) + d;
   float denominator = DotProduct(plane_normal, vector);
 
   if (fabs(denominator) < 0.00001)
      return (-1.0f);  // normal is orthogonal to vector, no intersection

   return -(numerator/denominator);
}


// return TRUE or FALSE if vector intersects a plane...
bool VectorIntersectPlane(const vec3_t origin, const vec3_t vector,
                          const vec3_t plane_origin, const vec3_t plane_normal,
                          vec3_t intersect_point)
{
   float dist;
   vec3_t v_temp;

   dist = DistanceToIntersection(origin, vector, plane_origin, plane_normal);

   if (dist < 0)
      return FALSE;

   VectorScale(vector, dist, v_temp);
   VectorAdd(origin, v_temp, intersect_point);

   return TRUE;
}
