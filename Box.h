#pragma once
#include <SFML\Graphics.hpp>
#include "Collider.h"

using namespace sf;

class Box {
public:
	Box(Vector2f position, Vector2f size);
	~Box();
	Collider GetCollider() { return Collider(body); }
private:
	RectangleShape body;
};

