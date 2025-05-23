/***
*
*	Copyright (c) 1996-2001, Valve LLC. All rights reserved.
*	
*	This product contains software technology licensed from Id 
*	Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc. 
*	All Rights Reserved.
*
****/

#ifndef __MATHLIB__
#define __MATHLIB__

// mathlib.h

#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifdef DOUBLEVEC_T
typedef double vec_t;
#else
typedef float vec_t;
#endif // DOUBLEVEC_T
typedef vec_t vec3_t[3];	// x,y,z
typedef vec_t vec4_t[4];	// x,y,z,w

#define	SIDE_FRONT		0
#define	SIDE_ON			2
#define	SIDE_BACK		1
#define	SIDE_CROSS		-2

#define DotProduct(x,y) ((x)[0]*(y)[0]+(x)[1]*(y)[1]+(x)[2]*(y)[2])
#define VectorSubtract(a,b,c) {(c)[0]=(a)[0]-(b)[0];(c)[1]=(a)[1]-(b)[1];(c)[2]=(a)[2]-(b)[2];}
#define VectorAdd(a,b,c) {(c)[0]=(a)[0]+(b)[0];(c)[1]=(a)[1]+(b)[1];(c)[2]=(a)[2]+(b)[2];}
#define VectorCopy(a,b) {(b)[0]=(a)[0];(b)[1]=(a)[1];(b)[2]=(a)[2];}
#define VectorScale(a,b,c) {(c)[0]=(b)*(a)[0];(c)[1]=(b)*(a)[1];(c)[2]=(b)*(a)[2];}

double Vector2DLength(vec3_t v);
double VectorLength(vec3_t v);

vec_t VectorNormalize (vec3_t v);

float DistanceToIntersection(const vec3_t origin, const vec3_t vector,
                             const vec3_t plane_origin, const vec3_t plane_normal);
bool VectorIntersectPlane(const vec3_t origin, const vec3_t vector,
                          const vec3_t plane_origin, const vec3_t plane_normal,
                          vec3_t intersect_point);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __MATHLIB__
