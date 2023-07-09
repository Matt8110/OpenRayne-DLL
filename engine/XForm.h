#pragma once

#include <math.h>
#include "Vector.h"

class CXForm
{
public:
	float a, b, c;
	float d, e, f;
	float g, h, i;
	float j, k, l;

	CXForm operator * (const CXForm& other)
	{
		CXForm ret;
		ret.a = i * other.c + other.b * e + other.a * a;
		ret.b = other.c * j + b * other.a + f * other.b;
		ret.c = other.c * k + c * other.a + g * other.b;
		ret.e = i * other.g + other.e * a + other.f * e;
		ret.f = other.g * j + other.e * b + other.f * f;
		ret.g = other.g * k + other.e * c + other.f * g;
		ret.i = i * other.k + other.i * a + other.j * e;
		ret.j = other.k * j + other.i * b + other.j * f;
		ret.k = other.k * k + other.i * c + other.j * g;
		ret.d = other.c * l + d * other.a + h * other.b + other.d;
		ret.h = l * other.g + other.e * d + other.f * h + other.h;
		ret.l = other.k * l + other.i * d + other.j * h + other.l;

		return ret;
	}

	void setupLocalToParent(const CVector& position, const CVector& orientation);
	void setupParentToLocal(const CVector& position, const CVector& orientation);
	CVector extractPos_L2P();
	CVector extractPBH_L2P();

	//Matches
	void mul(const CXForm& Main, const CXForm& other);
};

