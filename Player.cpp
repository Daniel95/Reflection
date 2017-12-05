#include "stdafx.h"
#include "Player.h"
#include "InputEvents.h"
#include "Window.h"
#include <iostream>

Player::Player() {
	playerShape = CircleShape(100.0f);
	cout << "player spawned" << endl;
	playerShape.setFillColor(Color::Green);
	KeyEvent.push_back([this](auto key) { OnKey(key); });
	MouseEvent.push_back([this](auto mouseButton, auto mousePosition, auto mouseDelta) { OnMouse(mouseButton, mousePosition, mouseDelta); });
	add_drawable(playerShape, 0);
}

Player::~Player() {
	//clear up player.
}

void Player::OnKey(Keyboard::Key key) {
	if (key == Keyboard::Key::A) {
		playerShape.move(-PLAYER_SPEED, 0);
	} else if (key == Keyboard::Key::D) {
		playerShape.move(PLAYER_SPEED, 0);
	}

	if (key == Keyboard::Key::W) {
		playerShape.move(0, -PLAYER_SPEED);
	} else if (key == Keyboard::Key::S) {
		playerShape.move(0, PLAYER_SPEED);
	}
}

void Player::OnMouse(Mouse::Button mouseButton, Vector2i mousePosition, Vector2i mouseDelta) {
	cout << "mouse pos " << endl;
	cout << mousePosition.x << endl;
	cout << mousePosition.y << endl;
}