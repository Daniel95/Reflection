#include "stdafx.h"
#include "Box.h"
#include "Window.h"
#include "Collisions.h"
#include <iostream>

Box::Box(Vector2f position, Vector2f size) {
	body.setSize(size);
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(position);

	cout << "spawn box" << endl;
	add_drawable(body, 1);
	AddColliderBody(body, 0);
}


Box::~Box() {}
