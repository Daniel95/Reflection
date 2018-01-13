#include "stdafx.h"
#include "MathHelper.h"
#include <math.h>

float MathHelper::Length(Vector2f vector) {
	return sqrt(vector.x * vector.x + vector.y * vector.y);
}

float MathHelper::Length(float x, float y) {
	return sqrt(x * x + y * y);
}

Vector2f MathHelper::Normalize(Vector2f vector) {
	float length = MathHelper::Length(vector.x, vector.y);

	if (length != 0) {
		vector.x /= length;
		vector.y /= length;
	}

	return vector;
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