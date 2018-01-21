#include "stdafx.h"
#include "Reflection.h"
#include "GameObject.h"
#include "Level.h"
#include "Window.h"
#include <iostream>
#include <sstream>
#include <string> 

GameObject::GameObject() {
	stringstream ss;
	ss << this;
	Id = ss.str();

	AddSideScrollingGameObject(*this);
	DestroyAllGameObjectsEvent[Id] = [this]() { Destroy(); };
}

GameObject::~GameObject() {
	RemoveSideScrollingGameObject(*this);
	DestroyAllGameObjectsEvent.erase(Id);
}

void GameObject::Destroy() {
	if (destroying) { return; }
	destroying = true;
	GameObjectsToDestroy.push_back(this);
}
