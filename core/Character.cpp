#include "Character.h"


void CCharacter::patchFuncs()
{
    //patchFunction(&_getAimPoint, 0x2C6E0);
    patchFunction(&CCharacter::_vfunction7, 0x2C6D0);
    patchFunction(&CCharacter::_vfunction71, 0x2A7B0);
    patchFunction(&CCharacter::_vfunction72, 0x2A7C0);
    patchFunction(&CCharacter::_vfunction73, 0x2A520);
    patchFunction(&CCharacter::_setScriptTurnToFace, 0x2A770);
    patchFunction(&CCharacter::_vfunction66, 0x2A9E0);
    //patchFunction(&CCharacter::_warpTo, 0x27E80);
}

int CCharacter::getDeadState()
{
    /*char* str;

    //HMMMMMMMMMMMMMMm, no idea wtf is going on here...may not be a char pointer
    if (field_d0 != (char*)0x78A123)
    {
        return 2;
    }

    str = field_1f8->FUN_4D9AE0();

    if (str[0] == 'D' || str[0] == 'd')
    {
        if (!strncmp(str, "DIE", 3))
        {
            return 1;
        }

        if (!strncmp(str, "DEAD", 4))
        {
            return 2;
        }
 
        if (!strcmp(str, "DEAD_POSSUM"))
        {
            return 0xFFFFFFFE;
        }
    }*/

    return 0;
}

//This is just weird, man
int CCharacter::getAimPoint(CVector& vec)
{
    if (getDeadState() != 0)
    {
        return 0;
    }

    CVector temp;
    CVector temp2;
    
    temp.x = boundingBox.x1 + boundingBox.x2;
    temp.y = boundingBox.y2 + boundingBox.y1;
    temp.z = boundingBox.z2 + boundingBox.z1;

    temp2.x = temp.x * 0.5f;
    temp2.y = temp.y * 0.5f;
    temp2.z = temp.z * 0.5f;

    vec.x = temp2.x;
    vec.z = temp2.z;
    vec.y = temp2.y + 1.0f;

    return 1;
}

void CCharacter::vfunction71(float val)
{
    field_5d4 = val;
}

int CCharacter::vfunction72()
{
    if (field_458 == 0)
    {
        return 1;
    }

    if (field_468 == 0)
    {
        return field_46c == 0;
    }

    return 0;
}

int CCharacter::vfunction73()
{
    return 0;
}

int CCharacter::vfunction7()
{
    return 0;
}

//Not completely equivelent
void CCharacter::warpTo(const CVector& newPos, const CVector& newOrient)
{
    if (position.x != newPos.x || position.z != newPos.z || fabs(newPos.y - position.y) > 5.0f)
    {
        field_51c = 9999.0f;
    }

    CDemonActor::warpTo(newPos, newOrient);

    field_53c.x = 0;
    field_53c.y = 0;
    field_53c.z = 0;
}

void CCharacter::setScriptTurnToFace(CDemonActor* act)
{
    field_45c = -1.0f;
    field_458 = act;
    field_460 = 1000000000000000000000000000000.0f; //May be wrong... but wtf?
    field_468 = 1.000001f;
    vfunction71(-1.0f);
}

int CCharacter::vfunction66()
{
    return field_46c == 0;
}