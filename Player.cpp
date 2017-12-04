#include "stdafx.h"
#include "Player.h"
#include "KeyEvents.h"
#include "Window.h"
#include <iostream>

Player::Player() {
	playerShape = CircleShape(100.0f);
	cout << "player spawned" << endl;
	playerShape.setFillColor(Color::Green);
	KeyEvent.push_back([this](auto key) { OnKey(key); });
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