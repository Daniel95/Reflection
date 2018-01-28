#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Level.h"
#include "GameObject.h"
#include "Reflection.h"
#include "GameEvents.h"
#include "TimeHelper.h"
#include "DelayMethods.h"
#include "Window.h"
#include "Score.h"
#include "Player.h"
#include "Box.h"
#include "Enemy.h"
#include "Range.h"

using namespace sf;
using namespace std;

vector<function<void()>> OnGameOverEvent;

const string levelId = "LevelId";
const float spawnScreenOffset = 300.0f;
const float boxSpawnInterval = 325.0f;
const int maxBoxSpawnAmount = 3;
const int minBoxSpawnAmount = 0;
const Vector2i minBoxSize = Vector2i(60, 60);
const Vector2i maxBoxSize = Vector2i(160, 220);
const int minBoxMass = 1;
const int maxBoxMass = 4;
const float enemySpawnInterval = 550.0f;
const int maxEnemySpawnAmount = 2;
const int minEnemySpawnAmount = 1;
const float boundaryHeight = 50;
const float scrollSpeed = -135.0f;

vector<GameObject*> sideScrollingGameObjects;
float boxSpawnTimer = 0;
float enemySpawnTimer = 0;
float minScreenHalfSpace = 0;

void SpawnBoxes();
void SpawnEnemies();
void OnPlayerKilled();

void StartLevel() {
	srand(time(NULL));

	StartScore();

	UpdateEvent[levelId] = UpdateLevel;
	PlayerKilledEvent[levelId] = OnPlayerKilled;

	Vector2f windowCenter = Vector2f((float)GameWindow.getSize().x / 2, (float)GameWindow.getSize().y / 2);
	float quarterWindowHeight = (float)GameWindow.getSize().y / 4;
	Vector2f player1Pos = Vector2f(windowCenter.x, windowCenter.y + quarterWindowHeight);
	Vector2f player2Pos = Vector2f(windowCenter.x, windowCenter.y - quarterWindowHeight);

	Player *player1 = new Player(Vector2f(player1Pos.x, player1Pos.y));
	Player *player2 = new Player(Vector2f(player2Pos.x, player2Pos.y));

	minScreenHalfSpace = player2->GetBody().getSize().y + 10;

	float halfBoundaryHeight = boundaryHeight / 2;

	Box *topBoundary = new Box(Vector2f(windowCenter.x, -halfBoundaryHeight), Vector2f((float)GameWindow.getSize().x, boundaryHeight), 9999);
	sideScrollingGameObjects.erase(remove(sideScrollingGameObjects.begin(), sideScrollingGameObjects.end(), topBoundary), sideScrollingGameObjects.end());

	Box *bottomBoundary = new Box(Vector2f(windowCenter.x, (float)GameWindow.getSize().y + halfBoundaryHeight), Vector2f((float)GameWindow.getSize().x, boundaryHeight), 9999);
	sideScrollingGameObjects.erase(remove(sideScrollingGameObjects.begin(), sideScrollingGameObjects.end(), bottomBoundary), sideScrollingGameObjects.end());

	SpawnBoxes();
}

//When there are no players left, OnGameOverEvent event will be called
void OnPlayerKilled() {
	if (Players.size() == 0) { 
		for (size_t i = 0; i < OnGameOverEvent.size(); i++) {
			OnGameOverEvent[i]();
		}
	}
}

void StopLevel() {
	StopScore();

	UpdateEvent.erase(levelId);
	PlayerKilledEvent.erase(levelId);

	for (auto const& x : DestroyAllGameObjectsEvent) {
		x.second();
	}

	sideScrollingGameObjects.clear();
	boxSpawnTimer = 0;
	enemySpawnTimer = 0;
	minScreenHalfSpace = 0;
}

void UpdateLevel() {
	float fixedScollSpeed = scrollSpeed * TimeHelper::DeltaTime;

	boxSpawnTimer += abs(fixedScollSpeed);
	if(boxSpawnTimer >= boxSpawnInterval) {
		boxSpawnTimer = 0;
		SpawnBoxes();
	}

	enemySpawnTimer += abs(fixedScollSpeed);
	if (enemySpawnTimer >= enemySpawnInterval) {
		enemySpawnTimer = 0;
		SpawnEnemies();
	}

	float levelObjectLeftSideX = 0;
	GameObject* gameObject;
	for (size_t i = 0; i < sideScrollingGameObjects.size(); i++) {
		gameObject = sideScrollingGameObjects[i];
		gameObject->GetBody().move(fixedScollSpeed, 0);
		levelObjectLeftSideX = gameObject->GetBody().getPosition().x + gameObject->GetBody().getSize().x / 2;
		if (levelObjectLeftSideX < 0) {
			gameObject->Destroy();
		}
	}
}

void AddSideScrollingGameObject(GameObject &gameObject) {
	sideScrollingGameObjects.push_back(&gameObject);
}

void RemoveSideScrollingGameObject(GameObject &gameObject) {
	sideScrollingGameObjects.erase(remove(sideScrollingGameObjects.begin(), sideScrollingGameObjects.end(), &gameObject), sideScrollingGameObjects.end());
}

bool RangeCompare(Range *range1, Range *range2) {
	return range1->GetMin() < range2->GetMin();
}

void SpawnEnemies() {
	int randomEnemySpawnAmount = rand() % (maxEnemySpawnAmount - minEnemySpawnAmount + 1) + minEnemySpawnAmount;

	for (int i = 0; i < randomEnemySpawnAmount; i++) {
		int halfEnemyHeight = (int)enemySize.y / 2;
		int halfEnemyWidth = (int)enemySize.x / 2;

		int minYPos = halfEnemyHeight;
		int maxYPos = GameWindow.getSize().y - halfEnemyHeight;

		int randomEnemyYPos = rand() % (maxYPos - minYPos + 1) + minYPos;

		int minXPos = GameWindow.getSize().x + halfEnemyWidth;
		int maxXPos = minXPos + (int)spawnScreenOffset;
		int randomEnemyXPos = rand() % (maxXPos - minXPos) + minXPos;

		new Enemy(Vector2f((float)randomEnemyXPos, (float)randomEnemyYPos));
	}
}

void SpawnBoxes() {
	vector<Range*> occupiedYSpaces;

	while (true) {
		int randomBoxHeight = rand() % (maxBoxSize.y - minBoxSize.y + 1) + minBoxSize.y;
		int halfBoxHeight = randomBoxHeight / 2;

		int minYPos = halfBoxHeight;
		int maxYPos = GameWindow.getSize().y - halfBoxHeight;

		int randomBoxYPos = rand() % (maxYPos - minYPos + 1) + minYPos;

		Range *occupiedYSpace = new Range(randomBoxYPos - halfBoxHeight, randomBoxYPos + halfBoxHeight);
		occupiedYSpaces.push_back(occupiedYSpace);

		sort(occupiedYSpaces.begin(), occupiedYSpaces.end(), RangeCompare);

		int biggestTopHalfScreenSpace = 0;
		int biggestBottomHalfScreenSpace = 0;
		int halfWindowHeight = GameWindow.getSize().y / 2;
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
				space.SetMax(GameWindow.getSize().y);
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

		new Box(Vector2f(GameWindow.getSize().x + (float)randomBoxWidth, (float)randomBoxYPos), Vector2f((float)randomBoxWidth, (float)randomBoxHeight), (float)randomBoxMass);
	}

	for (size_t i = 0; i < occupiedYSpaces.size(); i++) {
		delete occupiedYSpaces[i];
	}
	occupiedYSpaces.clear();
}