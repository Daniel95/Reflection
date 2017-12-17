#include "stdafx.h"
#include <iostream>
#include "Player.h"
#include <SFML/Graphics.hpp>
#include "InputEvents.h"
#include "Window.h"
#include "Collisions.h"
#include "MathHelper.h"
#include "TimeHelper.h"
#include "GameEvents.h"

Player::Player(Vector2f position) {
	body.setSize(Vector2f(60.0f, 100.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(position);

	body.setFillColor(Color::Green);
	UpdateEvent.push_back([this]() { OnUpdate(); });
	MouseEvent.push_back([this](auto mouseButton, auto mousePosition, auto mouseDelta) { OnMouse(mouseButton, mousePosition, mouseDelta); });

	collider.CollisionEnterEvent.push_back([this](auto collider, auto push) { OnCollisionEnter(collider, push); });
	collider.CollisionEvent.push_back([this](auto collider, auto push) { OnCollision(collider, push); });
	collider.CollisionExitEvent.push_back([this](auto collider) { OnCollisionExit(collider); });

	add_drawable(body, 0);
	AddCollider(collider, 0);
}

Player::~Player() {
	//clear up player.
}

void Player::OnUpdate() {
	Vector2i input;

	if (Keyboard::isKeyPressed(Keyboard::Key::A)) {
		input.x = -1;
	} else if (Keyboard::isKeyPressed(Keyboard::Key::D)) {
		input.x = 1;
	}

	if (Keyboard::isKeyPressed(Keyboard::Key::W)) {
		input.y = -1;
	} else if (Keyboard::isKeyPressed(Keyboard::Key::S)) {
		input.y = 1;
	}

	Vector2f direction = MathHelper::Normalize((float)input.x, (float)input.y);
	body.move((direction * PLAYER_SPEED) * TimeHelper::deltaTime);
}

void Player::OnCollisionEnter(Collider& collider, Vector2f push) { }

void Player::OnCollision(Collider& collider, Vector2f push) { }

void Player::OnCollisionExit(Collider& collider) { }

void Player::OnMouse(Mouse::Button mouseButton, Vector2i mousePosition, Vector2i mouseDelta) { }