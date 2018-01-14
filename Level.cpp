#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Level.h"
#include "LevelObject.h"
#include "TimeHelper.h"
#include "Window.h"
#include "Player.h"
#include "Box.h"
#include "Range.h"

using namespace sf;
using namespace std;

vector<LevelObject*> LevelObjectsToDestroy;

const float boxSpawnInterval = 350.0f;
const float spawnScreenOffset = 200.0f;
const int maxBoxSpawnAmount = 3;
const int minBoxSpawnAmount = 0;
const Vector2i minBoxSize = Vector2i(50, 50);
const Vector2i maxBoxSize = Vector2i(150, 200);
const int minBoxMass = 1;
const int maxBoxMass = 5;

vector<LevelObject*> levelObjects;
float scrollSpeed = -130.0f;
float blockSpawnTimer = 0;
float minScreenHalfSpace = 0;

void SpawnBoxes();

void InstantiateLevel() {
	srand(time(NULL));

	Vector2f windowCenter = Vector2f((float)GameWindowSize.x / 2, (float)GameWindowSize.y / 2);
	float quarterWindowHeight = (float)GameWindowSize.y / 4;
	Vector2f player1Pos = Vector2f(windowCenter.x, windowCenter.y + quarterWindowHeight);
	Vector2f player2Pos = Vector2f(windowCenter.x, windowCenter.y - quarterWindowHeight);

	Player *player1 = new Player(Vector2f(player1Pos.x, player1Pos.y));
	Player *player2 = new Player(Vector2f(player2Pos.x, player2Pos.y));

	minScreenHalfSpace = player2->Body.getSize().y + 10;

	Box *topBoundary = new Box(Vector2f(windowCenter.x, 0), Vector2f((float)GameWindowSize.x, 50), 9999);
	levelObjects.erase(remove(levelObjects.begin(), levelObjects.end(), topBoundary), levelObjects.end());

	Box *bottomBoundary = new Box(Vector2f(windowCenter.x, (float)GameWindowSize.y), Vector2f((float)GameWindowSize.x, 50), 9999);
	levelObjects.erase(remove(levelObjects.begin(), levelObjects.end(), bottomBoundary), levelObjects.end());

	SpawnBoxes();
}

void UpdateLevel() {
	for (size_t i = 0; i < LevelObjectsToDestroy.size(); i++) {
		DestroyLevelObject(*LevelObjectsToDestroy[i]);
	}
	LevelObjectsToDestroy.clear();

	float fixedScollSpeed = scrollSpeed * TimeHelper::DeltaTime;

	blockSpawnTimer += abs(fixedScollSpeed);
	if(blockSpawnTimer >= boxSpawnInterval) {
		blockSpawnTimer = 0;
		SpawnBoxes();
	}

	float levelObjectLeftSideX = 0;
	LevelObject* levelObject;
	for (size_t i = 0; i < levelObjects.size(); i++) {
		levelObject = levelObjects[i];
		levelObject->Body.move(fixedScollSpeed, 0);
		levelObjectLeftSideX = levelObject->Body.getPosition().x + levelObject->Body.getSize().x / 2;
		if (levelObjectLeftSideX < 0) {
			DestroyLevelObject(*levelObject);
		}
	}
}

void AddLevelObject(LevelObject &levelObject) {
	levelObjects.push_back(&levelObject);
}

void DestroyLevelObject(LevelObject &levelObject) {
	levelObjects.erase(remove(levelObjects.begin(), levelObjects.end(), &levelObject), levelObjects.end());
	delete &levelObject;
}

void RemoveLevelObject(LevelObject &levelObject) {
	levelObjects.erase(remove(levelObjects.begin(), levelObjects.end(), &levelObject), levelObjects.end());
}

bool RangeCompare(Range *range1, Range *range2) {
	return range1->GetMin() < range2->GetMin();
}

void SpawnBoxes() {
	vector<Range*> occupiedYSpaces;

	while (true) {
		int randomBoxHeight = rand() % (maxBoxSize.y - minBoxSize.y + 1) + minBoxSize.y;
		int halfBoxHeight = randomBoxHeight / 2;

		int minYPos = halfBoxHeight;
		int maxYPos = GameWindowSize.y - halfBoxHeight;

		int randomBoxYPos = rand() % (maxYPos - minYPos + 1) + minYPos;

		Range *occupiedYSpace = new Range(randomBoxYPos - halfBoxHeight, randomBoxYPos + halfBoxHeight);
		occupiedYSpaces.push_back(occupiedYSpace);

		sort(occupiedYSpaces.begin(), occupiedYSpaces.end(), RangeCompare);

		int biggestTopHalfScreenSpace = 0;
		int biggestBottomHalfScreenSpace = 0;
		int halfWindowHeight = GameWindowSize.y / 2;
		Range space(0, 0);

		for (size_t i = 0; i <= occupiedYSpaces.size(); i++) {
			space.SetMin(0);
			space.SetMax(0);

			//break whole spawning loop when the new boxs is going to spawn in a existings box
			if (i + 1 < occupiedYSpaces.size() && occupiedYSpaces[i]->GetMax() > occupiedYSpaces[i + 1]->GetMin()) {
				break;
			}

			if (i == 0) {
				space.SetMax(occupiedYSpaces[i]->GetMin());
			}
			if (i == occupiedYSpaces.size()) {
				space.SetMin(occupiedYSpaces[i - 1]->GetMax());
				space.SetMax(GameWindowSize.y);
			} 
			if(i != 0 && i != occupiedYSpaces.size()) {
				space.SetMin(occupiedYSpaces[i - 1]->GetMax());
				space.SetMax(occupiedYSpaces[i]->GetMin());
			}

			if (space.GetMin() < halfWindowHeight) {
				if (space.GetMax() > halfWindowHeight) {
					int sizeInTopHalfScreen = halfWindowHeight - space.GetMin();
					if (sizeInTopHalfScreen > biggestTopHalfScreenSpace) {
						biggestTopHalfScreenSpace = sizeInTopHalfScreen;
					}
				} else if(space.GetSize() > biggestTopHalfScreenSpace) {
					biggestTopHalfScreenSpace = space.GetSize();
				}
			}
			if (space.GetMax() > halfWindowHeight) {
				if (space.GetMin() < halfWindowHeight) {
					int sizeInBottomHalfScreen = space.GetMax() - halfWindowHeight;
					if (sizeInBottomHalfScreen > biggestBottomHalfScreenSpace) {
						biggestBottomHalfScreenSpace = sizeInBottomHalfScreen;
					}
				} else if (space.GetSize() > biggestBottomHalfScreenSpace) {
					biggestBottomHalfScreenSpace = space.GetSize();
				}
			}
		}

		if (biggestBottomHalfScreenSpace < minScreenHalfSpace || biggestTopHalfScreenSpace < minScreenHalfSpace) {
			break;
		}

		int randomBoxMass = rand() % (maxBoxMass - minBoxMass + 1) + minBoxMass;
		int randomBoxWidth = rand() % (maxBoxSize.x - minBoxSize.x + 1) + minBoxSize.x;

		new Box(Vector2f(GameWindowSize.x + (float)randomBoxWidth, (float)randomBoxYPos), Vector2f((float)randomBoxWidth, (float)randomBoxHeight), (float)randomBoxMass);
	}

	for (size_t i = 0; i < occupiedYSpaces.size(); i++) {
		delete occupiedYSpaces[i];
	}
	occupiedYSpaces.clear();
}