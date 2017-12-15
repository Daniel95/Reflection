#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Window.h"
#include "Collider.h"

using namespace sf;
using namespace std;

static map<int, vector<RectangleShape*>> colliderBodiesByLayer;

void UpdateCollisions() {
	for (auto const& x : colliderBodiesByLayer) {
		vector<RectangleShape*> colliderBodies = x.second;
		for (size_t c = 0; c < colliderBodies.size(); c++) {
			Collider collider = Collider(*colliderBodies[c]);
			colliderBodies.erase(remove(colliderBodies.begin(), colliderBodies.end(), colliderBodies[c]), colliderBodies.end());
			for (size_t oc = 0; oc < colliderBodies.size(); oc++) {
				collider.CheckCollision(Collider(*colliderBodies[oc]), 0.5f);
			}
		}
	}
}

void AddColliderBody(RectangleShape &colliderBody, int layer) {
	if (colliderBodiesByLayer.find(layer) == colliderBodiesByLayer.end()) {
		colliderBodiesByLayer[layer] = vector<RectangleShape*>();
	}
	colliderBodiesByLayer[layer].push_back(&colliderBody);
}
