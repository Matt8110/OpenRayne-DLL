#pragma once

#include "../patcher.h"
#include "../engine/Vector.h"
#include "../engine/Utils.h"
#include "../engine/Collision.h"
#include "../engine/Scratch.h"
#include "Set.h"

class CDemonParticle
{
public:
    CVector position;
    CVector field_C;
    CVector field_18;
    int field_24;
    int field_28;
    float field_2C; //Speed/num of particles?
    int field_30;
    int field_34;
    int field_38;
    int field_3C;
    int field_40;
    int field_44;
    float field_48;
    int field_4C;
    int field_50;
    int field_54;
    int field_58;

    static void patchFuncs();

    //Needed for virtual functions
    CDemonParticle* _constructorA(){return ::new CDemonParticle();}
    CDemonParticle* _constructorB(CDemonParticle* cpy){return ::new CDemonParticle(cpy);}
    int _hit(){return CDemonParticle::hit();}
    void _render(){CDemonParticle::render();}

    CDemonParticle();
    CDemonParticle(CDemonParticle* cpy);
    virtual int hit();
    virtual void render();
    virtual void create(CVector* pos, CVector* vel, float speed); //Just guesses
};