#include "XForm.h"

void CXForm::setupLocalToParent(const CVector& position, const CVector& orientation)
{
	float sinX = sinf(orientation.x);
	float cosX = cosf(orientation.x);
	float sinZ = sinf(orientation.z);
	float cosZ = cosf(orientation.z);
	float sinY = sinf(orientation.y);
	float cosY = cosf(orientation.y);

	a = cosY * cosZ + sinZ * sinY * sinX;
	b = -cosY * sinZ + cosZ * sinY * sinX;
	c = sinY * cosX;
	e = sinZ * cosX;
	f = cosZ * cosX;
	g = -sinX;
	i = -sinY * cosZ + sinZ * cosY * sinX;
	j = sinZ * sinY + cosZ * cosY * sinX;
	k = cosY * cosX;
	d = position.x;
	h = position.y;
	l = position.z;
}


void CXForm::setupParentToLocal(const CVector& position, const CVector& orientation)
{
	float sinX = sinf(orientation.x);
	float cosX = cosf(orientation.x);
	float sinZ = sinf(orientation.z);
	float cosZ = cosf(orientation.z);
	float sinY = sinf(orientation.y);
	float cosY = cosf(orientation.y);

	a = cosY * cosZ + sinZ * sinY * sinX;
	e = -cosY * sinZ + cosZ * sinY * sinX;
	i = sinY * cosX;
	b = sinZ * cosX;
	f = cosZ * cosX;
	j = -sinX;
	c = -sinY * cosZ + sinZ * cosY * sinX;
	g = sinZ * sinY + cosZ * cosY * sinX;
	k = cosY * cosX;
	d = -(position.z * c + position.x * a + position.y * b);
	h = -(position.z * g + position.x * e + position.y * f);
	l = -(position.z * k + position.x * i + position.x * j);
}

void CXForm::mul(const CXForm& Main, const CXForm& other)
	{
		a = Main.i * other.c + other.b * Main.e + other.a * Main.a;
		b = other.c * Main.j + Main.b * other.a + Main.f * other.b;
		c = other.c * Main.k + Main.c * other.a + Main.g * other.b;
		e = Main.i * other.g + other.e * Main.a + other.f * Main.e;
		f = other.g * Main.j + other.e * Main.b + other.f * Main.f;
		g = other.g * Main.k + other.e * Main.c + other.f * Main.g;
		i = Main.i * other.k + other.i * Main.a + other.j * Main.e;
		j = other.k * Main.j + other.i * Main.b + other.j * Main.f;
		k = other.k * Main.k + other.i * Main.c + other.j * Main.g;
		d = other.c * Main.l + Main.d * other.a + Main.h * other.b + other.d;
		h = Main.l * other.g + other.e * Main.d + other.f * Main.h + other.h;
		l = other.k * Main.l + other.i * Main.d + other.j * Main.h + other.l;
	}

CVector CXForm::extractPos_L2P()
{
	CVector ret;
	ret.x = d;
	ret.y = h;
	ret.z = l;

	return ret;
}

CVector CXForm::extractPBH_L2P()
{
	float tempA;
	float tempB;
	CVector ret;

	ret.y = c * c + a * a + b * b;

	if (ret.y > 0)
	{
		ret.z = 1.0f / sqrtf(ret.y);
		ret.z = 0.5f * ret.z * -(ret.y * ret.z * ret.z - 3.0f);//?????? the fuck?
		ret.z = 0.5f * ret.z * -(ret.y * ret.z * ret.z - 3.0f);
		ret.z = 0.5f * ret.z * -(ret.y * ret.z * ret.z - 3.0f);
		ret.y = ret.y * 0.5f * ret.z * -(ret.y * ret.z * ret.z - 3.0f);
	}

	if (ret.y > 0)
	{
		ret.y = 1.0f / ret.y;
	}

	ret.z = g * g + e * e + f * f;

	if (ret.z > 0)
	{
		tempA = 1.0f / sqrtf(ret.z);
		tempA = 0.5f * -(ret.z * tempA * tempA - 3.0f);
		tempA = 0.5f * -(ret.z * tempA * tempA - 3.0f);
		tempA = 0.5f * -(ret.z * tempA * tempA - 3.0f);
		ret.z = ret.z * 0.5f * tempA * -(ret.z * tempA * tempA - 3.0f);
	}

	if (ret.z > 0)
	{
		ret.z = 1.0f / ret.z;
	}

	tempA = k * k + i * i + j * j;
	if (tempA > 0)
	{
		ret.x = 1.0f / sqrtf(tempA);
		ret.x = 0.5f * ret.x - (tempA * ret.x * ret.x - 3.0f);
		ret.x = 0.5f * ret.x - (tempA * ret.x * ret.x - 3.0f);
		ret.x = 0.5f * ret.x - (tempA * ret.x * ret.x - 3.0f);
		tempA = tempA * 0.5f * ret.x * -(tempA * ret.x * ret.x - 3.0f);
	}

	if (tempA > 0)
	{
		tempA = 1.0f / tempA;
	}

	tempB = -g * ret.z;

	if (tempB >= -0.99999f) //Rounding error?
	{
		if (tempB <= 0.999999f)
		{
			ret.z = -(tempB * tempB - 1.0f);
			
			if (ret.z > 0)
			{
				ret.x = 1.0f / sqrtf(ret.z);
				ret.x = 0.5f * ret.x * -(ret.z * ret.x * ret.x - 3.0f);
				ret.x = 0.5f * ret.x * -(ret.z * ret.x * ret.x - 3.0f);
				ret.x = 0.5f * ret.x * -(ret.z * ret.x * ret.x - 3.0f);
				ret.z = ret.z * 0.5f * ret.x * -(ret.z * ret.x * ret.x - 3.0f);
			}

			tempB = asinf(tempB);
			ret.x = tempB;

			if (ret.x < -3.1415927f)
			{
				ret.x = ret.x + 6.2831855f;
			}
		}
		else
		{
			ret.z = 0;
			ret.x = 1.5707964f;
		}
	}
	else
	{
		ret.z = 0;
		ret.x = -1.5707964f;
	}

	if (ret.z >= -4.2817f)
	{
		tempB = atan2f(c * ret.y, k * tempA);
		ret.y = tempB;
		tempB = atan2f(e, f);
		ret.z = tempB;
	}
	else
	{
		ret.z = 0;
		tempB = atan2f(i * tempA, a * ret.y);
		ret.y = tempB;
	}

	return ret;
}