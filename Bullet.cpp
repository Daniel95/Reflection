#include "stdafx.h"
#include "Bullet.h"
#include "Window.h"
#include "Collisions.h"
#include "GameEvents.h"
#include "MathHelper.h"
#include "TimeHelper.h"
#include <iostream>

Bullet::Bullet(Vector2f position, Vector2f _direction, float _speed, Tags::Tag shooterTag) {
	GetBody().setSize(bulletSize);
	GetBody().setOrigin(GetBody().getSize() / 2.0f);
	GetBody().setPosition(position);
	GetBody().setFillColor(bulletColor);

	Tag = Tags::Tag::Bullet;
	ShooterTag = shooterTag;

	direction = _direction;
	speed = _speed;

	UpdateEvent[Id] = [this]() { OnUpdate(); };

	AddDrawable(GetBody(), bulletDrawLayer);
	AddCollider(collider, 0);

	collider.CollisionEnterEvent.push_back([this](auto collider, auto push) { OnCollisionEnterEvent(collider, push); });
	//collider.CollisionEvent.push_back([this](auto collider, auto push) { OnCollisionEvent(collider, push); });
}

Bullet::~Bullet() {
	RemoveCollider(collider, 0);
	RemoveDrawable(GetBody(), bulletDrawLayer);
	UpdateEvent.erase(Id);
}

void Bullet::OnUpdate() {
	GetBody().move(direction * speed * TimeHelper::DeltaTime);

	lifeTime += TimeHelper::DeltaTime;
	if (lifeTime > maxLifeTime) {
		Destroy();
	}
}

void Bullet::OnCollisionEnterEvent(Collider& collider, Vector2f push) {
	Destroy();
}

/*
void Bullet::OnCollisionEvent(Collider& collider, Vector2f push) {
	lifeTime += maxLifeTime / 60;
}
*/