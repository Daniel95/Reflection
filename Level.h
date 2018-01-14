#pragma once
#include "GameObject.h"

extern std::vector<GameObject*> GameObjectsToDestroy;

void InstantiateLevel();
void UpdateLevel();
void AddGameObject(GameObject &gameObject);
void DestroyGameObject(GameObject &gameObject);
void RemoveGameObject(GameObject &gameObject);