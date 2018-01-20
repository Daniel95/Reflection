#include "stdafx.h"
#include "GameObject.h"
#include "Level.h"
#include "Window.h"
#include <iostream>
#include <sstream>
#include <string> 

GameObject::GameObject() {
	AddSideScrollingGameObject(*this);

	stringstream ss;
	ss << this;
	Id = ss.str();
}

GameObject::~GameObject() {
	RemoveSideScrollingGameObject(*this);
}

void GameObject::Destroy() {
	if (destroying) { return; }
	destroying = true;
	GameObjectsToDestroy.push_back(this);
}
