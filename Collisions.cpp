#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Window.h"
#include "Collider.h"

using namespace sf;
using namespace std;

static map<int, vector<Collider*>> collidersByLayer;

void UpdateCollisions() {
	/*
	for (auto const& x : collidersByLayer) {
		vector<Collider*> colliders = x.second;
		for (size_t c = 0; c < colliders.size(); c++) {
			Collider* collider = colliders[c];
			colliders.erase(remove(colliders.begin(), colliders.end(), colliders[c]), colliders.end());
			for (size_t oc = 0; oc < colliders.size(); oc++) {
				Collider& otherCollider = *colliders[oc];
				collider->CheckCollision(otherCollider, 0.0f);
			}
		}
	}
	*/
	/*
	for (size_t l = 0; l < collidersByLayer.size(); l++) {
		vector<Collider*> colliders = collidersByLayer[l];
		for (size_t c = 0; c < colliders.size(); c++) {

			//NULLPNTR??
			//cout << colliders[c]->GetPosition().x << endl;



			//Collider* colliderPntr = colliders[c];
			//cout << c << endl;
			//cout << "this collider" << endl;
			//cout << colliderPntr->GetPosition().x << endl;
			colliders.erase(remove(colliders.begin(), colliders.end(), colliders[c]), colliders.end());
			for (size_t oc = 0; oc < colliders.size(); oc++) {
				//cout << oc << endl;
				//Collider* otherColliderPntr = colliders[oc];
				//cout << otherColliderPntr->GetPosition().x << endl;
				//Collider& otherColliderRef = *colliders[oc];
				//collider->CheckCollision(*otherCollider, 0.0f);
			}
		}
	}
	*/
}

void AddCollider(Collider &collider, int layer) {
	cout << collider.GetPosition().x << endl;

	if (collidersByLayer.find(layer) == collidersByLayer.end()) {
		collidersByLayer[layer] = vector<Collider*>();
	}
	collidersByLayer[layer].push_back(&collider);

	cout << "Positions" << endl;
	for (auto const& x : collidersByLayer) {
		vector<Collider*> colliders = x.second;
		for (size_t c = 0; c < colliders.size(); c++) {
			cout << colliders[c]->GetPosition().x << endl;
		}
	}
}
