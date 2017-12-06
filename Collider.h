#pragma once

#include <SFML\Graphics.hpp>

using namespace sf;

class Collider {
private:
	RectangleShape& body;

public:
	Collider(RectangleShape& body);
	~Collider();

	void Move(float dx, float dy) { body.move(dx, dy); }

	bool CheckCollision(Collider& other, float push);
	Vector2f GetPosition() { return body.getPosition(); }
	Vector2f GetHalfSize() { return body.getSize() / 2.0f; }

};

