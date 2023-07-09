#pragma once

#include "../patcher.h"
#include "../engine/Utils.h"
#include "../engine/Collision.h"

//I really hate this
class CDemonActor;

class CPortalSet
{
public:
    u8 data[2048]; //Unknown size
    static CPortalSet* gPortalSet;

    //Patchesss
    static void patchFuncs();

    void putActorInBsp(CDemonActor* actor) WRAP_FUNC;
    int isActorVisible(CDemonActor* actor) WRAP_FUNC;
    int collisionDetection(CCollisionInfo* collInfo) WRAP_FUNC;
};