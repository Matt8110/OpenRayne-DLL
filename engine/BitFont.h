#pragma once

#include "../patcher.h"

class CBitFont
{
public:
    static CBitFont* gMediumFont;

    static void patchFuncs();
    //char unk[1024];
    void drawText(int x, int y, int unk0, int unk1, const char* text) WRAP_FUNC;
};