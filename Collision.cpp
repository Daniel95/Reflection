#include "stdafx.h"
#include "Collision.h"
#include "Collider.h"

Collision::Collision(Collider &colliderOne, Collider &colliderTwo) : ColliderOne(colliderOne), ColliderTwo(colliderTwo) {}

Collision::~Collision() {}
