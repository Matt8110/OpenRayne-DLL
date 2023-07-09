#include "Particle.h"

void CDemonParticle::patchFuncs()
{
    patchFunction(&CDemonParticle::_constructorA, 0xEF370);
    patchFunction(&CDemonParticle::_constructorB, 0x6A6B0);
    patchFunction(&CDemonParticle::_hit, 0xEF335);
    patchFunction(&CDemonParticle::_render, 0xEF310);
}

CDemonParticle::CDemonParticle()
{
    field_28 = 0;
    field_24 = 1;

    //Was in FUN_004EEEF0
    field_2C = 0;
    field_30 = -1;
    field_34 = -1;
    field_38 = 0;
}

CDemonParticle::CDemonParticle(CDemonParticle* cpy)
{
    position.x = cpy->position.x;
    position.y = cpy->position.y;
    position.z = cpy->position.z;
    field_C.x = cpy->field_C.x;
    field_C.y = cpy->field_C.y;
    field_C.z = cpy->field_C.z;
    field_18.x = cpy->field_18.x;
    field_18.y = cpy->field_18.y;
    field_18.z = cpy->field_18.z;
    field_24 = cpy->field_24;
    field_28 = cpy->field_28;
    field_2C = cpy->field_2C;
    field_30 = cpy->field_30;
    field_34 = cpy->field_34;
    field_38 = cpy->field_38;
    field_3C = cpy->field_3C;
    field_40 = cpy->field_40;
    field_44 = cpy->field_44;
    field_48 = cpy->field_48;
    field_4C = cpy->field_4C;
    field_50 = cpy->field_50;
    field_54 = cpy->field_54;
    field_58 = cpy->field_58;
}

int CDemonParticle::hit()
{
    return 1;
}

void CDemonParticle::render()
{
    CUtils::reallyGTFO("Base class shouldn\'t render");
}

void CDemonParticle::create(CVector* pos, CVector* vel, float speed)
{
    field_18.x = 0;
    field_18.y = -32.0f;
    field_18.z = 0;
    field_30 = -1;
    field_34 = -1;
    field_38 = 0;
    position.x = pos->x;
    position.y = pos->y;
    position.z = pos->z;

    if (vel != nullptr)
    {
        float tempRandA = CUtils::fRand(0.78539819f, 1.5707964f);
        float tempRandB = CUtils::fRand(0.0f, 6.2831855f);

        float fVar7 = cosf(tempRandB);
        float dVar5 = fVar7;
        fVar7 = sinf(tempRandB);
        tempRandB = fVar7;
        fVar7 = cosf(tempRandA);
        float dVar6 = fVar7;
        fVar7 = sinf(tempRandA);
        tempRandA = 10.0f;

        field_C.x = dVar6 * (tempRandA * dVar5);
        field_C.y = tempRandA * fVar7;
        field_C.z = dVar6 * (tempRandA * tempRandB);
    }
    else
    {
        field_C.x = vel->x;
        field_C.y = vel->y;
        field_C.z = vel->z;
    }

    field_2C = speed;
    field_24 = 1;

    if (field_28 == 0)
    {
        CCollisionInfo* collInfo = (CCollisionInfo*)pushScratchMemory(sizeof(CCollisionInfo));
        collInfo->setDefaults();
        collInfo->ignoreAllActors();
        collInfo->setupParticle(position, field_C, field_18, field_2C);
        CDemonSet::gSet->collisionDetection(collInfo);

        //if (field_18 != nullptr)
    }
}