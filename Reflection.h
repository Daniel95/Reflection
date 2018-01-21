#pragma once
#include <functional> 
#include "GameObject.h"

using namespace std;

extern map<string, function<void()>> DestroyAllGameObjectsEvent;
extern vector<GameObject*> GameObjectsToDestroy;