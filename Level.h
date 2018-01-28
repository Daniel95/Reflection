#pragma once
#include "GameObject.h"
#include <functional>

using namespace std;
using namespace sf;

extern vector<function<void()>> OnGameOverEvent;

//The level is used to spawn GameObjects in order to create a level

void StartLevel();
void StopLevel();
void UpdateLevel();
void AddSideScrollingGameObject(GameObject &gameObject);
void RemoveSideScrollingGameObject(GameObject &gameObject);