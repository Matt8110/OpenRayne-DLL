#pragma once

#include <math.h>
#include "Vector.h"

class CMatrix
{
public:
	float m00, m10, m20;
	float m01, m11, m21;
	float m02, m12, m22;

	void genMatrix(const CVector& vector);
	void Identity();
};