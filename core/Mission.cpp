#include "Mission.h"

CDemonMission* CDemonMission::gSit;

void CDemonMission::patchFuncs()
{
    gSit = *(CDemonMission**)gBase + 0x22AC18;
}