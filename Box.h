#pragma once
#include <SFML\Graphics.hpp>
#include "Collider.h"

using namespace sf;

class Box {
private:
	RectangleShape body;
public:
	Box(Vector2f position, Vector2f size);
	~Box();
};

