#pragma once

#include "../patcher.h"
#include "Vector.h"

class CCollisionInfo
{
public:
	int field_0;
	int field_4;
	int field_8;
	char unk[0x918];

	void setDefaults() WRAP_FUNC;
	void ignoreAllActors() WRAP_FUNC;
	void setupParticle(CVector& vecA, CVector& vecB, CVector& vecC, float flt) WRAP_FUNC;
};