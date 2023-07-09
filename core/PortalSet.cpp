#include "PortalSet.h"

CPortalSet* CPortalSet::gPortalSet;

void CPortalSet::patchFuncs()
{
    gPortalSet = *(CPortalSet**)(gBase + 0x22D4A0);
}

void CPortalSet::putActorInBsp(CDemonActor* actor)
{
    /*asm volatile(
        "movl %[thisPtr], %%ecx;"
        "pushl %[actorPtr];"
        "movl %[funcPtr], %%eax;"
        "call *%%eax;"
        ::  [thisPtr] "g" (this),
            [actorPtr] "g" (actor),
            [funcPtr] "g" (gBase + 0xFC760)
    );*/
    WRAP_JMPEAX(gBase + 0xFC760);
}

int CPortalSet::isActorVisible(CDemonActor* actor)
{
    WRAP_JMPEAX(gBase + 0xFCA50);
}

int CPortalSet::collisionDetection(CCollisionInfo* collInfo)
{
    WRAP_JMPEAX(gBase + 0xFD220);
}