#include "stdafx.h"
#include "Bullet.h"
#include "Window.h"
#include "Collisions.h"
#include "GameEvents.h"
#include "MathHelper.h"
#include "TimeHelper.h"
#include <iostream>

Bullet::Bullet(Vector2f position, Vector2f _direction, float _speed) {
	Body.setSize(bulletSize);
	Body.setOrigin(Body.getSize() / 2.0f);
	Body.setPosition(position);
	Body.setFillColor(bulletColor);

	Tag = Tags::Tag::Bullet;
	
	direction = _direction;
	speed = _speed;

	UpdateEvent[Id] = [this]() { OnUpdate(); };

	AddDrawable(Body, 1);
	AddCollider(collider, 0);

	collider.CollisionEnterEvent.push_back([this](auto collider, auto push) { OnCollisionEnterEvent(collider, push); });
}

Bullet::~Bullet() {
	RemoveCollider(collider, 0);
	RemoveDrawable(Body, 1);
	UpdateEvent.erase(Id);
}

void Bullet::OnUpdate() {
	Body.move(direction * speed * TimeHelper::DeltaTime);
}

void Bullet::OnCollisionEnterEvent(Collider& collider, Vector2f push) {
	Destroy();
}
