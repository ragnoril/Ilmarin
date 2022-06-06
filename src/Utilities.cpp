#include "Utilities.h"
#include <cstdlib>

namespace Ilmarin
{
	namespace Util
	{
		int RandomNumber(int lowerLimit, int upperLimit)
		{
            return (rand() % upperLimit + lowerLimit);
		}
	}
}
