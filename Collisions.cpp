#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Window.h"
#include "Collisions.h"
#include "Collider.h"
#include "Collision.h"

using namespace sf;
using namespace std;

map<int, vector<Collider*>> collidersByLayer;
vector<Collision*> collisions;
vector<Collision*> outdatedCollisions;

void AddCollider(Collider &collider, int layer) {
	if (collidersByLayer.find(layer) == collidersByLayer.end()) {
		collidersByLayer[layer] = vector<Collider*>();
	}
	collidersByLayer[layer].push_back(&collider);
}

void RemoveCollider(Collider &collider, int layer) {
	if (collidersByLayer.find(layer) == collidersByLayer.end()) {
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
	vector<Collider*>& colliderVector = collidersByLayer[layer];
	colliderVector.erase(remove(colliderVector.begin(), colliderVector.end(), &collider), colliderVector.end());

	if (colliderVector.size() == 0) {
		collidersByLayer.erase(layer);
	}
}

//Loop through all colliders to CheckCollision
//Check which collions are new, need to be updated or are outdated
void UpdateCollisions() {
	outdatedCollisions = collisions;

	vector<Collider*> colliders;
	int otherCollidersIndex;
	Vector2f colliderOnePush;
	Vector2f colliderTwoPush;

	for (auto const& x : collidersByLayer) {
		colliders = x.second;
		otherCollidersIndex = 0;

		for (size_t c = 0; c < colliders.size(); c++) {
			Collider &colliderOne = *colliders[c];
			otherCollidersIndex++;

			//Loop through all other colliders
			for (size_t oc = otherCollidersIndex; oc < colliders.size(); oc++) {
				Collider &colliderTwo = *colliders[oc];
				colliderOnePush;
				colliderTwoPush;

				//Check if there is a collision between these two colliders, if so update the collision
				if (colliderOne.CheckCollision(colliderTwo, colliderOnePush, colliderTwoPush)) {
					//If the collision already existed, and is still active, it is removed from the outdatedCollisions vector
					UpdateCollision(colliderOne, colliderTwo, colliderOnePush, colliderTwoPush);
				}
			}
		}
	}

	UpdateOutdatedCollisions();
}

void UpdateCollision(Collider &colliderOne, Collider &colliderTwo, Vector2f colliderOnePush, Vector2f colliderTwoPush) {
	Collision *collision = NULL;

	bool collisionExists;
	//Check if this collision already exists
	for (size_t i = 0; i < collisions.size(); i++) {
		collisionExists = (&colliderOne == &collisions[i]->ColliderOne || &colliderOne == &collisions[i]->ColliderTwo) && (&colliderTwo == &collisions[i]->ColliderOne || &colliderTwo == &collisions[i]->ColliderTwo);

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

//Dispatch OnCollisionExit for each collision that existed before this frame, but was not updated this frame
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
