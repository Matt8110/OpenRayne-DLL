#pragma once

#include <math.h>
#include <iostream>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include "../patcher.h"

typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;
typedef int32_t s32;
typedef int16_t s16;
typedef int8_t s8;

#define PI 3.141592741012573f

class CUtils
{
public:
    static float wrapPi(float input)
    {
        float temp;

        if (fabs(input) > PI)
        {
            temp = input + PI;
            input = floorf(temp * 0.1591549f);
            return (temp - input * 6.283185f) - 3.141593f;
        }

        return input;
    }

    static void reallyGTFO(const char* format, ...)
    {
        va_list list;
        va_start(list, format);
        vfprintf(stdout, format, list);
        va_end(list);

        exit(0);
    }

    static float fRand(float min, float max)
    {
        float ran = rand();
        return ran * ((max - min) + min);
    }
};