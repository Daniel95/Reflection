#pragma once

#include <SFML/Graphics.hpp>
#include "Collider.h"

using namespace sf;

class Player {
private:
	const float PLAYER_SPEED = 800.0f;
	RectangleShape body;
public:
	Player(Vector2f position);
	~Player();
	void OnUpdate();
	void OnMouse(Mouse::Button mouseButton, Vector2i mousePosition, Vector2i mouseDelta);

	Vector2f GetPosition() { return body.getPosition(); }
};

