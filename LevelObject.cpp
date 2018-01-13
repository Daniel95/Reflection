#include "stdafx.h"
#include "LevelObject.h"
#include "Level.h"
#include "Window.h"
#include <iostream>
#include <sstream>
#include <string> 

LevelObject::LevelObject() {
	AddLevelObject(*this);

	stringstream ss;
	ss << this;
	Id = ss.str();
}

LevelObject::~LevelObject() {
	RemoveLevelObject(*this);
}

void LevelObject::Destroy() {
	LevelObjectsToDestroy.push_back(this);
}
