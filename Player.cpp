#include "stdafx.h"
#include "Player.h"
#include "InputEvents.h"
#include "Window.h"
#include <iostream>

Player::Player() {
	body.setSize(Vector2f(100.0f, 150.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(Vector2f(206.0f, 206.0f));

	cout << "player spawned" << endl;
	body.setFillColor(Color::Green);
	KeyEvent.push_back([this](auto key) { OnKey(key); });
	MouseEvent.push_back([this](auto mouseButton, auto mousePosition, auto mouseDelta) { OnMouse(mouseButton, mousePosition, mouseDelta); });
	add_drawable(body, 0);
}

Player::~Player() {
	//clear up player.
}

void Player::OnKey(Keyboard::Key key) {
	if (key == Keyboard::Key::A) {
		body.move(-PLAYER_SPEED, 0);
	} else if (key == Keyboard::Key::D) {
		body.move(PLAYER_SPEED, 0);
	}

	if (key == Keyboard::Key::W) {
		body.move(0, -PLAYER_SPEED);
	} else if (key == Keyboard::Key::S) {
		body.move(0, PLAYER_SPEED);
	}
}

void Player::OnMouse(Mouse::Button mouseButton, Vector2i mousePosition, Vector2i mouseDelta) {
	cout << "mouse pos " << endl;
	cout << mousePosition.x << endl;
	cout << mousePosition.y << endl;
}