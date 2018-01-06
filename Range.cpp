#include "stdafx.h"
#include "Range.h"

Range::Range(int _min, int _max) {
	min = _min;
	max = _max;
	size = _max - _min;
}