#pragma once
#include <SFML\Graphics.hpp>
#include "Collider.h"
#include "GameObject.h"

using namespace sf;

const Vector2f enemySize = Vector2f(60.0f, 100.0f);
const float enemyBulletSpeed = 550.0f;
const float enemyMass = 0.5f;
const Color enemyColor = Color::Red;
const float enemyShootCD = 0.9f;
const int enemyDrawLayer = 5;

//The enemy is able to shoot at the closests player
class Enemy : public GameObject {
	Collider collider = Collider(*this, enemyMass);
	float enemyShootTimer;

	void OnCollisionEnter(Collider& collider, Vector2f push);
	void OnUpdate();
public:
	Enemy(Vector2f position);
	~Enemy();
};
