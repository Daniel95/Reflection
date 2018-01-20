// Reflection.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <functional> 
#include <vector> 
#include <iostream>
#include "InputEvents.h"
#include "GameEvents.h"
#include "Window.h"
#include "Collisions.h"
#include "Level.h"
#include "Player.h"
#include "TimeHelper.h"
#include "Box.h"

using namespace std;
using namespace sf;

vector<GameObject*> GameObjectsToDestroy;

int main() {
	Clock clock;
	SFEvent.push_back(HandleInputEvents);
	UpdateEvent["HandleInputUpdate"] = HandleInputUpdate;

	StartLevel();

	while (GameWindow.isOpen()) {
		TimeHelper::DeltaTime = clock.restart().asSeconds();

		//Destroy GameObjects that were marked to be destroyed previous frame
		for (size_t i = 0; i < GameObjectsToDestroy.size(); i++) {
			delete GameObjectsToDestroy[i];
		}
		GameObjectsToDestroy.clear();

		Event sfEvent;
		while (GameWindow.pollEvent(sfEvent)) {
			switch (sfEvent.type) {
				case Event::Closed:
					GameWindow.close();
					break;
			}

			for (size_t i = 0; i < SFEvent.size(); i++) {
				SFEvent[i](sfEvent);
			}
		}

		for (auto const& x : UpdateEvent) {
			x.second();
		}

		UpdateCollisions();

		GameWindow.clear();
		DrawDrawablesInOrder();
		GameWindow.display();
	}

	return 0;
}