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
	GetBody().setSize(enemySize);
	GetBody().setOrigin(GetBody().getSize() / 2.0f);
	GetBody().setPosition(position);
	GetBody().setFillColor(enemyColor);

	Tag = Tags::Tag::Enemy;

	collider.CollisionEnterEvent.push_back([this](auto collider, auto push) { OnCollisionEnter(collider, push); });

	UpdateEvent[Id] = [this]() { OnUpdate(); };

	AddDrawable(GetBody(), enemyDrawLayer);
	AddCollider(collider, 0);
}

Enemy::~Enemy() {
	RemoveDrawable(GetBody(), enemyDrawLayer);
	RemoveCollider(collider, 0);
	UpdateEvent.erase(Id);
}

void Enemy::OnUpdate() {
	//Only shoot at the player when there is one, and when i am completely inside the screen
	if (Players.size() == 0) { return; }
	if (GetBody().getPosition().x > GameWindow.getSize().x - GetBody().getSize().x) { return; }

	enemyShootTimer += TimeHelper::DeltaTime;
	if (enemyShootTimer >= enemyShootCD) {
		float smallestDistanceToPlayer = FLT_MAX;
		Vector2f offsetToClosestPlayer;
		float distance;
		Vector2f offset;

		//Find the closest player
		for (size_t i = 0; i < Players.size(); i++) {
			offset = Players[i]->GetBody().getPosition() - GetBody().getPosition();
			distance = MathHelper::Length(offset);
			if (distance < smallestDistanceToPlayer) {
				smallestDistanceToPlayer = distance;
				offsetToClosestPlayer = offset;
			}
		}

		Vector2f direction = MathHelper::Normalize(offsetToClosestPlayer);
		Vector2f spawnPosition = GetBody().getPosition() + (direction * 100.0f);

		new Bullet(spawnPosition, direction, enemyBulletSpeed, Tag);

		enemyShootTimer = 0;
	}
}

void Enemy::OnCollisionEnter(Collider& collider, Vector2f push) {
	GameObject* colliderGameObject = &collider.GetGameObject();

	if (colliderGameObject->Tag == Tags::Tag::Bullet) {
		//Only get killed by a bullet if it wasn't shot by another enemy
		if (Bullet* c = dynamic_cast<Bullet*>(colliderGameObject)) {
			if (c->ShooterTag != Tags::Tag::Enemy) {
				Destroy();
			}
		}
	}
}