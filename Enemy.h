#pragma once
#include <SFML\Graphics.hpp>
#include "Collider.h"
#include "LevelObject.h"

using namespace sf;

const Vector2f enemySize = Vector2f(60.0f, 100.0f);
const float enemyMass = 0.5f;
const Color enemyColor = Color::Red;

class Enemy : public LevelObject {
	Collider collider = Collider(Body, enemyMass);

	void OnUpdate();
public:
	Enemy(Vector2f position);
	~Enemy();
};
