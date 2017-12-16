#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Window.h"
#include "Collisions.h"
#include "Collider.h"
#include "Collision.h"

using namespace sf;
using namespace std;

static map<int, vector<Collider*>> colliderBodiesByLayer;
static vector<Collision*> collisions;

void AddCollider(Collider &collider, int layer) {
	if (colliderBodiesByLayer.find(layer) == colliderBodiesByLayer.end()) {
		colliderBodiesByLayer[layer] = vector<Collider*>();
	}
	colliderBodiesByLayer[layer].push_back(&collider);
}

void UpdateCollisions() {
	for (auto const& x : colliderBodiesByLayer) {
		vector<Collider*> colliders = x.second;

		for (size_t c = 0; c < colliders.size(); c++) {
			Collider &colliderOne = *colliders[c];
			colliders.erase(remove(colliders.begin(), colliders.end(), colliders[c]), colliders.end());

			for (size_t oc = 0; oc < colliders.size(); oc++) {
				Collider &colliderTwo = *colliders[oc];
				Vector2f colliderOnePush;
				Vector2f colliderTwoPush;
				if (colliderOne.CheckCollision(colliderTwo, colliderOnePush, colliderTwoPush)) {
					UpdateCollisionEvents(colliderOne, colliderTwo, colliderOnePush, colliderTwoPush);
				}
			}
		}
	}
}

void UpdateCollisionEvents(Collider &colliderOne, Collider &colliderTwo, Vector2f colliderOnePush, Vector2f colliderTwoPush) {
	Collision *collisionPntr = NULL;
	for (size_t i = 0; i < collisions.size(); i++) {
		bool collisionExists = &colliderOne == &collisions[i]->ColliderOne || &colliderOne == &collisions[i]->ColliderTwo && &colliderTwo == &collisions[i]->ColliderOne || &colliderTwo == &collisions[i]->ColliderTwo;
		if (collisionExists) {
			collisionPntr = collisions[i];
			break;
		}
	}

	if (collisionPntr == NULL) {
		Collision collision(colliderOne, colliderTwo);
		collisionPntr = &collision;
	}
}
