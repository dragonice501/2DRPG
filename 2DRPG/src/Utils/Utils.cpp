#include "Utils.h"

float Clampf(const float v, const float min, const float max)
{
	if (v < min) return min;
	else if (v > max) return max;
	else return v;
}