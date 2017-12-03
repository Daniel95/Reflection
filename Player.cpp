#include "stdafx.h"
#include "Player.h"
#include "KeyEvents.h"
#include "Window.h"

CircleShape player(100.f);
const float PLAYER_SPEED = 0.4f;

void OnKey(Keyboard::Key key);

Player::Player() {
	player.setFillColor(Color::Green);
	KeyEvent.push_back(OnKey);
	//add_drawable(player, 0);
}

Player::~Player() {
	//clear up player.
}

void OnKey(Keyboard::Key key) {
	if (key == Keyboard::Key::A) {
		player.move(-PLAYER_SPEED, 0);
	} else if (key == Keyboard::Key::D) {
		player.move(PLAYER_SPEED, 0);
	}

	if (key == Keyboard::Key::W) {
		player.move(0, -PLAYER_SPEED);
	} else if (key == Keyboard::Key::S) {
		player.move(0, PLAYER_SPEED);
	}
}