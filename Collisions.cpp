#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Window.h"
#include "Collisions.h"
#include "Collider.h"

using namespace sf;
using namespace std;

static map<int, vector<Collider*>> colliderBodiesByLayer;
static vector<Collider*[2]> collisions;

void UpdateCollisions() {
	for (auto const& x : colliderBodiesByLayer) {
		vector<Collider*> colliderBodies = x.second;
		for (size_t c = 0; c < colliderBodies.size(); c++) {
			Collider &colliderOne = *colliderBodies[c];
			colliderBodies.erase(remove(colliderBodies.begin(), colliderBodies.end(), colliderBodies[c]), colliderBodies.end());
			for (size_t oc = 0; oc < colliderBodies.size(); oc++) {
				Collider &colliderTwo = *colliderBodies[c];

				/*
				Vector2f colliderOnePush;
				Vector2f colliderTwoPush;
				if (colliderOne.CheckCollision(colliderTwo, colliderOnePush, colliderTwoPush)) {
					UpdateCollisionEvents(colliderOne, colliderTwo, colliderOnePush, colliderTwoPush);
				}
				*/

				colliderOne.CheckCollision(colliderTwo);
			}
		}
	}
}

void UpdateCollisionEvents(Collider &colliderOne, Collider &colliderTwo, Vector2f colliderOnePush, Vector2f colliderTwoPush) {
	Collider* (*collisionPntr)[2] = NULL;
	for (size_t i = 0; i < collisions.size(); i++) {
		bool collisionExists = collisions[i][0] || collisions[i][1] && &colliderTwo == collisions[i][0] || collisions[i][1];
		if (collisionExists) {
			collisionPntr = &collisions[i];
			break;
		}
	}

	if (collisionPntr == NULL) {
		Collider* collision[2] = { &colliderOne, &colliderTwo };
		//collisions.push_back(collision);
		collisionPntr = &collision;
	}
}

void AddCollider(Collider &collider, int layer) {
	if (colliderBodiesByLayer.find(layer) == colliderBodiesByLayer.end()) {
		colliderBodiesByLayer[layer] = vector<Collider*>();
	}
	colliderBodiesByLayer[layer].push_back(&collider);
}
