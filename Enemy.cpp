#include "stdafx.h"
#include "Enemy.h"
#include "Window.h"
#include "Collisions.h"
#include "GameEvents.h"
#include "MathHelper.h"
#include <iostream>
#include <sstream>
#include <string> 

using namespace std;
using namespace sf;

Enemy::Enemy(Vector2f position) {
	Body.setSize(enemySize);
	Body.setOrigin(Body.getSize() / 2.0f);
	Body.setPosition(position);

	stringstream ss;
	ss << this;
	string addressName = ss.str();

	cout << addressName << endl;

	UpdateEvent[addressName] = [this]() { OnUpdate(); };

	AddDrawable(Body, 1);
	AddCollider(collider, 0);
}


Enemy::~Enemy() {
	RemoveDrawable(Body, 1);
	RemoveCollider(collider, 0);
}

void Enemy::OnUpdate() {

}
