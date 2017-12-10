#pragma once

#include <SFML/Graphics.hpp>
#include "Collider.h"

using namespace sf;
using namespace std;

extern map<int, vector<Collider*>> collidersByLayer;

void AddCollider(Collider &collider, int layer);
void UpdateCollisions();