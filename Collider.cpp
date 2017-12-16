#include "stdafx.h"
#include <iostream>
#include "Collider.h"

using namespace std;

Collider::Collider(RectangleShape &body, float mass) : body(body) {
	Mass = mass;
}

Collider::Collider(RectangleShape &body) : body(body) { }

Collider::~Collider() { }

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
				other.Move(0.0f , -intersectY * push);
			} else {
				Move(0.0f, -intersectY * (1.0f - push));
				other.Move(0.0f, intersectY * push);
			}
		}

		return true;
	}

	return false;
}

