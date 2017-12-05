#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class Player {
private:
	const float PLAYER_SPEED = 0.4f;
	CircleShape playerShape;
public:
	Player();
	~Player();
	void OnKey(Keyboard::Key key);
	void OnMouse(Mouse::Button mouseButton, Vector2i mousePosition, Vector2i mouseDelta);
};

