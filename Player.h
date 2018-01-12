#pragma once

#include <SFML/Graphics.hpp>
#include "Collider.h"
#include "LevelObject.h"

using namespace sf;

const float playerSpeed = 800.0f;
const Vector2f playerSize = Vector2f(60.0f, 100.0f);
const float playerMass = 0.5f;
const Color playerColor = Color::Green;

class Player : public LevelObject {
private:
	Collider collider = Collider(Body, playerMass);

	void OnUpdate();
	void OnCollisionEnter(Collider& collider, Vector2f push);
	void OnCollision(Collider& collider, Vector2f push);
	void OnCollisionExit(Collider& collider);
	void OnOtherPlayerCollision(Collider& collider, Vector2f push);
	void OnOtherPlayerSpawned(Player* otherPlayer);
	void OnMouseDown(Mouse::Button mouseButton, Vector2i mousePosition);
public:
	Player(Vector2f position);
	~Player();

	float Mass;

	Collider* GetCollider() { return &collider; }
};

extern vector<Player*> Players;
extern vector<function<void(Player*)>> PlayerSpawnedEvent;