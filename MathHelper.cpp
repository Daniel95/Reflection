#include "stdafx.h"
#include "MathHelper.h"
#include <math.h>

float MathHelper::Length(float x, float y) {
	return sqrt(x * x + y * y);
}

Vector2f MathHelper::Normalize(float x, float y) {
	float length = MathHelper::Length(x, y);

	Vector2f vector;
	if (length != 0) {
		vector.x = x / length;
		vector.y = y / length;
	}

	return vector;
}