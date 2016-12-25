//
//  Math.h
//  Engine.Framework
//
//  Created by Narendra Umate on 4/13/13.
//  Copyright (c) 2013 Narendra Umate. All rights reserved.
//

#ifndef __Engine_Framework__Math__
#define __Engine_Framework__Math__

#include <float.h>

#if defined(__linux__)
#include <math.h>
#endif //defined(__linux__)

#if defined(__APPLE__)
// Use this without SDL
#define _USE_MATH_DEFINES
#include <math.h>
#endif // defined(__APPLE__)

#if defined(_WIN32)
// Use this without SDL
#define _USE_MATH_DEFINES
#include <cmath>
#endif // defined(_WIN32)

// double precision literal is either
// 1 place before point and 35 after or
// 0 place before point and 36 after it

#define M_PI_180 M_PI / 180.0f
#define M_180_PI 180.0f / M_PI
#define M_EPSILON 0.000001f
#define M_DEGREE_TO_RADIAN M_PI_180
#define M_RADIAN_TO_DEGREE M_180_PI

//	Windows UINT
#ifndef UINT
typedef unsigned int UINT;
#endif //UINT

//	MacOS uint
#ifndef uint
typedef unsigned int uint;
#endif //uint

float invsqrt(const float& value);
bool isp2(const int& value);
int flp2(const int& value);
int clp2(const int& value);

int clamp(const int& value, const int& min, const int& max);
float clamp(const float& value, const float& min, const float& max);

float degrees(const float& radians);
float radians(const float& degrees);

float lerp(const float& a, const float& b, const float& t);
float barycentric(const float& value1, const float& value2, const float& value3, const float& amount1, const float& amount2);
float catmullRom(const float& value1, const float& value2, const float& value3, const float& value4, const float& amount);
float hermite(const float& value1, const float& tangent1, const float& value2, const float& tangent2, const float& amount);
float smoothStep(const float& value1, const float& value2, const float& amount);

#endif /* defined(__Engine_Framework__Math__) */
