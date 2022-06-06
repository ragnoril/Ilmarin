#include <math.h>
#include "Math.h"

namespace Ilmarin
{
	namespace Math
	{
		float AngleBetweenTwoPoints(float x1, float y1, float x2, float y2)
		{
			return atan2(y2 - y1, x2 - x1) * 180 / PI;
		}

		float AngleBetweenTwoPoints(IPoint *p1, IPoint *p2)
		{
			return atan2(p2->y - p1->y, p2->x - p1->x) * 180 / PI;
		}

		float Sqrt(float src)
		{
			float t;
#if _MSC_VER > 1000
			_asm
			{
				fld src
				fsqrt
				fstp t
			}
			
#else
			t = sqrtf(src);
			//asm {"fld %1; fsqrt; fstp %0;":"=r"(t):"r"(src):};

#endif
			return t;
		}

		float Distance(float x1, float y1, float x2, float y2)
		{
			float a = x2 - x1;
			float b = y2 - y1;
			return Sqrt(a * a + b * b);
		}

		float Distance(IPoint *p1, IPoint *p2)
		{
			float a = (float)p2->x - p1->x;
			float b = (float)p2->y - p1->y;
			return Sqrt(a * a + b * b);
		}
	}
}
