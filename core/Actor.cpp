#include "Actor.h"

CDemonActor* CDemonActor::gSimActor;
FILE* CDemonActor::archiveInStream;
FILE* CDemonActor::archiveOutStream;
char* CDemonActor::archiveIndentString;
int* CDemonActor::archiveMode;

void CDemonActor::patchFuncs()
{
    gSimActor = *(CDemonActor**)gBase + 0x1804534;
    archiveInStream = *(FILE**)gBase + 0x1804538;
    archiveOutStream = *(FILE**)gBase + 0x180453C;
    archiveMode = (int*)gBase + 0x1804540;
    archiveIndentString = *(char**)gBase + 0x1804550;

    patchFunction(CDemonActor::_constructor, 0xEA90);
    patchFunction(CDemonActor::_warpTo, 0xE240);
    patchFunction(CDemonActor::attachActor, 0xE0B0);
    patchFunction(CDemonActor::detachMe, 0xD810);
    patchFunction(CDemonActor::_setup, 0xEBC0);
    patchFunction(CDemonActor::b2w, 0xDCC0);
    patchFunction(CDemonActor::applyAttachedListPosAndOrient, 0xD8A0);
    patchFunction(CDemonActor::_renderTransparent, 0xB9C0);
    patchFunction(_amIVisible, 0xB980);
    //patchFunction(_process, 0xDCB0);

}

CDemonActor::CDemonActor()
{
    field_D4 = 0x78A123;
    name[0] = '\0';
    field_148 = 0;
    field_14C = 0;
    position.x = 0;
    position.y = 0;
    position.z = 0;
    unkInt0 = 0;
    orientation.x = 0;
    orientation.y = 0;
    orientation.z = 0;
    orientationMatrix.Identity();
    field_68 = 150.0f;
    field_98 = 0xFFFFFFFF;
    field_A0 = 0xFFFFFFFF;
    group = nullptr;
    field_E4 = nullptr;
    field_E8 = 0;
    field_EC = nullptr;
    visibilityFlagA = 1;
    visibilityFlagB = 0;
    selfIlluminated = 0;
    field_FC = 0;
    field_100 = 0;
    field_64 = 100;
    field_98 = 0;
    field_9C = nullptr;
    field_B0 = 0;
    field_A4 = 0;
    field_A8 = 0;
    attachListStart = nullptr;
    attachListNext = nullptr;
    attachListPrev = nullptr;
    gettingHarpooned = 0;

    CBoundingBox3D tempBB;
    tempBB.x1 = 4.0f;
    tempBB.y1 = 8.0f;
    tempBB.z1 = 4.0f;
    tempBB.x2 = -4.0f;
    tempBB.y2 = 0.0f;
    tempBB.z2 = -4.0f;
    setBoundingBox(tempBB);
    
    computeDirMat();

    field_108 = 0;
    field_AC = 0;
}

void CDemonActor::setBoundingBox(CBoundingBox3D& bb)
{
    boundingBox.x1 = bb.x1;
    boundingBox.y1 = bb.y1;
    boundingBox.z1 = bb.z1;
    boundingBox.x2 = bb.x2;
    boundingBox.y2 = bb.y2;
    boundingBox.z2 = bb.z2;
    boundingBoxSize = bb.computeBoundingSphereRadiusFromCenter();
    b2w();
}

CVector CDemonActor::getFocusPoint()
{
    CVector ret;
    ret.x = focusPoint.x;
    ret.y = focusPoint.y;
    ret.z = focusPoint.z;

    return ret;
}

CVector CDemonActor::getLookAtPoint()
{
    CVector ret;
    ret.x = position.x;
    ret.y = position.y;
    ret.z = position.z;

    return ret;
}

void CDemonActor::applyAttachedListPosAndOrient()
{
    if (attachListStart != nullptr)
    {
        CXForm tempForm;
        CXForm tempFormB;
        tempForm.setupLocalToParent(position, orientation);

        for (CDemonActor* tempActor = attachListStart; tempActor != nullptr; tempActor = tempActor->attachListNext)
        {
            //tempFormB.mul(tempActor->xForm, tempForm);//Updated, should still match
            tempFormB = tempActor->xForm * tempForm;

            tempActor->CDemonActor::warpTo(tempFormB.extractPos_L2P(), tempFormB.extractPBH_L2P());
        }
    }
}

void CDemonActor::computeDirMat()
{
    orientation.x = CUtils::wrapPi(orientation.x);
    orientation.z = CUtils::wrapPi(orientation.z);
    orientation.y = CUtils::wrapPi(orientation.y);

    orientationMatrix.genMatrix(orientation);
    b2w();
}

