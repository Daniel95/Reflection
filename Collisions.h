#pragma once

#include <SFML/Graphics.hpp>
#include "Collider.h"

using namespace sf;
using namespace std;

extern map<int, vector<RectangleShape*>> colliderBodiesByLayer;

void AddColliderBody(RectangleShape &collider, int layer);
void UpdateCollisions();