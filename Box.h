#pragma once
#include <SFML\Graphics.hpp>
#include "Collider.h"
#include "GameObject.h"

using namespace sf;

const int boxDrawLayer = 5;

class Box : public GameObject {
private:
	Collider collider = Collider(*this);
public:
	Box(Vector2f position, Vector2f size, float mass);
	~Box();
};

