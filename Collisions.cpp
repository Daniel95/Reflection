#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Window.h"
#include "Collisions.h"
#include "Collider.h"
#include "Collision.h"

using namespace sf;
using namespace std;

map<int, vector<Collider*>> colliderBodiesByLayer;
vector<Collision*> collisions;
vector<Collision*> outdatedCollisions;

void AddCollider(Collider &collider, int layer) {
	if (colliderBodiesByLayer.find(layer) == colliderBodiesByLayer.end()) {
		colliderBodiesByLayer[layer] = vector<Collider*>();
	}
	colliderBodiesByLayer[layer].push_back(&collider);
}

void RemoveCollider(Collider &collider, int layer) {
	if (colliderBodiesByLayer.find(layer) == colliderBodiesByLayer.end()) {
		cout << "Collider to remove not found!" << endl;
		return;
	}

	//Potentially remove active collisions
	for (size_t i = 0; i < collisions.size(); i++) {
		Collision& collision = *collisions[i];
		if (&collision.ColliderOne == &collider) {
			collision.ColliderTwo.DispatchCollisionExitEvent(collision.ColliderOne);

			collisions.erase(remove(collisions.begin(), collisions.end(), &collision), collisions.end());
			delete &collision;
		} else if (&collision.ColliderTwo == &collider) {
			collision.ColliderOne.DispatchCollisionExitEvent(collision.ColliderTwo);

			collisions.erase(remove(collisions.begin(), collisions.end(), &collision), collisions.end());
			delete &collision;
		}
	}

	//Remove collider from layer
	vector<Collider*>& colliderVector = colliderBodiesByLayer[layer];
	colliderVector.erase(remove(colliderVector.begin(), colliderVector.end(), &collider), colliderVector.end());

	if (colliderVector.size() == 0) {
		colliderBodiesByLayer.erase(layer);
	}
}

void UpdateCollisions() {
	outdatedCollisions = collisions;
	for (auto const& x : colliderBodiesByLayer) {
		vector<Collider*> colliders = x.second;
		int otherCollidersStartIndex = 0;

		for (size_t c = 0; c < colliders.size(); c++) {
			Collider &colliderOne = *colliders[c];
			otherCollidersStartIndex++;

			for (size_t oc = otherCollidersStartIndex; oc < colliders.size(); oc++) {
				Collider &colliderTwo = *colliders[oc];
				Vector2f colliderOnePush;
				Vector2f colliderTwoPush;
				if (colliderOne.CheckCollision(colliderTwo, colliderOnePush, colliderTwoPush)) {
					UpdateCollision(colliderOne, colliderTwo, colliderOnePush, colliderTwoPush);
				}
			}
		}
	}
	UpdateOutdatedCollisions();
}

void UpdateCollision(Collider &colliderOne, Collider &colliderTwo, Vector2f colliderOnePush, Vector2f colliderTwoPush) {
	Collision *collision = NULL;

	//Check if this collision already exists
	for (size_t i = 0; i < collisions.size(); i++) {
		bool collisionExists = (&colliderOne == &collisions[i]->ColliderOne || &colliderOne == &collisions[i]->ColliderTwo) && (&colliderTwo == &collisions[i]->ColliderOne || &colliderTwo == &collisions[i]->ColliderTwo);

		if (collisionExists) {
			collision = collisions[i];
			break;
		}
	}

	if (collision == NULL) { //Collision enter
		collision = new Collision(colliderOne, colliderTwo);
		collisions.push_back(collision);
		colliderOne.DispatchCollisionEnterEvent(colliderTwo, colliderOnePush);
		colliderTwo.DispatchCollisionEnterEvent(colliderOne, colliderTwoPush);
	} else { //Collision
		colliderOne.DispatchCollisionEvent(colliderTwo, colliderOnePush);
		colliderTwo.DispatchCollisionEvent(colliderOne, colliderTwoPush);
		outdatedCollisions.erase(remove(outdatedCollisions.begin(), outdatedCollisions.end(), collision), outdatedCollisions.end());
	}
}

void UpdateOutdatedCollisions() {
	for (size_t i = 0; i < outdatedCollisions.size(); i++) {
		Collision& outdatedCollision = *outdatedCollisions[i];

		outdatedCollision.ColliderOne.DispatchCollisionExitEvent(outdatedCollision.ColliderTwo);
		outdatedCollision.ColliderTwo.DispatchCollisionExitEvent(outdatedCollision.ColliderOne);

		collisions.erase(remove(collisions.begin(), collisions.end(), &outdatedCollision), collisions.end());
		delete &outdatedCollision;
	}
	outdatedCollisions.clear();
}
