#pragma once

#include <stdlib.h>
#include <stdint.h>
#include "Utils.h"
#include <string>
#include "../patcher.h"

class CMini3D
{
public:
    static float*    ambientRed;
    static float*    ambientGreen;
    static float*    ambientBlue;
    static uint8_t** tempVertexBuffer;
    static int*      polyFlag;
    static int*      blendFlag;
    static int*      destBlendFlag;
    static int*      fogFlag;
    static int*      clipFlag;
    static float*    fogMin;
    static float*    fogMax;
    static float*    invFogMaxMin;

    //API
    static void pAPIDLLsetDestBlend(int val) WRAP_FUNC;

    static void patchFuncs();

    //Wrapped
    static void setAmbientLight(float ambient);

    //Unknown
    static void setDestBlend(int val);

    //Non-matching
    static void enableFog();

    //Matching
    static void* alloc32(int size);
    static float getAmbientLight();
    static int init();
    static void disableBlend();
    static void enableBlend();
    static void disableFog();
};