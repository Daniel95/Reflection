#include "stdafx.h"
#include "Box.h"
#include "Window.h"
#include "Collisions.h"
#include <iostream>

Box::Box(Vector2f position, Vector2f size, float mass) {
	body.setSize(size);
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(position);

	collider.Mass = mass;

	AddDrawable(body, 1);
	AddCollider(collider, 0);
}


Box::~Box() {
	RemoveDrawable(body, 1);
	RemoveCollider(collider, 0);
	//clear up box.
}