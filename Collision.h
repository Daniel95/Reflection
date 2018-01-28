#pragma once

#include "Collider.h"

//A collision is created when to colliders collide. It is used to easily keep track off all collisions.
class Collision {
public:
	Collision(Collider &colliderOne, Collider &colliderTwo);
	~Collision();

	Collider &ColliderOne;
	Collider &ColliderTwo;
};

