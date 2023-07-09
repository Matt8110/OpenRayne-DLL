#pragma once

#include "../patcher.h"

#include <iostream>
#include <string>
#include <windows.h>
#include <stdio.h>
#include "../engine/Matrix.h"
#include "../engine/Vector.h"
#include "../engine/XForm.h"
#include "../engine/BoundingBox3D.h"
#include "../engine/Utils.h"
#include <stdio.h>
#include "../engine/Mini3D.h"
#include "PortalSet.h"
#include "../engine/BitFont.h"
#include "../engine/Collision.h"


#define ___fastcall __attribute__((regparm(2)))
#define STDCALL __attribute__((stdcall))
#define THISCALL __attribute__((thiscall))

class CActorType
{
public:
	char* unk[63];

private:
};

class CDemonActor
{
public:
    char name[32];
	CVector position;
	int unkInt0;
	CVector orientation;
	CMatrix orientationMatrix;
	int field_64;
	float field_68; //Intial jump velocity?
	float boundingBoxSize;
	CVector focusPoint;
	CBoundingBox3D boundingBox;
	int field_94;
	int field_98;//Room?
	CDemonActor* field_9C; //Next actor?
	int field_A0;//maybe room??
	int field_A4;//Counts up, maybe a timer?
	int field_A8;//Same as A4
	int field_AC;
	int field_B0;//1 and changes to 2 when moving around in certain spots. 
	int field_B4;//Also possibly room
	int field_B8;//Maybe also?
	int field_BC;
	int field_C0;
	int field_C4;
	float lightMin;
	float lightMax;
	int field_D0;
	int field_D4;
	char* group;
	int field_DC;
	int field_E0;
	CDemonActor* field_E4;
	CDemonActor* field_E8;
	CDemonActor* field_EC;
	int visibilityFlagA;//0xF0
	int visibilityFlagB;//0xF4
	int selfIlluminated;
	int field_FC;
	int field_100;
	int gettingHarpooned; //I think?
	int field_108;
	CDemonActor* attachListStart;
	CDemonActor* attachListNext;
	CDemonActor* attachListPrev; //Could possibly be attachListParent?
	CXForm xForm;
	CDemonActor* field_148;
	CDemonActor** field_14C;
	static int* archiveMode;
	static FILE* archiveInStream;
	static FILE* archiveOutStream;
	static CDemonActor* gSimActor;
	static char* archiveIndentString;

	static void patchFuncs();
	void test();

	//WRAPPED
	void archive() WRAP_FUNC;
	static void archiveString(char* str, const char* name) WRAP_FUNC;
	int isOfType(const char* type) WRAP_FUNC;
	int collideWithMyBoundingBox(CCollisionInfo& collInfo) WRAP_FUNC;
	static void FUN_0040C490(const char* str, const char* name) WRAP_FUNC;
	static void failedToLoadProperty(const char* str, const char* name) WRAP_FUNC;

	//Needed for virtual functions
	CDemonActor* _constructor(){return ::new (this)CDemonActor();}
	void _setup(){CDemonActor::setup();}
	void _process(){CDemonActor::process();}
	void _warpTo(const CVector& newPos, const CVector& newOrient){CDemonActor::warpTo(newPos, newOrient);}
	int _amIVisible(){return CDemonActor::amIVisible();}
	int _renderTransparent(){return CDemonActor::renderTransparent();}

	//Should be equivelent. Works when replaced in game
	CDemonActor();
	//Should be equivelent. Works when replaced in game
	void b2w();
	//Close to matching, but can't quite get it. Should be equivelent
	void attachActor(CDemonActor* actorToAttach);

	//Matching
	void detachMe();
	void FUN_0040d790();
	void applyAttachedListPosAndOrient();
	void computeDirMat();
	void setBoundingBox(CBoundingBox3D& bb);

	virtual void warpTo(const CVector& newPos, const CVector& newOrient);
	virtual bool amIVisible();
	virtual CVector getFocusPoint();
	virtual int getHarpoonBone();
	virtual CVector getLookAtPoint();
	virtual void process();//For some reason my test uses JMP instead of CALL.
	virtual int renderTransparent();
	virtual void setHasChanged();
	virtual void setup();
	virtual int amIHidden();
	virtual int render();
	virtual char* getActorType(); //Should return CActorType* instead of char*
	virtual void getHurt();
	virtual int collideWithMe(CCollisionInfo& collInfo);
	virtual int vfunction15();
	virtual int vfunction17();
	virtual int vfunction19();
	virtual int vfunction21();
	virtual void vfunction22();
	virtual void vfunction24();
	virtual void vfunction25();
	virtual void vfunction26();
	virtual int vfunction27();
	virtual int vfunction30();
	virtual void vfunction31();
	virtual void vfunction32();
	virtual void vfunction33();
	virtual int vfunction34();
	virtual int vfunction35();
	virtual bool vfunction42();
	virtual int vfunction44();
	virtual int vfunction5();
	virtual int vfunction7();
	
	static void archiveInt(int* val, const char* name) WRAP_FUNC;
	static void archiveFloat(float* val, const char* name);
	static void archiveVector(CVector* vec, const char* name) WRAP_FUNC;
	static void archiveOrient(CVector* vec, const char* name);
};