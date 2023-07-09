#include "BoundingBox3D.h"

float CBoundingBox3D::computeBoundingSphereRadiusFromCenter()
{
	float tempX = x2 - x1;
	float tempY = y2 - y1;
	float tempZ = y2 - z1;

	return sqrtf(tempZ * tempZ + tempX * tempX + tempY * tempY);
}