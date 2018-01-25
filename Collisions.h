#pragma once

#include <SFML/Graphics.hpp>
#include "Collider.h"
#include "Collision.h"

using namespace sf;
using namespace std;

void AddCollider(Collider &collider, int layer);
void RemoveCollider(Collider &collider, int layer);
void UpdateCollisions();
void UpdateCollision(Collider &colliderOne, Collider &colliderTwo, Vector2f colliderOnePush, Vector2f colliderTwoPush);
void UpdateOutdatedCollisions();