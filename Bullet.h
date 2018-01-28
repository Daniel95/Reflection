#pragma once
#include <SFML\Graphics.hpp>
#include "Collider.h"
#include "GameObject.h"
#include "Tags.h"

using namespace sf;

const Vector2f bulletSize = Vector2f(10.0f, 10.0f);
const float bulletMass = 0.0f;
const Color bulletColor = Color::Red;
const float maxLifeTime = 30;
const int bulletDrawLayer = 5;

//A bullet moves toward a direction and gets automaticly destroyed when hitting an collider
class Bullet : public GameObject {
	Vector2f direction;
	float speed;
	float lifeTime;

	Collider collider = Collider(*this, bulletMass);

	void OnUpdate();
	void OnCollisionEnterEvent(Collider&, Vector2f);
public:
	Tags::Tag ShooterTag;

	Bullet(Vector2f position, Vector2f direction, float speed, Tags::Tag shooterTag);
	~Bullet();
};

