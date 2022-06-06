#ifndef IMATH_H
#define IMATH_H

#include "IPrimitive.h"

#define PI 3.14159265f

namespace Ilmarin
{
	namespace Math
	{
		float AngleBetweenTwoPoints(float x1, float y1, float x2, float y2);
		float AngleBetweenTwoPoints(IPoint *p1, IPoint *p2);
		float Sqrt(float src);
		float Distance(float x1, float y1, float x2, float y2);
		float Distance(IPoint *p1, IPoint *p2);
	}
}

#endif
