#pragma once
#include "GameObject.h"

extern std::vector<GameObject*> GameObjectsToDestroy;

void StartLevel();
void StopLevel();
void UpdateLevel();
void AddSideScrollingGameObject(GameObject &gameObject);
void RemoveSideScrollingGameObject(GameObject &gameObject);
void RemoveSideScrollingGameObject(GameObject &gameObject);