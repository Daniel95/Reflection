#include "stdafx.h"
#include "LevelObject.h"
#include "Level.h"
#include "Window.h"
#include <iostream>

LevelObject::LevelObject() {
	AddLevelObject(*this);
}

LevelObject::~LevelObject() {
	cout << "LevelObject removed" << endl;

	RemoveLevelObject(*this);
}
