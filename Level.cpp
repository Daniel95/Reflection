#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Level.h"
#include "LevelObject.h"
#include "TimeHelper.h"
#include "Window.h"
#include "Player.h"
#include "Box.h"

using namespace sf;
using namespace std;

const float boxSpawnInterval = 0.1f;
const float spawnScreenOffset = 200;
const int maxBoxSpawnAmount = 3;
const int minBoxSpawnAmount = 0;

vector<LevelObject*> levelObjects;
float scrollSpeed = -0.1f;
float blockSpawnTimer = 0;
float maxCombinedBoxHeightToSpawn;

void SpawnBoxes();

void InstantiateLevel() {
	Vector2f windowCenter = Vector2f((float)GameWindowSize.x / 2, (float)GameWindowSize.y / 2);
	float quarterWindowHeight = (float)GameWindowSize.y / 4;
	Vector2f player1Pos = Vector2f(windowCenter.x, windowCenter.y + quarterWindowHeight);
	Vector2f player2Pos = Vector2f(windowCenter.x, windowCenter.y - quarterWindowHeight);

	Player *player1 = new Player(Vector2f(player1Pos.x, player1Pos.y));
	Player *player2 = new Player(Vector2f(player2Pos.x, player2Pos.y));

	float playersCombinedHeight = player1->Body.getSize().y + player2->Body.getSize().y;
	maxCombinedBoxHeightToSpawn = GameWindowSize.y - playersCombinedHeight - 10;

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
	for (size_t i = 0; i < boxSpawnAmount; i++) {
		maxRandomHeight = (remainingHeight / remainingBoxes) * 2;

		cout << "remainingBoxes:" << endl;
		cout << remainingBoxes << endl;

		cout << "maxRandomHeight:" << endl;
		cout << maxRandomHeight << endl;

		boxHeight = rand() % (maxRandomHeight + 1);

		cout << "boxHeight:" << endl;
		cout << boxHeight << endl;
		int remainingHeight = maxCombinedBoxHeightToSpawn;

		cout << "remainingHeight:" << endl;
		cout << remainingHeight << endl;
		new Box(Vector2f(GameWindowSize.x, remainingHeight), Vector2f(50, boxHeight), 0.5f);

		remainingHeight - boxHeight;
		remainingBoxes--;
	}

	//windowSize.y
}
