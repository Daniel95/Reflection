#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Window.h"
#include "Collider.h"

using namespace sf;
using namespace std;

static map<int, vector<Collider*>> colliderBodiesByLayer;

void UpdateCollisions() {
	for (auto const& x : colliderBodiesByLayer) {
		vector<Collider*> colliderBodies = x.second;
		for (size_t c = 0; c < colliderBodies.size(); c++) {
			Collider collider = *colliderBodies[c];
			colliderBodies.erase(remove(colliderBodies.begin(), colliderBodies.end(), colliderBodies[c]), colliderBodies.end());
			for (size_t oc = 0; oc < colliderBodies.size(); oc++) {
				collider.CheckCollision(*colliderBodies[oc]);
			}
		}
	}
}

void AddColliderBody(Collider &collider, int layer) {
	if (colliderBodiesByLayer.find(layer) == colliderBodiesByLayer.end()) {
		colliderBodiesByLayer[layer] = vector<Collider*>();
	}
	colliderBodiesByLayer[layer].push_back(&collider);
}
