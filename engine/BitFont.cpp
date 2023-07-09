#include "BitFont.h"

CBitFont* CBitFont::gMediumFont;

void CBitFont::patchFuncs()
{
    gMediumFont = *(CBitFont**)gBase + 0x184CFE8;
}

void CBitFont::drawText(int x, int y, int unk0, int unk1, const char* text)
{
    //((void(*)(CBitFont*, int, int, int, int, const char*))(gBase + 0x6D1D0))(this, x, y, unk0, unk1, text);
    WRAP_JMPEAX(gBase + 0x6D1D0);
}