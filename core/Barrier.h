#pragma once

#include "Actor.h"
#include "Mission.h"
#include "Set.h"

class CBarrier : public CDemonActor
{
public:
    CVector size;
    int addToPathGrid;
    char effectClassNameList[64];

    static int fileVersion;
    static char* registryEntry;

    static void patchFuncs();

    //Needed for virtual functions
    CBarrier* _constructor(){return ::new (this)CBarrier();}
    char* _getActorType(){return CBarrier::getActorType();}
    void _archive() {CBarrier::archive();}
    void _setup() {CBarrier::setup();}
    void _setHasChanged() {CBarrier::setHasChanged();}
    int _renderTransparent() {return CBarrier::renderTransparent();}
    int _collideWithMe(CCollisionInfo& collInfo){return CBarrier::collideWithMe(collInfo);}

    CBarrier();
    virtual void archive();
    virtual char* getActorType() override;
    virtual void setup() override;
    virtual void setHasChanged() override;
    virtual int renderTransparent() override;
    virtual int collideWithMe(CCollisionInfo& collInfo) override;

private:

};