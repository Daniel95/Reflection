#include "stdafx.h"
#include "Bullet.h"
#include "Window.h"
#include "Collisions.h"
#include "GameEvents.h"
#include "MathHelper.h"
#include "TimeHelper.h"
#include <iostream>

Bullet::Bullet(Vector2f position, Vector2f _direction) {
	//Vector2f direction = MathHelper::Normalize((float)direction.x, (float)direction.y);

	Body.setSize(bulletSize);
	Body.setOrigin(Body.getSize() / 2.0f);
	Body.setPosition(position);

	direction = _direction;

	UpdateEvent[Id] = [this]() { OnUpdate(); };

	AddDrawable(Body, 1);
	AddCollider(collider, 0);
}

Bullet::~Bullet() {
	//bullet not removed from update event
	//UpdateEvent[0].
	UpdateEvent.erase(Id);
}

void Bullet::OnUpdate() {
	Body.move(direction * bulletSpeed * TimeHelper::DeltaTime);
}
