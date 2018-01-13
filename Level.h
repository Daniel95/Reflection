#pragma once
#include "LevelObject.h"

extern std::vector<LevelObject*> LevelObjectsToDestroy;

void InstantiateLevel();
void UpdateLevel();
void AddLevelObject(LevelObject &levelObject);
void DestroyLevelObject(LevelObject &levelObject);
void RemoveLevelObject(LevelObject &levelObject);