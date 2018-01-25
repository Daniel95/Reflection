#include "stdafx.h"
#include "Box.h"
#include "Window.h"
#include "Collisions.h"
#include "GameObject.h"
#include <iostream>

Box::Box(Vector2f position, Vector2f size, float mass) {
	GetBody().setSize(size);
	GetBody().setOrigin(GetBody().getSize() / 2.0f);
	GetBody().setPosition(position);

	Tag = Tags::Tag::Box;

	collider.Mass = mass;

	AddDrawable(GetBody(), 1);
	AddCollider(collider, 0);
}


Box::~Box() {
	RemoveDrawable(GetBody(), 1);
	RemoveCollider(collider, 0);
}