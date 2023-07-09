#pragma once

#include "../patcher.h"

class CDemonMission
{
public:
    static void patchFuncs();

    static CDemonMission* gSit; //Weird name, but okay
};