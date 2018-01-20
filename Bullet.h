#pragma once
#include <SFML\Graphics.hpp>
#include "Collider.h"
#include "GameObject.h"

using namespace sf;

const Vector2f bulletSize = Vector2f(10.0f, 10.0f);
const float bulletMass = 0.0f;
const Color bulletColor = Color::Red;
const float maxLifeTime = 30;

class Bullet : GameObject {
	Vector2f direction;
	float speed;
	float lifeTime;

	Collider collider = Collider(*this, bulletMass);

	void OnUpdate();
	void OnCollisionEnterEvent(Collider&, Vector2f);
public:
	Bullet(Vector2f position, Vector2f direction, float speed);
	~Bullet();
};

