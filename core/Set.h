#pragma once

#include "../patcher.h"
#include "../engine/Collision.h"
#include "PortalSet.h"

class CBarrier;

class CDemonSet
{
public:
    static void patchFuncs();

    static CDemonSet* gSet;

    void addBarrier(CBarrier* barrier);
    void collisionDetection(CCollisionInfo* collinfo);
};