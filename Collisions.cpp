#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Window.h"
#include "Collider.h"

using namespace sf;
using namespace std;

map<int, vector<Collider&>> collidersByLayer;

static void UpdateCollisions() {
	for (int l = 0; l < collidersByLayer.size(); l++) {
		vector<Collider&> colliders = collidersByLayer[l];
		for (int c = 0; c < colliders.size(); c++) {
			Collider& collider = colliders[c];
			colliders.erase(remove(colliders.begin(), colliders.end(), collider), colliders.end());
			for (int oc = 0; oc < colliders.size(); oc++) {
				collider.CheckCollision(colliders[oc], 0.0f);
			}
		}
	}
}

void AddCollider(Collider &collider, int layer) {
	if (collidersByLayer.find(layer) == collidersByLayer.end()) {
		collidersByLayer[layer] = vector<Collider&>();
	}
	collidersByLayer[layer].push_back(collider);
}