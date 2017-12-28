#include "stdafx.h"
#include "Box.h"
#include "Window.h"
#include "Collisions.h"
#include "LevelObject.h"
#include <iostream>

Box::Box(Vector2f position, Vector2f size, float mass) {
	Body.setSize(size);
	Body.setOrigin(Body.getSize() / 2.0f);
	Body.setPosition(position);

	collider.Mass = mass;

	AddDrawable(Body, 1);
	AddCollider(collider, 0);
}


Box::~Box() {
	RemoveDrawable(Body, 1);
	RemoveCollider(collider, 0);
	//clear up box.
}