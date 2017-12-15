#pragma once

#include <SFML/Graphics.hpp>
#include "Collider.h"

using namespace sf;
using namespace std;

extern map<int, vector<Collider*>> colliderBodiesByLayer;

void AddColliderBody(Collider &collider, int layer);
void UpdateCollisions();