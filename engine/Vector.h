#pragma once

#include <math.h>


class CVector
{
public:
	float x, y, z;

	CVector();
	CVector(float x, float y, float z);

	CVector operator = (const CVector otherVec)
	{
		x = otherVec.x;
		y = otherVec.y;
		z = otherVec.z;

		return *this;
	}

	CVector operator + (const CVector& otherVec)
	{
		CVector result;
		result.x = otherVec.x + x;
		result.y = otherVec.y + y;
		result.z = otherVec.z + z;

		return result;
	}

	CVector operator - (const CVector& otherVec)
	{
		CVector result;
		result.x = x - otherVec.x;
		result.y = y - otherVec.y;
		result.z = z - otherVec.z;

		return result;
	}
};
