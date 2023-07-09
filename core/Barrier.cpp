#include "Barrier.h"

char* CBarrier::registryEntry;
int CBarrier::fileVersion = 2;

void CBarrier::patchFuncs()
{
    registryEntry = (char*)gBase + 0x1804680;

    //patchFunction(&CBarrier::_constructor, 0xF190);
    patchFunction(&CBarrier::_getActorType, 0xF180);
    patchFunction(&CBarrier::_archive, 0xF270);
    patchFunction(&CBarrier::_setup, 0xF1D0);
    patchFunction(&CBarrier::_setHasChanged, 0xF310);
    patchFunction(&CBarrier::_renderTransparent, 0xF260);
    patchFunction(&CBarrier::_collideWithMe, 0xF2C0);
}

CBarrier::CBarrier()
{
    size.x = 5.0f;
    size.y = 5.0f;
    size.z = 5.0f;
    effectClassNameList[0] = '\0';
    addToPathGrid = 1;
}

void CBarrier::archive()
{
    CDemonActor::archive();

    archiveVector(&size, "size");

    if (fileVersion > 1)
    {
        archiveString(effectClassNameList, "effectClassNameList");
        archiveInt(&addToPathGrid, "addToPathGrid");
    }
}

char* CBarrier::getActorType()
{
    return registryEntry;
}

void CBarrier::setup()
{
    CDemonActor::setup();

    visibilityFlagB = *(int*)CDemonMission::gSit + 0x1008;
    visibilityFlagA = 0;

    CBoundingBox3D tempBB;
    tempBB.x1 = -size.x * 0.5f;
    tempBB.y1 = -0.1f;
    tempBB.z1 = -size.z * 0.5f;
    tempBB.x2 = size.x * 0.5f;
    tempBB.y2 = size.y + 0.1f;
    tempBB.z2 = size.z * 0.5f;

    setBoundingBox(tempBB);
}

void CBarrier::setHasChanged()
{
    if (addToPathGrid)
    {
        CDemonSet::gSet->addBarrier(this);
    }
}

int CBarrier::renderTransparent()
{
    return 0;
}


//Appears to work, may need to revisit
int CBarrier::collideWithMe(CCollisionInfo& collInfo)
{
    if (collInfo.field_8 == 0)
    {
        if (effectClassNameList[0] == 0 || gSimActor == nullptr || gSimActor->isOfType(effectClassNameList))
        {
            return collideWithMyBoundingBox(collInfo);
        }
    }

    return 0;
}