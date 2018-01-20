#include "stdafx.h"
#include "Enemy.h"
#include "Window.h"
#include "Collisions.h"
#include "GameEvents.h"
#include "MathHelper.h"
#include "GameObject.h"
#include "TimeHelper.h"
#include "Bullet.h"
#include "Player.h"

#include <iostream>

using namespace std;
using namespace sf;

Enemy::Enemy(Vector2f position) {
	Body.setSize(enemySize);
	Body.setOrigin(Body.getSize() / 2.0f);
	Body.setPosition(position);
	Body.setFillColor(enemyColor);

	Tag = Tags::Tag::Enemy;

	collider.CollisionEnterEvent.push_back([this](auto collider, auto push) { OnCollisionEnter(collider, push); });

	UpdateEvent[Id] = [this]() { OnUpdate(); };

	AddDrawable(Body, 1);
	AddCollider(collider, 0);
}

Enemy::~Enemy() {
	RemoveDrawable(Body, 1);
	RemoveCollider(collider, 0);
	UpdateEvent.erase(Id);
}

void Enemy::OnUpdate() {
	if (Players.size() == 0) { return; }

	enemyShootTimer += TimeHelper::DeltaTime;
	if (enemyShootTimer >= enemyShootCD) {
		float smallestDistanceToPlayer = FLT_MAX;
		Vector2f offsetToClosestPlayer;
		float distance;
		Vector2f offset;

		for (size_t i = 0; i < Players.size(); i++) {
			offset = Players[i]->Body.getPosition() - Body.getPosition();
			distance = MathHelper::Length(offset);
			if (distance < smallestDistanceToPlayer) {
				smallestDistanceToPlayer = distance;
				offsetToClosestPlayer = offset;
			}
		}

		if (smallestDistanceToPlayer > maxShootDistance) { return; }

		Vector2f direction = MathHelper::Normalize(offsetToClosestPlayer);
		Vector2f spawnPosition = Body.getPosition() + (direction * 100.0f);

		new Bullet(spawnPosition, direction, enemyBulletSpeed);

		enemyShootTimer = 0;
	}
}

void Enemy::OnCollisionEnter(Collider& collider, Vector2f push) {
	if (collider.GetGameObject().Tag == Tags::Tag::Bullet) {
		Destroy();
	}
}