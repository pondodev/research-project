#ifndef DAN_MATH_H
#define DAN_MATH_H

#include <cstdlib>
#include <cmath>

#define PI 3.14159265359
#define TAU PI*2

float lerp( float a, float b, float t );
float inverse_lerp( float a, float b, float val );
float remap( float in_min, float in_max, float out_min, float out_max, float val );
float rand_f( float min, float max );
float frac( float v );

#endif
