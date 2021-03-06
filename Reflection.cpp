// Reflection.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <functional> 
#include <vector> 
#include <string> 
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

const string mainMenuId = "MainID";

void SwitchToLevel();
void SwitchToMainMenu();

//here the game is started and events are assigned to control the state of the game.
//The main loop has no game specific logic in it, only calls methods which can be used to create a game.
//You could create an entirely different game by creating new GameObjects, change the way they are spawned in the level
int main() {
	Clock clock;
	SFEvent.push_back(HandleInputEvents);
	UpdateEvent["HandleInputUpdate"] = HandleInputUpdate;
	KeyDownEvent[mainMenuId] = OnKeyDown;

	StartMainMenu();

	//Switch between main menu and level
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

void OnKeyDown(Keyboard::Key key) {
	if (key != Keyboard::Key::Escape) { return; }
	GameWindow.close();
}