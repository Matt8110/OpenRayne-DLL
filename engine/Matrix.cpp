#include "Matrix.h"

void CMatrix::genMatrix(const CVector& vector)
{
	float sinX = sinf(vector.x);
	float cosX = cosf(vector.x);
	float sinZ = sinf(vector.z);
	float cosZ = cosf(vector.z);
	float sinY = sinf(vector.y);
	float cosY = cosf(vector.y);

	m00 = cosY * cosZ + sinZ * sinY * sinX;
	m10 = -cosY * sinZ + cosZ * sinY * sinX;
	m20 = sinY * cosX;
	m01 = sinZ * cosX;
	m11 = cosZ * cosX;
	m21 = -sinX;
	m02 = -sinY * cosZ + sinZ * cosY * sinX;
	m12 = sinZ * sinY + cosZ * cosY * sinX;
	m22 = cosY * cosX;
}

void CMatrix::Identity()
{
	m22 = 1.0f;
	m11 = 1.0f;
	m00 = 1.0f;
	m02 = 0.0f;
	m01 = 0.0f;
	m12 = 0.0f;
	m10 = 0.0f;
	m21 = 0.0f;
	m20 = 0.0f;
}