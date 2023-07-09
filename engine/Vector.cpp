#include "Vector.h"

CVector::CVector()
{
	x = 0;
	y = 0;
	z = 0;
}

CVector::CVector(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}