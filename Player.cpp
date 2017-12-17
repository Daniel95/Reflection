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

vector<Player*> Players;
vector<function<void(Player&)>> PlayerSpawnEvent;

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

	//subscribe to previous existing players
	for (size_t p = 0; p < Players.size(); p++) {
		Player &otherPlayer = *Players[p];
		otherPlayer.CollisionEnterEvent.push_back([this](auto collider, auto push) { OnOtherPlayerCollision(collider, push); });
	}
	//dispatch player spawned event so other players in the Players can subscribe to this player
	for (size_t e = 0; e < PlayerSpawnEvent.size(); e++) {
		PlayerSpawnEvent[e](*this);
	}
	//add myself to Players list
	Players.push_back(this);

	add_drawable(body, 0);
	AddCollider(collider, 0);
}

Player::~Player() {
	//clear up player:
	//unsub from events.
	//remove from player list
	//disptach player removed event so other players can unsubscribe from this player
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

void Player::OnOtherPlayerCollision(Collider& collider, Vector2f push) {
	body.move(push);
}

void Player::OnMouse(Mouse::Button mouseButton, Vector2i mousePosition, Vector2i mouseDelta) { }