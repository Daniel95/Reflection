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

	//Subscribe to the CollisionEnterEvent
	collider.CollisionEnterEvent.push_back([this](auto collider, auto push) { OnCollisionEnterEvent(collider, push); });
}

Bullet::~Bullet() {
	RemoveCollider(collider, 0);
	RemoveDrawable(GetBody(), bulletDrawLayer);
	UpdateEvent.erase(Id);
}

//Move the bullet, and when it's lifetime is over, destroy it
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