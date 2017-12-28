#include "stdafx.h"
#include <iostream>
#include "Player.h"
#include <SFML/Graphics.hpp>
#include "InputEvents.h"
#include "Level.h"
#include "Window.h"
#include "Collisions.h"
#include "MathHelper.h"
#include "TimeHelper.h"
#include "GameEvents.h"

vector<Player*> Players;
vector<function<void(Player*)>> PlayerSpawnedEvent;

Player::Player(Vector2f position) {
	Body.setSize(Vector2f(60.0f, 100.0f));
	Body.setOrigin(Body.getSize() / 2.0f);
	Body.setPosition(position);
	Body.setFillColor(Color::Green);

	UpdateEvent.push_back([this]() { OnUpdate(); });
	MouseEvent.push_back([this](auto mouseButton, auto mousePosition, auto mouseDelta) { OnMouse(mouseButton, mousePosition, mouseDelta); });
	collider.CollisionEnterEvent.push_back([this](auto collider, auto push) { OnCollisionEnter(collider, push); });
	collider.CollisionEvent.push_back([this](auto collider, auto push) { OnCollision(collider, push); });
	collider.CollisionExitEvent.push_back([this](auto collider) { OnCollisionExit(collider); });

	//subscribe to previous existing players
	for (size_t p = 0; p < Players.size(); p++) {
		Player &otherPlayer = *Players[p];
		otherPlayer.collider.CollisionEnterEvent.push_back([this](auto collider, auto push) { OnOtherPlayerCollision(collider, push); });
		otherPlayer.collider.CollisionEvent.push_back([this](auto collider, auto push) { OnOtherPlayerCollision(collider, push); });
	}
	Players.push_back(this);

	//dispatch player spawned event so other players can subscribe to this player
	for (size_t e = 0; e < PlayerSpawnedEvent.size(); e++) {
		PlayerSpawnedEvent[e](this);
	}
	//add myself to Players list
	PlayerSpawnedEvent.push_back([this](auto player) { OnOtherPlayerSpawned(player); });

	AddDrawable(Body, 0);
	AddCollider(collider, 0);
}

Player::~Player() {
	RemoveDrawable(Body, 0);
	RemoveCollider(collider, 0);
	Players.erase(remove(Players.begin(), Players.end(), this), Players.end());

	//clear up player:
	//unsub from events.
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
	Body.move((direction * PLAYER_SPEED) * TimeHelper::DeltaTime);
}

void Player::OnCollisionEnter(Collider& collider, Vector2f push) { }

void Player::OnCollision(Collider& collider, Vector2f push) {  }

void Player::OnCollisionExit(Collider& collider) { }

void Player::OnOtherPlayerCollision(Collider& collider, Vector2f push) {
	Body.move(push);
}

void Player::OnOtherPlayerSpawned(Player* otherPlayer) {
	otherPlayer->collider.CollisionEnterEvent.push_back([this](auto collider, auto push) { OnOtherPlayerCollision(collider, push); });
	otherPlayer->collider.CollisionEvent.push_back([this](auto collider, auto push) { OnOtherPlayerCollision(collider, push); });
}

void Player::OnMouse(Mouse::Button mouseButton, Vector2i mousePosition, Vector2i mouseDelta) { }