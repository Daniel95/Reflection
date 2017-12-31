#include "stdafx.h"
#include "Range.h"

Range::Range(int min, int max) {
	Min = min;
	Max = max;
	Size = max - min;
}