#include "MathH.h"
#include <iostream>
#include <Windows.h>

namespace Math
{
	float distance(float x1, float y1, float x2, float y2)
	{
		return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
	}

	Vec3 WorldToScreen(const Vec3& boneLocation, const viewMatrix& vm)
	{
		// TODO:
	}
}