void CDemonActor::warpTo(const CVector& newPos, const CVector& newOrient)
{
    orientation.x = newOrient.x;
    orientation.y = newOrient.y;
    orientation.z = newOrient.z;
    position.x = newPos.x;
    position.y = newPos.y;
    position.z = newPos.z;

    computeDirMat();
    applyAttachedListPosAndOrient();
}

void CDemonActor::b2w()
{
    float bbx = (boundingBox.x1 + boundingBox.x2);
    float bby = (boundingBox.y2 + boundingBox.y1);
    float bbz = (boundingBox.z2 + boundingBox.z1);

    float bbscaledX = bbx * 0.5f;
    float bbscaledY = bby * 0.5f;
    float bbscaledZ = bbz * 0.5f;

    focusPoint.x = bbscaledY * orientationMatrix.m10 + bbscaledX * orientationMatrix.m00 + bbscaledZ * orientationMatrix.m20 + position.x;
    focusPoint.y = orientationMatrix.m21 * bbscaledZ + orientationMatrix.m01 * bbscaledX + orientationMatrix.m11 * bbscaledY + position.y;
    focusPoint.z = bbscaledZ * orientationMatrix.m22 + orientationMatrix.m12 * bbscaledY + orientationMatrix.m02 * bbscaledX + position.z;
    
    FUN_0040d790(); 
}	

void CDemonActor::FUN_0040d790()
{

    if (field_98 >= 0)
    {
        CPortalSet::gPortalSet->putActorInBsp(this);
    }
}

bool CDemonActor::amIVisible()
{
    if (visibilityFlagA == 0 && visibilityFlagB == 0)
    {
        return 0;
    }

    return CPortalSet::gPortalSet->isActorVisible(this);
}

int CDemonActor::getHarpoonBone()
{
    return 0xFFFFFFFF;
}

void CDemonActor::setup()
{
    computeDirMat();

    if (attachListPrev != nullptr)
    {
        attachListPrev->attachActor(this);
    }
}

void CDemonActor::process()
{
    applyAttachedListPosAndOrient();
}

int CDemonActor::renderTransparent()
{
    return 0;
}

void CDemonActor::detachMe()
{
    CDemonActor* tempAttachListStart;
    CDemonActor* tempAttachListPrev = attachListPrev;

    if (tempAttachListPrev != nullptr)
    {
        CDemonActor* tempAttachListNext = attachListNext;
        attachListPrev = nullptr;
        attachListNext = nullptr;
        tempAttachListStart = tempAttachListPrev->attachListStart;

        if (tempAttachListPrev->attachListStart == this)
        {
            tempAttachListPrev->attachListStart = tempAttachListNext;
            return;
        }

        while(true)
        {
            tempAttachListPrev = tempAttachListStart;
            if (tempAttachListPrev == nullptr)
            {
                //gtfoSourceFile = "ACTOR.CPP";
                //gtfoSourceLine = 0xcd2;
                CUtils::reallyGTFO("Attach list corruption detected detaching \'%s\'", name);
            }

            if (tempAttachListPrev->attachListNext == this)
                break;

            tempAttachListStart = tempAttachListPrev->attachListNext;
        }

        tempAttachListStart->attachListNext = tempAttachListNext;
    }
}

void CDemonActor::attachActor(CDemonActor* actorToAttach)
{

    if (actorToAttach != nullptr)
    {
        actorToAttach->detachMe();

        for (CDemonActor* tempActor = this; tempActor != nullptr; tempActor = tempActor->attachListPrev)
        {
            if (tempActor == actorToAttach)
            {
                //reallyGTFOFile = "ACTOR.CPP";
                //reallyGTFOLine = 0xC91;
                CUtils::reallyGTFO("CDemonActor::attachActor - circular involving \'%s\' and \'%s\'", name, actorToAttach->name);
            }
        }

        actorToAttach->attachListPrev = this;
        actorToAttach->attachListNext = attachListStart;
        attachListStart = actorToAttach;

        CXForm localToParent;
        CXForm parentToLocal;

        localToParent.setupLocalToParent(actorToAttach->position, actorToAttach->orientation);
        parentToLocal.setupParentToLocal(position, orientation);

        CXForm res;
        res.mul(localToParent, parentToLocal);

        actorToAttach->xForm = res;
    }
}

int CDemonActor::amIHidden()
{
    return 0;
}

int CDemonActor::render()
{
    return 0;
}

void CDemonActor::archive()
{
    WRAP_JMPEAX(gBase + 0xE820);
}

