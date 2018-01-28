#pragma once

#include <SFML/Graphics.hpp>
#include "Collider.h"
#include "GameObject.h"

using namespace sf;

const float playerSpeed = 600.0f;
const float playerBulletSpeed = 800.0f;
const Vector2f playerSize = Vector2f(60.0f, 100.0f);
const float playerMass = 0.5f;
const Color playerColor = Color::Green;
const float playerShootCD = 0.3f;
const int playerDrawLayer = 1;
const int maxPlayers = 2;

//The player is able to move and shoot, players will also react to the collision of other players and will die when another player dies
//When all players are dead, it's game over
class Player : public GameObject {
private:
	Collider collider = Collider(*this, playerMass);
	float playerShootTimer = 0;

	void OnUpdate();
	void OnCollisionEnter(Collider& collider, Vector2f push);
	void OnCollision(Collider& collider, Vector2f push);
	void OnCollisionExit(Collider& collider);
	void OnOtherPlayerCollision(Collider& collider, Vector2f push);
	void OnOtherPlayerSpawned(Player* otherPlayer);
	void OnOtherPlayerKilled();
	void OnMouse(Mouse::Button mouseButton, Vector2i mousePosition, Vector2i mouseDelta);
public:
	Player(Vector2f position);
	~Player();

	float Mass;

	Collider* GetCollider() { return &collider; }
};

extern vector<Player*> Players;
extern map<string, function<void(Player*)>> PlayerSpawnedEvent;
extern map<string, function<void()>> PlayerKilledEvent;