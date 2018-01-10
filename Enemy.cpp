#include "stdafx.h"
#include "Enemy.h"
#include "Window.h"
#include "Collisions.h"
#include "GameEvents.h"
#include "MathHelper.h"
#include <iostream>

Enemy::Enemy(Vector2f position) {
	Body.setSize(enemySize);
	Body.setOrigin(Body.getSize() / 2.0f);
	Body.setPosition(position);

	UpdateEvent.push_back([this]() { OnUpdate(); });

	AddDrawable(Body, 1);
	AddCollider(collider, 0);
}


Enemy::~Enemy() {
	RemoveDrawable(Body, 1);
	RemoveCollider(collider, 0);
}

void Enemy::OnUpdate() {

}
