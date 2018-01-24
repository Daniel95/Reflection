#include "stdafx.h"
#include <iostream>
#include "Collider.h"

using namespace std;

Collider::Collider(GameObject &gameObject, float mass) : gameObject(gameObject), body(gameObject.Body) {
	Mass = mass;
}

Collider::Collider(GameObject &gameObject) : gameObject(gameObject), body(gameObject.Body) { }

Collider::~Collider() {
	CollisionEnterEvent.clear();
	CollisionEvent.clear();
	CollisionExitEvent.clear();
}

bool Collider::CheckCollision(Collider& other, Vector2f &thisPush, Vector2f &otherPush) {
	Vector2f otherPosition = other.GetPosition();
	Vector2f otherHalfSize = other.GetHalfSize();

	Vector2f thisPosition = GetPosition();
	Vector2f thisHalfSize = GetHalfSize();

	float deltaX = otherPosition.x - thisPosition.x;
	float deltaY = otherPosition.y - thisPosition.y;
	float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
	float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

	if (intersectX < 0.0f && intersectY < 0.0f) {
		float combinedMass = Mass + other.Mass;
		float axisPush = Mass / combinedMass;

		if (intersectX > intersectY) {
			if (deltaX > 0.0f) {
				thisPush = Vector2f(intersectX * (1.0f - axisPush), 0.0f);
				otherPush = Vector2f(-intersectX * axisPush, 0.0f);
			} else {
				thisPush = Vector2f(-intersectX * (1.0f - axisPush), 0.0f);
				otherPush = Vector2f(intersectX * axisPush, 0.0f);
			}
		} else {
			if (deltaY > 0.0f) {
				thisPush = Vector2f(0.0f, intersectY * (1.0f - axisPush));
				otherPush = Vector2f(0.0f, -intersectY * axisPush);
			} else {
				thisPush = Vector2f(0.0f, -intersectY * (1.0f - axisPush));
				otherPush = Vector2f(0.0f, intersectY * axisPush);
			}
		}

		Move(thisPush);
		other.Move(otherPush);

		return true;
	}

	return false;
}


bool Collider::CheckCollision(Collider& other) {
	//body.getGlobalBounds().intersects(other.body.getGlobalBounds());

	Vector2f otherPosition = other.GetPosition();
	Vector2f otherHalfSize = other.GetHalfSize();

	Vector2f thisPosition = GetPosition();
	Vector2f thisHalfSize = GetHalfSize();

	float deltaX = otherPosition.x - thisPosition.x;
	float deltaY = otherPosition.y - thisPosition.y;
	float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
	float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

	if (intersectX < 0.0f && intersectY < 0.0f) {
		float combinedMass = Mass + other.Mass;
		float push = Mass / combinedMass;

		if (intersectX > intersectY) {
			if (deltaX > 0.0f) {
				Move(intersectX * (1.0f - push), 0.0f);
				other.Move(-intersectX * push, 0.0f);
			} else {
				Move(-intersectX * (1.0f - push), 0.0f);
				other.Move(intersectX * push, 0.0f);
			}
		} else {
			if (deltaY > 0.0f) {
				Move(0.0f, intersectY * (1.0f - push));
				other.Move(0.0f, -intersectY * push);
			} else {
				Move(0.0f, -intersectY * (1.0f - push));
				other.Move(0.0f, intersectY * push);
			}
		}

		return true;
	}

	return false;
}

void Collider::DispatchCollisionEnterEvent(Collider& collider, Vector2f push) {
	for (size_t i = 0; i < CollisionEnterEvent.size(); i++) {
		CollisionEnterEvent[i](collider, push);
	}
}

void Collider::DispatchCollisionEvent(Collider& collider, Vector2f push) {
	for (size_t i = 0; i < CollisionEvent.size(); i++) {
		CollisionEvent[i](collider, push);
	}
}

void Collider::DispatchCollisionExitEvent(Collider& collider) {
	for (size_t i = 0; i < CollisionExitEvent.size(); i++) {
		CollisionExitEvent[i](collider);
	}
}