#pragma once
#include <SFML\Graphics.hpp>
#include "Collider.h"
#include "LevelObject.h"

using namespace sf;

const float bulletSpeed = 800.0f;
const Vector2f bulletSize = Vector2f(10.0f, 10.0f);
const float bulletMass = 0.0f;
const Color bulletColor = Color::Red;

class Bullet : LevelObject {
	Vector2f direction;

	Collider collider = Collider(Body, bulletMass);

	void OnUpdate();
	void OnCollisionEnterEvent(Collider&, Vector2f);
public:
	Bullet(Vector2f position, Vector2f direction);
	~Bullet();
};

