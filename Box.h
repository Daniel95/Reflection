#pragma once
#include <SFML\Graphics.hpp>
#include "Collider.h"
#include "LevelObject.h"

using namespace sf;

class Box : public LevelObject {
private:
	Collider collider = Collider(Body);
public:
	Box(Vector2f position, Vector2f size, float mass);
	~Box();
};

