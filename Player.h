#pragma once

#include <SFML/Graphics.hpp>
#include "Collider.h"

using namespace sf;

class Player {
private:
	const float PLAYER_SPEED = 800.0f;
	RectangleShape body;
	Collider collider = Collider(body, 0.5f);
public:
	Player(Vector2f position);
	~Player();
	void OnUpdate();
	void OnCollisionEnter(Collider& collider, Vector2f push);
	void OnCollision(Collider& collider, Vector2f push);
	void OnCollisionExit(Collider& collider);
	void OnMouse(Mouse::Button mouseButton, Vector2i mousePosition, Vector2i mouseDelta);

	float Mass;
	vector<function<void(Collider&, Vector2f)>> CollisionEnterEvent;
	vector<function<void(Collider&, Vector2f)>> CollisionEvent;
	vector<function<void(Collider&)>> CollisionExitEvent;

	Vector2f GetPosition() { return body.getPosition(); }
	Collider* GetCollider() { return &collider; }
};

