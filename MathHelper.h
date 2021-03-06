#pragma once

#include "stdafx.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class MathHelper {
public:
	static float Length(Vector2f vector);
	static float Length(float x, float y);
	static Vector2f Normalize(Vector2f vector);
	static Vector2f Normalize(float x, float y);
};