void CDemonActor::archiveString(char* str, const char* name)
{
    WRAP_JMPEAX(gBase + 0xC790);
}

void CDemonActor::archiveInt(int* val, const char* name)
{
    /*if (*archiveMode == 1)
    {
        //if (archiveInStream->scanf("%d", val) != 1)
        if (fscanf(archiveInStream, "%d", val) != 1)
        {
            failedToLoadProperty("Integer value", name);
        }
    }
    else
    {
        //archiveOutStream->printf("%s%d", archiveIndentString, *val);
        fprintf(archiveOutStream, "%s%d", archiveIndentString, *val);
    }
    FUN_0040C490("Integer value", name);*/

    WRAP_JMPEAX(gBase + 0xC9C0);
}

void CDemonActor::archiveFloat(float* val, const char* name)
{
    /*if (archiveMode == 1)
    {
        if (archiveInStream->scanf("%f", val) != 1)
        {
            failedToLoadProperty("Floating point value", name);
        }
    }
    else
    {
        archiveOutStream->printf("%s%g", archiveIndentString, *val);
    }

    FUN_0040C490("Floating point value", name);*/
}

void CDemonActor::archiveVector(CVector* vec, const char* name)
{
    /*if (archiveMode == 1)
    {
        if (archiveInStream->scanf("%f,%f,%f", &vec->x, &vec->y, &vec->z) != 3)
        {
            failedToLoadProperty("3D vector", name);
        }
    }
    else
    {
        archiveOutStream->printf("%s%g,%g,%g", archiveIndentString, vec->x, vec->y, vec->z);
    }

    FUN_0040C490("3D vector", name);*/

    WRAP_JMPEAX(gBase + 0xC510);
}

void CDemonActor::archiveOrient(CVector* vec, const char* name)
{
    /*if (archiveMode == 1)
    {
        if (archiveInStream->scanf("%f,%f,%f", &vec->x, &vec->y, &vec->z) != 3)
        {
            failedToLoadProperty("Euler PBH orientation", name);
        }
    }
    else
    {
        archiveOutStream->printf("%s%g,%g,%g", archiveIndentString, vec->x, vec->y, vec->z);
    }

    FUN_0040C490("Euler PBH orientation", name);*/
}

char* CDemonActor::getActorType()
{
    /*gtfoSourceFile = "ACTOR.CPP";
    gtfoSourceLine = 0x346;*/
    CUtils::reallyGTFO("CDemonActor::getActorType called for %s.  Should never be called for this base class!", name);

    //Temp
    //printf("CDemonActor::getActorType called for %s.  Should never be called for this base class!", name);

    return nullptr;
}

void CDemonActor::setHasChanged()
{
    return;
}

int CDemonActor::collideWithMe(CCollisionInfo& collInfo)
{
    return 0;
}

int CDemonActor::vfunction15()
{
    return 0;
}

int CDemonActor::vfunction17()
{
    return 0;
}

int CDemonActor::vfunction19()
{
    return 0;
}

int CDemonActor::vfunction21()
{
    return 0;
}

void CDemonActor::vfunction22()
{
    return;
}

void CDemonActor::getHurt()
{
    return;
}

void CDemonActor::vfunction24()
{
    return;
}

void CDemonActor::vfunction25()
{
    return;
}

void CDemonActor::vfunction26()
{
    return;
}

int CDemonActor::vfunction27()
{
    return 0;
}

int CDemonActor::vfunction30()
{
    return 0;
}

void CDemonActor::vfunction31()
{
    return;
}

void CDemonActor::vfunction32()
{
    return;
}

void CDemonActor::vfunction33()
{
    return;
}

int CDemonActor::vfunction34()
{
    return 0;
}

int CDemonActor::vfunction35()
{
    return 0;
}

bool CDemonActor::vfunction42()
{
    return 0;
}

int CDemonActor::vfunction44()
{
    return 0;
}

int CDemonActor::vfunction5()
{
    return 0;
}

int CDemonActor::vfunction7()
{
    return 1;
}


//Wrapped
int CDemonActor::isOfType(const char* type)
{
    WRAP_JMPEAX(gBase + 0xEA60);
}

int CDemonActor::collideWithMyBoundingBox(CCollisionInfo& collInfo)
{
    WRAP_JMPEAX(gBase + 0xE780);
}

void CDemonActor::FUN_0040C490(const char* str, const char* name)
{
    WRAP_JMPEAX(gBase + 0xC490);
}
void CDemonActor::failedToLoadProperty(const char* str, const char* name)
{
    WRAP_JMPEAX(gBase + 0xC420);
}