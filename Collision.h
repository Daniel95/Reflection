#pragma once

#include "Collider.h"

class Collision {
public:
	Collision(Collider &colliderOne, Collider &colliderTwo);
	~Collision();

	Collider &ColliderOne;
	Collider &ColliderTwo;
};

