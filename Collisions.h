#pragma once

#include <SFML/Graphics.hpp>
#include "Collider.h"
#include "Collision.h"

using namespace sf;
using namespace std;

extern map<int, vector<Collider*>> colliderBodiesByLayer;
extern vector<Collision*> collisions;

void AddCollider(Collider &collider, int layer);
void UpdateCollisions();
void UpdateCollisionEvents(Collider &colliderOne, Collider &colliderTwo, Vector2f colliderOnePush, Vector2f colliderTwoPush);