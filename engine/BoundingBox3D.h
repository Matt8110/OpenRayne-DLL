#pragma once

#include <math.h>

class CBoundingBox3D
{
public:
	float x1, y1, z1;
	float x2, y2, z2;

	float computeBoundingSphereRadiusFromCenter();

	CBoundingBox3D operator = (CBoundingBox3D other)
	{
		x1 = other.x1;
		y1 = other.y1;
		z1 = other.z1;
		x2 = other.x2;
		y2 = other.y2;
		z2 = other.z2;

		return *this;
	}
};

