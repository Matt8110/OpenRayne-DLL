#include "Collision.h"

void CCollisionInfo::setDefaults()
{
    WRAP_JMPEAX(gBase + 0x121E10);
}

void CCollisionInfo::ignoreAllActors()
{
    WRAP_JMPEAX(gBase + 0x11C8A0);
}

void CCollisionInfo::setupParticle(CVector& vecA, CVector& vecB, CVector& vecC, float flt)
{
    WRAP_JMPEAX(gBase + 0x11E030);
}