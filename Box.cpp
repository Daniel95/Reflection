#include "stdafx.h"
#include "Box.h"
#include "Window.h"
#include "Collisions.h"
#include "GameObject.h"
#include <iostream>

Color boxColor = Color::White;

Box::Box(Vector2f position, Vector2f size, float mass) {
	GetBody().setSize(size);
	GetBody().setOrigin(GetBody().getSize() / 2.0f);
	GetBody().setPosition(position);
	GetBody().setFillColor(boxColor);

	Tag = Tags::Tag::Box;

	collider.Mass = mass;

	AddDrawable(GetBody(), boxDrawLayer);
	AddCollider(collider, 0);
}

Box::~Box() {
	RemoveDrawable(GetBody(), boxDrawLayer);
	RemoveCollider(collider, 0);
}