#include "STD_TYPES.h"

sint32 Map(sint32 InputRangeMin, sint32 InputRangeMax , sint32 OutputRangeMin , sint32 OutputRangeMax , sint32 InputValue)
{
	return ( (OutputRangeMax - OutputRangeMin) / (InputRangeMax - InputRangeMin) ) * InputValue;
}
