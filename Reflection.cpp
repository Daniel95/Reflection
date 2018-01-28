// Reflection.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <functional> 
#include <vector> 
#include <iostream>
#include "Reflection.h"
#include "InputEvents.h"
#include "Score.h"
#include "GameEvents.h"
#include "Window.h"
#include "MainMenu.h"
#include "Collisions.h"
#include "DelayMethods.h"
#include "Level.h"
#include "Player.h"
#include "TimeHelper.h"
#include "Box.h"

using namespace std;
using namespace sf;

map<string, function<void()>> DestroyAllGameObjectsEvent;

void SwitchToLevel();
void SwitchToMainMenu();

int main() {
	Clock clock;
	SFEvent.push_back(HandleInputEvents);
	UpdateEvent["HandleInputUpdate"] = HandleInputUpdate;

	StartMainMenu();
	OnStartClickedEvent.push_back(SwitchToLevel);
	OnGameOverEvent.push_back(SwitchToMainMenu);

	while (GameWindow.isOpen()) {
		//Update deltatime
		TimeHelper::DeltaTime = clock.restart().asSeconds();

		HandleDelayedMethods();

		//SF events
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

		//Dispatch update event
		for (auto const& x : UpdateEvent) {
			x.second();
		}

		//Collisions
		UpdateCollisions();

		//Drawing
		GameWindow.clear();
		DrawDrawablesInOrder();
		GameWindow.display();
	}

	return 0;
}

void SwitchToLevel() {
	StopMainMenu();
	StartLevel();
}

void SwitchToMainMenu() {
	StopLevel();
	StartMainMenu();
}