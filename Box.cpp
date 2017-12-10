#include "stdafx.h"
#include "Box.h"
#include "Window.h"

Box::Box(Vector2f position, Vector2f size) {
	body.setSize(size);
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(position);
	add_drawable(body, 1);
}


Box::~Box() {}
