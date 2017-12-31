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

const float boxSpawnInterval = 0.1f;
const float spawnScreenOffset = 200;
const int maxBoxSpawnAmount = 3;
const int minBoxSpawnAmount = 0;
const Vector2i minBoxSize = Vector2i(50, 50);
const Vector2i maxBoxSize = Vector2i(200, 250);

vector<LevelObject*> levelObjects;
float scrollSpeed = -0.1f;
float blockSpawnTimer = 0;
float minScreenHalfSpace = 0;

void SpawnBoxes();

void InstantiateLevel() {
	Vector2f windowCenter = Vector2f((float)GameWindowSize.x / 2, (float)GameWindowSize.y / 2);
	float quarterWindowHeight = (float)GameWindowSize.y / 4;
	Vector2f player1Pos = Vector2f(windowCenter.x, windowCenter.y + quarterWindowHeight);
	Vector2f player2Pos = Vector2f(windowCenter.x, windowCenter.y - quarterWindowHeight);

	Player *player1 = new Player(Vector2f(player1Pos.x, player1Pos.y));
	Player *player2 = new Player(Vector2f(player2Pos.x, player2Pos.y));

	minScreenHalfSpace = player2->Body.getSize().y + 10;

	//Box *box1 = new Box(Vector2f(player1Pos.x + 200, player1Pos.y), Vector2f(57, 204), 100.0f);
	//Box *box2 = new Box(Vector2f(player1Pos.x + 280, player1Pos.y + 150), Vector2f(50, 100), 0.5f);
	//Box *box3 = new Box(Vector2f(player2Pos.x - 355, player2Pos.y), Vector2f(100, 162), 10.0f);
	//Box *box4 = new Box(Vector2f(player2Pos.x - 133, player2Pos.y + 200), Vector2f(79, 135), 1.5f);
	//Box *box5 = new Box(Vector2f(player2Pos.x - 320, player2Pos.y - 100), Vector2f(60, 112), 100.0f);
	//Box *box6 = new Box(Vector2f(player2Pos.x + 450, player2Pos.y + 300), Vector2f(37, 190), 0.1f);

	Box *topBoundary = new Box(Vector2f(windowCenter.x, 0), Vector2f((float)GameWindowSize.x, 50), 9999);
	levelObjects.erase(remove(levelObjects.begin(), levelObjects.end(), topBoundary), levelObjects.end());

	Box *bottomBoundary = new Box(Vector2f(windowCenter.x, (float)GameWindowSize.y), Vector2f((float)GameWindowSize.x, 50), 9999);
	levelObjects.erase(remove(levelObjects.begin(), levelObjects.end(), bottomBoundary), levelObjects.end());

	SpawnBoxes();

	//Box *rightBoundary = new Box(Vector2f(0, windowCenter.y), Vector2f(0, (float)windowSize.y), 9999);
	//Box *leftBoundary = new Box(Vector2f((float)windowSize.x, windowCenter.y), Vector2f(0, (float)windowSize.y), 9999);
}

void UpdateLevel() {
	blockSpawnTimer += TimeHelper::DeltaTime * abs(scrollSpeed);
	if(blockSpawnTimer >= boxSpawnInterval) {
		blockSpawnTimer = 0;
		//SpawnBoxes();
	}

	float levelObjectLeftSideX = 0;
	LevelObject* levelObject;
	for (size_t i = 0; i < levelObjects.size(); i++) {
		levelObject = levelObjects[i];
		levelObject->Body.move(scrollSpeed, 0);
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

bool RangeCompare(Range range1, Range range2) {
	return range1.GetMin() < range2.GetMax();
}

void SpawnBoxes() {
	vector<Range*> occupiedYSpaces;

	while (true) {
		int randomBoxHeight = rand() % (maxBoxSize.y - minBoxSize.y + 1) + minBoxSize.y;
		int halfBoxHeight = randomBoxHeight / 2;

		int minY = halfBoxHeight;
		int maxY = GameWindowSize.y - halfBoxHeight;

		int randomBoxY = rand() % (maxY - minY + 1) + minY;

		Range occupiedYSpace = Range(minY, maxY);
		occupiedYSpaces.push_back(&occupiedYSpace);

		//break whole spawning loop when the new boxs is going to spawn in a existing box
		for (size_t i = 0; i < occupiedYSpaces.size(); i++) {
			if (minY > occupiedYSpaces[i]->GetMin() || maxY < occupiedYSpaces[i]->GetMax()) {
				break;
			}
		}

		sort(occupiedYSpaces.begin(), occupiedYSpaces.end(), RangeCompare);

		int biggestTopHalfScreenSpace = 0;
		int biggestBottomHalfScreenSpace = 0;
		int halfWindowHeight = GameWindowSize.y / 2;
		Range space(0, 0);
		for (size_t i = 0; i <= occupiedYSpaces.size(); i++) {
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

			if (space.GetMax() < halfWindowHeight && space.GetSize() > biggestTopHalfScreenSpace) {
				biggestTopHalfScreenSpace = space.GetSize();
			} else if(space.GetMin() > halfWindowHeight && space.GetSize() > biggestBottomHalfScreenSpace) {
				biggestBottomHalfScreenSpace = space.GetSize();
			}
		}

		if (biggestBottomHalfScreenSpace < minScreenHalfSpace || biggestTopHalfScreenSpace < minScreenHalfSpace) {
			break;
		}

		new Box(Vector2f(GameWindowSize.x - 160, randomBoxY), Vector2f(50, randomBoxHeight), 0.5f);
	}
}


/*
void SpawnBoxes() {
	int boxSpawnAmount = rand() % (maxBoxSpawnAmount - minBoxSpawnAmount + 1) + minBoxSpawnAmount;

	cout << "WindowHeight:" << endl;
	cout << GameWindowSize.y << endl;

	cout << "maxCombinedBoxHeightToSpawn:" << endl;
	cout << maxCombinedBoxHeightToSpawn << endl;

	int remainingHeight = maxCombinedBoxHeightToSpawn;
	int remainingBoxes = boxSpawnAmount;
	int boxHeight;
	int maxRandomHeight;
	int minRandomHeight;
	for (size_t i = 0; i < boxSpawnAmount; i++) {
		int defaultBoxHeight = (remainingHeight / remainingBoxes);
		maxRandomHeight = defaultBoxHeight * 1.5f;
		if (maxRandomHeight > remainingHeight) {
			maxRandomHeight = remainingHeight;
		}

		minRandomHeight = defaultBoxHeight * 0.75f;

		cout << "remainingBoxes:" << endl;
		cout << remainingBoxes << endl;

		cout << "maxRandomHeight:" << endl;
		cout << maxRandomHeight << endl;

		boxHeight = rand() % (maxRandomHeight - minRandomHeight + 1) + minRandomHeight;

		cout << "boxHeight:" << endl;
		cout << boxHeight << endl;
		int remainingHeight = maxCombinedBoxHeightToSpawn;

		cout << "remainingHeight:" << endl;
		cout << remainingHeight << endl;
		new Box(Vector2f(GameWindowSize.x - 160, remainingHeight), Vector2f(50, boxHeight), 0.5f);

		remainingHeight - boxHeight;
		remainingBoxes--;
	}

	//windowSize.y
}
*/
