#include "Set.h"

CDemonSet* CDemonSet::gSet;

void CDemonSet::patchFuncs()
{
    gSet = *(CDemonSet**)gBase + 0x22DB18;

    patchFunction(&CDemonSet::collisionDetection, 0x11BF40);
}

void CDemonSet::addBarrier(CBarrier* barrier)
{
    return;
}

void CDemonSet::collisionDetection(CCollisionInfo* collInfo)
{
    CPortalSet::gPortalSet->collisionDetection(collInfo);
}