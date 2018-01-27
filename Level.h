#pragma once
#include "GameObject.h"
#include <functional>

using namespace std;
using namespace sf;

extern vector<function<void()>> OnGameOverEvent;

void StartLevel();
void StopLevel();
void UpdateLevel();
void AddSideScrollingGameObject(GameObject &gameObject);
void RemoveSideScrollingGameObject(GameObject &gameObject);